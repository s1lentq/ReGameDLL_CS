#include "precompiled.h"

/* <3eb434> ../cstrike/dlls/bot/cs_bot_weapon.cpp:17 */
NOBODY void CCSBot::FireWeaponAtEnemy(void)
{
//	{
//		class CBasePlayer *enemy;                            //    20
//		IsUsingSniperRifle(const class CCSBot *const this);  //    29
//		{
//			class Vector2D toAimSpot;                     //    47
//			float rangeToEnemy;                           //    48
//			float yaw;                                    //    50
//			class Vector2D dir;                           //    51
//			float onTarget;                               //    53
//			float const halfSize;                          //    57
//			float const halfPI;                            //    60
//			float aimTolerance;                           //    61
//			{
//				class CCSBotManager *ctrl;           //    65
//				bool doAttack;                        //    67
//				IsUsingKnife(const class CCSBot *const this);  //    86
//				{
//					float const knifeRange;        //   121
//					ForceRun(CCSBot *const this,
//						float duration);  //   125
//					{
//						float const knifeStabChance;     //   142
//					}
//				}
//				IsUsingPistol(const class CCSBot *const this);  //   157
//				{
//					float const closePistolRange;  //   160
//					StartRapidFire(CCSBot *const this);  //   165
//				}
//				{
//					float const sprayRange;        //   175
//					IsUsingMachinegun(const class CCSBot *const this);  //   176
//					{
//						float const distantTargetRange;        //   183
//						IsUsingSniperRifle(const class CCSBot *const this);  //   184
//					}
//				}
//			}
//			NormalizeInPlace(Vector2D *const this);  //    48
//			DotProduct(const class Vector2D &a,
//					const class Vector2D &b);  //    53
//			IsUsingSniperRifle(const class CCSBot *const this);  //    57
//		}
//		IsActiveWeaponReloading(const class CBot *const this);  //    40
//		GetTimeSinceAcquiredCurrentEnemy(const class CCSBot *const this);  //    33
//		GetSurpriseDelay(const class CCSBot *const this);  //    34
//		ClearSurpriseDelay(CCSBot *const this);  //    37
//		IsNotMoving(const class CCSBot *const this);  //    29
//		StopRapidFire(CCSBot *const this);  //    24
//	}
}

/* <3ea12d> ../cstrike/dlls/bot/cs_bot_weapon.cpp:210 */
void CCSBot::SetAimOffset(float accuracy)
{
	// if our accuracy is less than perfect, it will improve as we "focus in" while not rotating our view
	if (accuracy < 1.0f)
	{
		// if we moved our view, reset our "focus" mechanism
		if (IsViewMoving(100.0f))
		{
			m_aimSpreadTimestamp = gpGlobals->time;
		}

		// focusTime is the time it takes for a bot to "focus in" for very good aim, from 2 to 5 seconds
		const float focusTime = Q_max(5.0f * (1.0f - accuracy), 2.0f);

		float focusInterval = gpGlobals->time - m_aimSpreadTimestamp;
		float focusAccuracy = focusInterval / focusTime;

		// limit how much "focus" will help
		const float maxFocusAccuracy = 0.75f;

		if (focusAccuracy > maxFocusAccuracy)
			focusAccuracy = maxFocusAccuracy;

		accuracy = Q_max(accuracy, focusAccuracy);
	}

	PrintIfWatched("Accuracy = %4.3f\n", accuracy);

	float range = (m_lastEnemyPosition - pev->origin).Length();
	const float_precision maxOffset = range * ((float_precision)m_iFOV / DEFAULT_FOV) * 0.1;
	float error = maxOffset * (1 - accuracy);

	m_aimOffsetGoal[0] = RANDOM_FLOAT(-error, error);
	m_aimOffsetGoal[1] = RANDOM_FLOAT(-error, error);
	m_aimOffsetGoal[2] = RANDOM_FLOAT(-error, error);

	// define time when aim offset will automatically be updated
	m_aimOffsetTimestamp = gpGlobals->time + RANDOM_FLOAT(0.25, 1);
}

/* <3ea224> ../cstrike/dlls/bot/cs_bot_weapon.cpp:252 */
void CCSBot::UpdateAimOffset(void)
{
	if (gpGlobals->time >= m_aimOffsetTimestamp)
	{
		SetAimOffset(GetProfile()->GetSkill());
	}

	// move current offset towards goal offset
	Vector d = m_aimOffsetGoal - m_aimOffset;
	const float stiffness = 0.1f;

	m_aimOffset.x += stiffness * d.x;
	m_aimOffset.y += stiffness * d.y;
	m_aimOffset.z += stiffness * d.z;
}

/* <3ea2b7> ../cstrike/dlls/bot/cs_bot_weapon.cpp:271 */
NOBODY bool CCSBot::AdjustZoom(float range)
{
//	IsUsingSniperRifle(const class CCSBot *const this);  //   273
//	{
//		float const sniperZoomRange;                           //   275
//		float const sniperFarZoomRange;                        //   276
//		GetZoomLevel(const class CCSBot *const this);  //   282
//		GetZoomLevel(const class CCSBot *const this);  //   291
//		GetZoomLevel(const class CCSBot *const this);  //   300
//	}
}

/* <3e9e2d> ../cstrike/dlls/bot/cs_bot_weapon.cpp:320 */
bool isSniperRifle(CBasePlayerItem *item)
{
	switch (item->m_iId)
	{
	case WEAPON_SCOUT:
	case WEAPON_SG550:
	case WEAPON_AWP:
	case WEAPON_G3SG1:
		break;
	default:
		return false;
	}

	return true;
}

/* <3ea3ab> ../cstrike/dlls/bot/cs_bot_weapon.cpp:342 */
bool CCSBot::IsUsingAWP(void)
{
	return (m_pActiveItem && m_pActiveItem->m_iId == WEAPON_AWP);
}

/* <3ea3ce> ../cstrike/dlls/bot/cs_bot_weapon.cpp:357 */
NOBODY bool CCSBot::DoesActiveWeaponHaveSilencer(void)
{
}

/* <3ea3f1> ../cstrike/dlls/bot/cs_bot_weapon.cpp:375 */
bool CCSBot::IsUsingSniperRifle(void)
{
	if (m_pActiveItem)
	{
		return isSniperRifle(m_pActiveItem);
	}
	return false;
}

/* <3ea462> ../cstrike/dlls/bot/cs_bot_weapon.cpp:387 */
NOBODY bool CCSBot::IsSniper(void)
{
//	{
//		int i;                                                //   389
//		{
//			class CBasePlayerItem *item;                 //   391
//			isSniperRifle(CBasePlayerItem *item);  //   393
//		}
//	}
}

// Return true if we are actively sniping (moving to sniper spot or settled in)

/* <3ea4c1> ../cstrike/dlls/bot/cs_bot_weapon.cpp:405 */
bool CCSBot::IsSniping(void) const
{
	if (GetTask() == MOVE_TO_SNIPER_SPOT || GetTask() == SNIPING)
		return true;

	return false;
}

/* <3ea4e8> ../cstrike/dlls/bot/cs_bot_weapon.cpp:417 */
bool CCSBot::IsUsingShotgun(void)
{
	return (m_pActiveItem && (m_pActiveItem->m_iId == WEAPON_XM1014 || m_pActiveItem->m_iId == WEAPON_M3));
}

/* <3ea50f> ../cstrike/dlls/bot/cs_bot_weapon.cpp:437 */
bool CCSBot::IsUsingMachinegun(void)
{
	return (m_pActiveItem && m_pActiveItem->m_iId == WEAPON_M249);
}

/* <3ea532> ../cstrike/dlls/bot/cs_bot_weapon.cpp:449 */
NOBODY bool CCSBot::IsPrimaryWeaponEmpty(void)
{
//	{
//		class CBasePlayerWeapon *gun;                        //   451
//	}
}

/* <3ea578> ../cstrike/dlls/bot/cs_bot_weapon.cpp:467 */
NOBODY bool CCSBot::IsPistolEmpty(void)
{
//	{
//		class CBasePlayerWeapon *gun;                        //   469
//	}
}

/* <3ea5d9> ../cstrike/dlls/bot/cs_bot_weapon.cpp:485 */
NOBODY bool CCSBot::DoEquip(CBasePlayerWeapon *gun)
{
//	Start(IntervalTimer *const this);  //   496
}

/* <3ea621> ../cstrike/dlls/bot/cs_bot_weapon.cpp:510 */
NOBODY void CCSBot::EquipBestWeapon(bool mustEquip)
{
//	{
//		class CCSBotManager *ctrl;                           //   523
//		class CBasePlayerWeapon *primary;                    //   525
//		GetElapsedTime(const class IntervalTimer *const this);  //   513
//		{
//			int weaponClass;                              //   528
//			AllowShotguns(const class CCSBotManager *const this);  //   530
//			DoEquip(CCSBot *const this,
//				class CBasePlayerWeapon *gun);  //   538
//		}
//		DoEquip(CCSBot *const this,
//			class CBasePlayerWeapon *gun);  //   545
//		EquipKnife(CCSBot *const this);  //   550
//	}
}

/* <3ea7fe> ../cstrike/dlls/bot/cs_bot_weapon.cpp:557 */
NOBODY void CCSBot::EquipPistol(void)
{
//	{
//		class CCSBotManager *ctrl;                           //   563
//		GetElapsedTime(const class IntervalTimer *const this);  //   560
//		IsUsingPistol(const class CCSBot *const this);  //   566
//		DoEquip(CCSBot *const this,
//			class CBasePlayerWeapon *gun);  //   567
//	}
}

/* <3ea91a> ../cstrike/dlls/bot/cs_bot_weapon.cpp:575 */
NOBODY void CCSBot::EquipKnife(void)
{
//	IsUsingKnife(const class CCSBot *const this);  //   581
//	EquipKnife(CCSBot *const this);  //   575
}

/* <3ea98b> ../cstrike/dlls/bot/cs_bot_weapon.cpp:589 */
NOBODY bool CCSBot::HasGrenade(void)
{
}

/* <3ea9ae> ../cstrike/dlls/bot/cs_bot_weapon.cpp:598 */
NOBODY bool CCSBot::EquipGrenade(bool noSmoke)
{
//	IsSniper(const class CCSBot *const this);  //   601
//	IsUsingGrenade(const class CCSBot *const this);  //   604
//	HasGrenade(const class CCSBot *const this);  //   607
}

/* <3eaa8c> ../cstrike/dlls/bot/cs_bot_weapon.cpp:624 */
bool CCSBot::IsUsingKnife(void)
{
	CBasePlayerWeapon *gun = (CBasePlayerWeapon *)m_pActiveItem;
	return (gun && gun->m_iId == 29);
}

/* <3eaac2> ../cstrike/dlls/bot/cs_bot_weapon.cpp:638 */
bool CCSBot::IsUsingPistol(void)
{
	UNTESTED

	CBasePlayerWeapon *gun = (CBasePlayerWeapon *)m_pActiveItem;
	if (gun)
	{
		switch (gun->m_iId)
		{
		case WEAPON_USP:
		case WEAPON_GLOCK18:
		case WEAPON_P228:
		case WEAPON_DEAGLE:
		case WEAPON_ELITE:
		case WEAPON_FIVESEVEN:
			return true;
		default:
			break;
		}

		// TODO: check it, from the dwarf should be used function IsPistol
//	{
//		class CBasePlayerWeapon *gun;                        //   640
//		IsPistol(CBasePlayerWeapon *const this);  //   642
//	}
		//return gun->IsPistol();
	}
	return false;
}

/* <3eab09> ../cstrike/dlls/bot/cs_bot_weapon.cpp:652 */
bool CCSBot::IsUsingGrenade(void)
{
	CBasePlayerWeapon *gun = (CBasePlayerWeapon *)m_pActiveItem;
	return (gun && (gun->m_iId == WEAPON_SMOKEGRENADE || gun->m_iId == WEAPON_FLASHBANG || gun->m_iId == WEAPON_HEGRENADE));
}

/* <3eab3f> ../cstrike/dlls/bot/cs_bot_weapon.cpp:672 */
NOBODY bool CCSBot::IsUsingHEGrenade(void)
{
//	{
//		class CBasePlayerWeapon *gun;                        //   674
//	}
}

/* <3eab80> ../cstrike/dlls/bot/cs_bot_weapon.cpp:690 */
void CCSBot::ThrowGrenade(const Vector *target)
{
	if (IsUsingGrenade() && !m_isWaitingToTossGrenade)
	{
		const float angleTolerance = 1.0f;

		SetLookAt("GrenadeThrow", target, PRIORITY_UNINTERRUPTABLE, 3.0f, false, angleTolerance);

		m_isWaitingToTossGrenade = true;
		m_tossGrenadeTimer.Start(3.0f);
	}
}

/* <3eac08> ../cstrike/dlls/bot/cs_bot_weapon.cpp:709 */
NOBODY bool CCSBot::FindGrenadeTossPathTarget(const Vector *pos)
{
//	{
//		int i;                                                //   715
//		Vector dir;                                     //   726
//		float length;                                         //   727
//		float const inc;                                       //   729
//		Vector p;                                       //   730
//		Vector visibleSpot;                             //   731
//		float const bufferRange;                               //   745
//		TraceResult result;                                   //   747
//		Vector check;                                   //   748
//		operator+(const Vector *const this,
//				const Vector &v);  //   718
//		operator-(const Vector *const this,
//				const Vector &v);  //   726
//		NormalizeInPlace(Vector *const this);  //   727
//		Vector(Vector *const this,
//			const Vector &v);  //   731
//		operator+(const Vector *const this,
//				const Vector &v);  //   751
//		{
//			float range;                                  //   756
//		}
//		operator+(const Vector *const this,
//				const Vector &v);  //   764
//		{
//			float range;                                  //   769
//		}
//		operator+(const Vector *const this,
//				const Vector &v);  //   777
//		{
//			float range;                                  //   782
//		}
//		operator+(const Vector *const this,
//				const Vector &v);  //   790
//		{
//			float range;                                  //   795
//		}
//		{
//			float t;                                      //   732
//			operator*(float fl,
//					const Vector &v);  //   734
//			operator+(const Vector *const this,
//					const Vector &v);  //   734
//		}
//	}
}

/* <3eaf22> ../cstrike/dlls/bot/cs_bot_weapon.cpp:810 */
NOBODY void CCSBot::ReloadCheck(void)
{
//	{
//		float const safeReloadWaitTime;                        //   812
//		float const reloadAmmoRatio;                           //   813
//		IsActiveWeaponReloading(const class CBot *const this);  //   819
//		IsPistolEmpty(const class CCSBot *const this);  //   827
//		IsUsingAWP(const class CCSBot *const this);  //   848
//		GetNearbyEnemyCount(const class CCSBot *const this);  //   854
//		{
//			float const hideChance;                        //   857
//			{
//				float const safeTime;                  //   861
//				GetTimeSinceLastSawEnemy(const class CCSBot *const this);  //   862
//				{
//					const Vector *spot;   //   865
//				}
//			}
//		}
//		GetTimeSinceLastSawEnemy(const class CCSBot *const this);  //   835
//		IsPistol(CBasePlayerWeapon *const this);  //   827
//	}
}

/* <3eb0ac> ../cstrike/dlls/bot/cs_bot_weapon.cpp:885 */
NOBODY void CCSBot::SilencerCheck(void)
{
//	{
//		float const safeSilencerWaitTime;                      //   887
//		IsActiveWeaponReloading(const class CBot *const this);  //   889
//		DoesActiveWeaponHaveSilencer(const class CCSBot *const this);  //   892
//		GetNearbyEnemyCount(const class CCSBot *const this);  //   896
//		{
//			bool isSilencerOn;                            //   899
//			class CBasePlayerWeapon *myGun;              //   901
//		}
//	}
}

/* <3eb1a9> ../cstrike/dlls/bot/cs_bot_weapon.cpp:926 */
NOBODY void CCSBot::__MAKE_VHOOK(OnTouchingWeapon)(CWeaponBox *box)
{
//	{
//		class CBasePlayerItem *droppedGun;                   //   929
//		class CBasePlayerWeapon *myGun;                      //   934
//		float const safeTime;                                  //   947
//		GetTimeSinceLastSawEnemy(const class CCSBot *const this);  //   948
//		{
//			int i;                                        //   952
//			{
//				int prefID;                           //   954
//				GetWeaponPreference(const class BotProfile *const this,
//							int i);  //   954
//			}
//		}
//	}
}

/* <3eb277> ../cstrike/dlls/bot/cs_bot_weapon.cpp:977 */
NOBODY bool CCSBot::IsFriendInLineOfFire(void)
{
//	{
//		Vector aimDir;                                  //   981
//		TraceResult result;                                   //   984
//		Vector target;                                  //   985
//		operator+(const Vector *const this,
//				const Vector &v);  //   980
//		operator*(float fl,
//				const Vector &v);  //   985
//		operator+(const Vector *const this,
//				const Vector &v);  //   985
//		{
//			class CBaseEntity *victim;                   //   990
//			Instance(edict_t *pent);  //   990
//		}
//	}
}

/* <3eb84d> ../cstrike/dlls/bot/cs_bot_weapon.cpp:1009 */
NOBODY float CCSBot::ComputeWeaponSightRange(void)
{
//	{
//		Vector aimDir;                                  //  1013
//		TraceResult result;                                   //  1016
//		Vector target;                                  //  1017
//		operator+(const Vector *const this,
//				const Vector &v);  //  1012
//		operator*(float fl,
//				const Vector &v);  //  1017
//		operator+(const Vector *const this,
//				const Vector &v);  //  1017
//		operator-(const Vector *const this,
//				const Vector &v);  //  1020
//		Length(const Vector *const this);  //  1020
//	}
}

#ifdef HOOK_GAMEDLL

void CCSBot::OnTouchingWeapon(CWeaponBox *box)
{
	OnTouchingWeapon_(box);
}

#endif // HOOK_GAMEDLL
