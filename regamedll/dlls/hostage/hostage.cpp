/*
*
*   This program is free software; you can redistribute it and/or modify it
*   under the terms of the GNU General Public License as published by the
*   Free Software Foundation; either version 2 of the License, or (at
*   your option) any later version.
*
*   This program is distributed in the hope that it will be useful, but
*   WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*   General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program; if not, write to the Free Software Foundation,
*   Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*   In addition, as a special exception, the author gives permission to
*   link the code of this program with the Half-Life Game Engine ("HL
*   Engine") and Modified Game Libraries ("MODs") developed by Valve,
*   L.L.C ("Valve").  You must obey the GNU General Public License in all
*   respects for all of the code used other than the HL Engine and MODs
*   from Valve.  If you modify this file, you may extend this exception
*   to your version of the file, but you are not obligated to do so.  If
*   you do not wish to do so, delete this exception statement from your
*   version.
*
*/

#include "precompiled.h"

cvar_t cv_hostage_debug = { "hostage_debug", "0", FCVAR_SERVER, 0.0f, nullptr };
cvar_t cv_hostage_stop  = { "hostage_stop", "0", FCVAR_SERVER, 0.0f, nullptr };

CHostageManager *g_pHostages = nullptr;
int g_iHostageNumber = 0;

struct
{
	HostageChatterType type;
	char *fileName;
} hostageSoundStruct[] = {
	{ HOSTAGE_CHATTER_START_FOLLOW, "hostage/huse/getouttahere.wav" },
	{ HOSTAGE_CHATTER_START_FOLLOW, "hostage/huse/illfollow.wav"    },
	{ HOSTAGE_CHATTER_START_FOLLOW, "hostage/huse/letsdoit.wav"     },
	{ HOSTAGE_CHATTER_START_FOLLOW, "hostage/huse/letsgo.wav"       },
	{ HOSTAGE_CHATTER_START_FOLLOW, "hostage/huse/letshurry.wav"    },
	{ HOSTAGE_CHATTER_START_FOLLOW, "hostage/huse/letsmove.wav"     },
	{ HOSTAGE_CHATTER_START_FOLLOW, "hostage/huse/okletsgo.wav"     },
	{ HOSTAGE_CHATTER_START_FOLLOW, "hostage/huse/youlead.wav"      },

	{ HOSTAGE_CHATTER_STOP_FOLLOW, "hostage/hunuse/comeback.wav"    },
	{ HOSTAGE_CHATTER_STOP_FOLLOW, "hostage/hunuse/dontleaveme.wav" },
	{ HOSTAGE_CHATTER_STOP_FOLLOW, "hostage/hunuse/illstayhere.wav" },
	{ HOSTAGE_CHATTER_STOP_FOLLOW, "hostage/hunuse/notleaveme.wav"  },
	{ HOSTAGE_CHATTER_STOP_FOLLOW, "hostage/hunuse/yeahillstay.wav" },

	{ HOSTAGE_CHATTER_INTIMIDATED, "hostage/hseenbyt/donthurtme1.wav"     },
	{ HOSTAGE_CHATTER_INTIMIDATED, "hostage/hseenbyt/donthurtme2.wav"     },
	{ HOSTAGE_CHATTER_INTIMIDATED, "hostage/hseenbyt/dontkill.wav"        },
	{ HOSTAGE_CHATTER_INTIMIDATED, "hostage/hseenbyt/endpeace.wav"        },
	{ HOSTAGE_CHATTER_INTIMIDATED, "hostage/hseenbyt/nevernegotiate.wav"  },
	{ HOSTAGE_CHATTER_INTIMIDATED, "hostage/hseenbyt/nottellanything.wav" },
	{ HOSTAGE_CHATTER_INTIMIDATED, "hostage/hseenbyt/surrender.wav"       },
	{ HOSTAGE_CHATTER_INTIMIDATED, "hostage/hseenbyt/whatdoyou.wav"       },
	{ HOSTAGE_CHATTER_INTIMIDATED, "hostage/hseenbyt/whyareyou.wav"       },

	{ HOSTAGE_CHATTER_RETREAT, "hostage/hseenbyt/donthurtme1.wav" },
	{ HOSTAGE_CHATTER_RETREAT, "hostage/hseenbyt/donthurtme2.wav" },
	{ HOSTAGE_CHATTER_RETREAT, "hostage/hseenbyt/dontkill.wav"    },
	{ HOSTAGE_CHATTER_RETREAT, "hostage/hseenbyt/dontkill.wav"    },
	{ HOSTAGE_CHATTER_RETREAT, "hostage/hretreat/illgoback1.wav"  },
	{ HOSTAGE_CHATTER_RETREAT, "hostage/hretreat/illgoback2.wav"  },
	{ HOSTAGE_CHATTER_RETREAT, "hostage/hretreat/okokgoing.wav"   },
	{ HOSTAGE_CHATTER_RETREAT, "hostage/hretreat/okokgoing2.wav"  },
	{ HOSTAGE_CHATTER_RETREAT, "hostage/hretreat/sorry1.wav"      },
	{ HOSTAGE_CHATTER_RETREAT, "hostage/hretreat/sorry2.wav"      },
	{ HOSTAGE_CHATTER_RETREAT, "hostage/hretreat/sorry3.wav"      },

	{ HOSTAGE_CHATTER_PAIN, "hostage/hpain/hpain1.wav" },
	{ HOSTAGE_CHATTER_PAIN, "hostage/hpain/hpain2.wav" },
	{ HOSTAGE_CHATTER_PAIN, "hostage/hpain/hpain3.wav" },
	{ HOSTAGE_CHATTER_PAIN, "hostage/hpain/hpain4.wav" },
	{ HOSTAGE_CHATTER_PAIN, "hostage/hpain/hpain5.wav" },
	{ HOSTAGE_CHATTER_PAIN, "hostage/hpain/hpain6.wav" },

	{ HOSTAGE_CHATTER_SCARED_OF_GUNFIRE, "hostage/hreactions/awwcrap1.wav"      },
	{ HOSTAGE_CHATTER_SCARED_OF_GUNFIRE, "hostage/hreactions/awwcrap2.wav"      },
	{ HOSTAGE_CHATTER_SCARED_OF_GUNFIRE, "hostage/hreactions/getdown1.wav"      },
	{ HOSTAGE_CHATTER_SCARED_OF_GUNFIRE, "hostage/hreactions/getdown2.wav"      },
	{ HOSTAGE_CHATTER_SCARED_OF_GUNFIRE, "hostage/hreactions/getdown3.wav"      },
	{ HOSTAGE_CHATTER_SCARED_OF_GUNFIRE, "hostage/hreactions/lookout1.wav"      },
	{ HOSTAGE_CHATTER_SCARED_OF_GUNFIRE, "hostage/hreactions/lookout2.wav"      },
	{ HOSTAGE_CHATTER_SCARED_OF_GUNFIRE, "hostage/hreactions/lookshooting1.wav" },
	{ HOSTAGE_CHATTER_SCARED_OF_GUNFIRE, "hostage/hreactions/lookshooting2.wav" },
	{ HOSTAGE_CHATTER_SCARED_OF_GUNFIRE, "hostage/hreactions/lookshooting3.wav" },
	{ HOSTAGE_CHATTER_SCARED_OF_GUNFIRE, "hostage/hreactions/ohgod1.wav"        },
	{ HOSTAGE_CHATTER_SCARED_OF_GUNFIRE, "hostage/hreactions/ohgod2.wav"        },

	{ HOSTAGE_CHATTER_SCARED_OF_MURDER, "hostage/hreactions/awwcrap1.wav" },
	{ HOSTAGE_CHATTER_SCARED_OF_MURDER, "hostage/hreactions/awwcrap2.wav" },
	{ HOSTAGE_CHATTER_SCARED_OF_MURDER, "hostage/hreactions/deargod1.wav" },
	{ HOSTAGE_CHATTER_SCARED_OF_MURDER, "hostage/hreactions/deargod2.wav" },
	{ HOSTAGE_CHATTER_SCARED_OF_MURDER, "hostage/hreactions/deargod3.wav" },
	{ HOSTAGE_CHATTER_SCARED_OF_MURDER, "hostage/hreactions/ohgod1.wav"   },
	{ HOSTAGE_CHATTER_SCARED_OF_MURDER, "hostage/hreactions/ohgod2.wav"   },
	{ HOSTAGE_CHATTER_SCARED_OF_MURDER, "hostage/hreactions/ohno1.wav"    },
	{ HOSTAGE_CHATTER_SCARED_OF_MURDER, "hostage/hreactions/ohno2.wav"    },
	{ HOSTAGE_CHATTER_SCARED_OF_MURDER, "hostage/hreactions/awww2.wav"    },
	{ HOSTAGE_CHATTER_SCARED_OF_MURDER, "hostage/hreactions/awww4.wav"    },

	{ HOSTAGE_CHATTER_LOOK_OUT, "hostage/hreactions/awwcrap1.wav" },
	{ HOSTAGE_CHATTER_LOOK_OUT, "hostage/hreactions/awwcrap2.wav" },
	{ HOSTAGE_CHATTER_LOOK_OUT, "hostage/hreactions/lookout1.wav" },
	{ HOSTAGE_CHATTER_LOOK_OUT, "hostage/hreactions/lookout2.wav" },

	{ HOSTAGE_CHATTER_PLEASE_RESCUE_ME, "hostage/hseenbyct/areyousave.wav"  },
	{ HOSTAGE_CHATTER_PLEASE_RESCUE_ME, "hostage/hseenbyct/getmeoutta1.wav" },
	{ HOSTAGE_CHATTER_PLEASE_RESCUE_ME, "hostage/hseenbyct/getmeoutta2.wav" },
	{ HOSTAGE_CHATTER_PLEASE_RESCUE_ME, "hostage/hseenbyct/imahostage.wav"  },
	{ HOSTAGE_CHATTER_PLEASE_RESCUE_ME, "hostage/hseenbyct/rescueme1.wav"   },
	{ HOSTAGE_CHATTER_PLEASE_RESCUE_ME, "hostage/hseenbyct/rescueme2.wav"   },
	{ HOSTAGE_CHATTER_PLEASE_RESCUE_ME, "hostage/hseenbyct/theyregonna.wav" },

	{ HOSTAGE_CHATTER_IMPATIENT_FOR_RESCUE, "hostage/hseenbyct/areyousave.wav"  },
	{ HOSTAGE_CHATTER_IMPATIENT_FOR_RESCUE, "hostage/hseenbyct/getmeoutta1.wav" },
	{ HOSTAGE_CHATTER_IMPATIENT_FOR_RESCUE, "hostage/hseenbyct/getmeoutta2.wav" },
	{ HOSTAGE_CHATTER_IMPATIENT_FOR_RESCUE, "hostage/hseenbyct/rescueme1.wav"   },
	{ HOSTAGE_CHATTER_IMPATIENT_FOR_RESCUE, "hostage/hseenbyct/rescueme2.wav"   },

	{ HOSTAGE_CHATTER_SEE_RESCUE_ZONE, "hostage/hseezone/almostouttahere.wav" },
	{ HOSTAGE_CHATTER_SEE_RESCUE_ZONE, "hostage/hseezone/almostthere.wav"     },
	{ HOSTAGE_CHATTER_SEE_RESCUE_ZONE, "hostage/hseezone/keepgoing.wav"       },
	{ HOSTAGE_CHATTER_SEE_RESCUE_ZONE, "hostage/hseezone/notfar.wav"          },

	{ HOSTAGE_CHATTER_CTS_WIN, "hostage/hctwin/alldead.wav"   },
	{ HOSTAGE_CHATTER_CTS_WIN, "hostage/hctwin/goodnews.wav"  },
	{ HOSTAGE_CHATTER_CTS_WIN, "hostage/hctwin/outtahere.wav" },
	{ HOSTAGE_CHATTER_CTS_WIN, "hostage/hctwin/over1.wav"     },
	{ HOSTAGE_CHATTER_CTS_WIN, "hostage/hctwin/over2.wav"     },
	{ HOSTAGE_CHATTER_CTS_WIN, "hostage/hctwin/over3.wav"     },
	{ HOSTAGE_CHATTER_CTS_WIN, "hostage/hctwin/over4.wav"     },
	{ HOSTAGE_CHATTER_CTS_WIN, "hostage/hctwin/over5.wav"     },
	{ HOSTAGE_CHATTER_CTS_WIN, "hostage/hctwin/relief.wav"    },

	{ HOSTAGE_CHATTER_TERRORISTS_WIN, "hostage/htwin/doomed.wav"  },
	{ HOSTAGE_CHATTER_TERRORISTS_WIN, "hostage/htwin/godno.wav"   },
	{ HOSTAGE_CHATTER_TERRORISTS_WIN, "hostage/htwin/nowwhat.wav" },
	{ HOSTAGE_CHATTER_TERRORISTS_WIN, "hostage/htwin/ohman.wav"   },
	{ HOSTAGE_CHATTER_TERRORISTS_WIN, "hostage/htwin/ohno.wav"    },

	{ HOSTAGE_CHATTER_RESCUED, "hostage/hrescued/finally.wav"     },
	{ HOSTAGE_CHATTER_RESCUED, "hostage/hrescued/finallysafe.wav" },
	{ HOSTAGE_CHATTER_RESCUED, "hostage/hrescued/thankyou.wav"    },
	{ HOSTAGE_CHATTER_RESCUED, "hostage/hrescued/wemadeit1.wav"   },
	{ HOSTAGE_CHATTER_RESCUED, "hostage/hrescued/wemadeit2.wav"   },
	{ HOSTAGE_CHATTER_RESCUED, "hostage/hrescued/wemadeit3.wav"   },

	{ HOSTAGE_CHATTER_WARN_NEARBY, "hostage/hwarn/becareful1.wav"   },
	{ HOSTAGE_CHATTER_WARN_NEARBY, "hostage/hwarn/becareful2.wav"   },
	{ HOSTAGE_CHATTER_WARN_NEARBY, "hostage/hwarn/stillaround1.wav" },
	{ HOSTAGE_CHATTER_WARN_NEARBY, "hostage/hwarn/stillaround2.wav" },

	{ HOSTAGE_CHATTER_WARN_SPOTTED, "hostage/hwarn/lookout1.wav"   },
	{ HOSTAGE_CHATTER_WARN_SPOTTED, "hostage/hwarn/lookout2.wav"   },
	{ HOSTAGE_CHATTER_WARN_SPOTTED, "hostage/hwarn/overthere1.wav" },
	{ HOSTAGE_CHATTER_WARN_SPOTTED, "hostage/hwarn/overthere2.wav" },

	{ HOSTAGE_CHATTER_CALL_TO_RESCUER, "hostage/hwavect/helpme1.wav"   },
	{ HOSTAGE_CHATTER_CALL_TO_RESCUER, "hostage/hwavect/helpme2.wav"   },
	{ HOSTAGE_CHATTER_CALL_TO_RESCUER, "hostage/hwavect/hey1.wav"      },
	{ HOSTAGE_CHATTER_CALL_TO_RESCUER, "hostage/hwavect/hey2.wav"      },
	{ HOSTAGE_CHATTER_CALL_TO_RESCUER, "hostage/hwavect/overhere1.wav" },

	{ HOSTAGE_CHATTER_COUGH, "hostage/hsmoke/cough1.wav" },
	{ HOSTAGE_CHATTER_COUGH, "hostage/hsmoke/cough2.wav" },
	{ HOSTAGE_CHATTER_COUGH, "hostage/hsmoke/cough3.wav" },
	{ HOSTAGE_CHATTER_COUGH, "hostage/hsmoke/cough4.wav" },
	{ HOSTAGE_CHATTER_COUGH, "hostage/hsmoke/cough5.wav" },
	{ HOSTAGE_CHATTER_COUGH, "hostage/hsmoke/cough6.wav" },

	{ HOSTAGE_CHATTER_BLINDED, "hostage/hflash/cantsee.wav" },
	{ HOSTAGE_CHATTER_BLINDED, "hostage/hflash/myeyes.wav"  },

	{ HOSTAGE_CHATTER_SAW_HE_GRENADE, "hostage/hgrenade/grenade1.wav" },
	{ HOSTAGE_CHATTER_SAW_HE_GRENADE, "hostage/hgrenade/grenade2.wav" },
	{ HOSTAGE_CHATTER_SAW_HE_GRENADE, "hostage/hgrenade/run.wav"      },
	{ HOSTAGE_CHATTER_SAW_HE_GRENADE, "hostage/hgrenade/watchout.wav" },

	{ HOSTAGE_CHATTER_DEATH_CRY, "hostage/hdie/hdeath1.wav" },
	{ HOSTAGE_CHATTER_DEATH_CRY, "hostage/hdie/hdeath2.wav" },
	{ HOSTAGE_CHATTER_DEATH_CRY, "hostage/hdie/hdeath3.wav" },
};

LINK_ENTITY_TO_CLASS(hostage_entity, CHostage, CCSHostage)
LINK_ENTITY_TO_CLASS(monster_scientist, CHostage, CCSHostage)

void CHostage::Spawn()
{
	if (!g_pHostages) {
		g_pHostages = new CHostageManager;
	}

	Precache();

	MAKE_STRING_CLASS("hostage_entity", pev);

	pev->movetype = MOVETYPE_STEP;
	pev->solid = SOLID_SLIDEBOX;
	pev->takedamage = DAMAGE_YES;
	pev->flags |= FL_MONSTER;
	pev->deadflag = DEAD_NO;
	pev->max_health = 100;
	pev->health = pev->max_health;
	pev->gravity = 1;
	pev->view_ofs = VEC_HOSTAGE_VIEW;
	pev->velocity = Vector(0, 0, 0);

	if (pev->spawnflags & SF_MONSTER_HITMONSTERCLIP)
		pev->flags |= FL_MONSTERCLIP;

	if (pev->skin < 0)
		pev->skin = 0;

	SET_MODEL(edict(), STRING(pev->model));
	SetActivity(ACT_IDLE);

	m_flNextChange = 0;
	m_State = STAND;
	m_hTargetEnt = nullptr;
	m_hStoppedTargetEnt = nullptr;
	m_vPathToFollow[0] = Vector(0, 0, 0);
	m_flFlinchTime = 0;
	m_bRescueMe = FALSE;

	UTIL_SetSize(pev, VEC_HOSTAGE_HULL_MIN, VEC_HOSTAGE_HULL_MAX);
	UTIL_MakeVectors(pev->v_angle);

	SetBoneController(0, UTIL_VecToYaw(gpGlobals->v_forward));
	SetBoneController(1, 0);
	SetBoneController(2, 0);
	SetBoneController(3, 0);
	SetBoneController(4, 0);

	DROP_TO_FLOOR(edict());

	SetThink(&CHostage::IdleThink);
	pev->nextthink = gpGlobals->time + RANDOM_FLOAT(0.1, 0.2);

	m_flNextFullThink = gpGlobals->time + RANDOM_FLOAT(0.1, 0.2);
	m_vStart = pev->origin;
	m_vStartAngles = pev->angles;
	m_vOldPos = Vector(9999, 9999, 9999);
	m_iHostageIndex = ++g_iHostageNumber;

	m_nTargetNode = NODE_INVALID_EMPTY;
	m_fHasPath = FALSE;

	m_flLastPathCheck = -1;
	m_flPathAcquired = -1;
	m_flPathCheckInterval = 0.1f;
	m_flNextRadarTime = gpGlobals->time + RANDOM_FLOAT(0, 1);

	m_LocalNav = new CLocalNav(this);
	m_bStuck = FALSE;
	m_flStuckTime = 0;
	m_improv = nullptr;
}

void CHostage::Precache()
{
	if (AreImprovAllowed())
	{
		static int which = 0;
		switch (which)
		{
		case REGULAR_GUY:
			pev->model = MAKE_STRING("models/hostageA.mdl");
			break;
		case OLD_GUY:
			pev->model = MAKE_STRING("models/hostageB.mdl");
			break;
		case BLACK_GUY:
			pev->model = MAKE_STRING("models/hostageC.mdl");
			break;
		case GOOFY_GUY:
			pev->model = MAKE_STRING("models/hostageD.mdl");
			break;
		default:
			break;
		}

		m_whichModel = static_cast<ModelType>(which);

		if (++which > 3)
			which = 0;
	}
	else
	{
		m_whichModel = REGULAR_GUY;
		if (pev->model.IsNull())
		{
			pev->model = MAKE_STRING("models/scientist.mdl");
		}
	}

	PRECACHE_MODEL(pev->model);
	PRECACHE_SOUND("hostage/hos1.wav");
	PRECACHE_SOUND("hostage/hos2.wav");
	PRECACHE_SOUND("hostage/hos3.wav");
	PRECACHE_SOUND("hostage/hos4.wav");
	PRECACHE_SOUND("hostage/hos5.wav");
	PRECACHE_MODEL("sprites/smoke.spr");
}

void CHostage::SetActivity(Activity act)
{
	if (m_Activity != act)
	{
		int sequence = LookupActivity(act);
		if (sequence != ACT_INVALID)
		{
			if (pev->sequence != sequence)
			{
				if ((m_Activity != ACT_WALK && m_Activity != ACT_RUN) || (act != ACT_WALK && act != ACT_RUN))
				{
					pev->frame = 0;
				}

				pev->sequence = sequence;
			}

			m_Activity = act;
			ResetSequenceInfo();
		}
	}
}

void CHostage::IdleThink()
{
	float flInterval;
	const float upkeepRate = 0.03f;
	const float giveUpTime = (1 / 30.0f);
	float const updateRate = 0.1f;

	if (AreImprovAllowed() && !TheNavAreaList.empty())
	{
		if (!m_improv)
		{
			m_improv = new CHostageImprov(this);
		}
	}
	else
	{
		if (m_improv)
		{
			delete m_improv;
			m_improv = nullptr;
		}
	}

	pev->nextthink = gpGlobals->time + giveUpTime;

	flInterval = StudioFrameAdvance();
	DispatchAnimEvents(flInterval);

	if (m_improv)
	{
		m_improv->OnUpkeep(upkeepRate);
	}

	if (m_flNextFullThink > gpGlobals->time)
	{
		return;
	}

	m_flNextFullThink = gpGlobals->time + 0.1f;

	if (pev->deadflag == DEAD_DEAD)
	{
		UTIL_SetSize(pev, Vector(0, 0, 0), Vector(0, 0, 0));
		return;
	}

	if (m_hTargetEnt && ((m_bStuck && gpGlobals->time - m_flStuckTime > 5.0f) || m_hTargetEnt->pev->deadflag != DEAD_NO))
	{
		m_State = STAND;
		m_hTargetEnt = nullptr;
		m_bStuck = FALSE;
	}

	if (m_hTargetEnt || m_improv)
	{
		CBasePlayer *pPlayer = nullptr;

		if (m_improv)
		{
			if (m_improv->IsFollowing())
				pPlayer = m_improv->GetFollowLeader();
		}
		else
		{
			pPlayer = GetClassPtr<CCSPlayer>((CBasePlayer *)m_hTargetEnt->pev);
		}

		if (!pPlayer || pPlayer->m_iTeam == CT)
		{
			if (!CSGameRules()->m_bMapHasRescueZone)
			{
				bool bResHostagePt = false;

				if (UTIL_FindEntityByClassname(nullptr, "info_hostage_rescue"))
					bResHostagePt = true;

				CBaseEntity *pSpot = nullptr;
				while ((pSpot = UTIL_FindEntityByClassname(pSpot, "info_hostage_rescue")))
				{
					if ((pSpot->pev->origin - pev->origin).Length() < MAX_HOSTAGES_RESCUE_RADIUS)
					{
						m_bRescueMe = TRUE;
						break;
					}
				}

				if (!bResHostagePt)
				{
					pSpot = nullptr;

					while ((pSpot = UTIL_FindEntityByClassname(pSpot, "info_player_start")))
					{
						if ((pSpot->pev->origin - pev->origin).Length() < MAX_HOSTAGES_RESCUE_RADIUS)
						{
							m_bRescueMe = TRUE;
							break;
						}
					}
				}
			}

			if (m_bRescueMe)
			{
				if (TheBots)
				{
					TheBots->OnEvent(EVENT_HOSTAGE_RESCUED, pPlayer, this);
				}

				if (TheCareerTasks && CSGameRules()->IsCareer() && pPlayer && !pPlayer->IsBot())
				{
					TheCareerTasks->HandleEvent(EVENT_HOSTAGE_RESCUED, pPlayer);
				}

				pev->deadflag = DEAD_RESPAWNABLE;

				if (pPlayer)
				{
					pPlayer->AddAccount(REWARD_TAKEN_HOSTAGE, RT_HOSTAGE_RESCUED);
					UTIL_LogPrintf("\"%s<%i><%s><CT>\" triggered \"Rescued_A_Hostage\"\n", STRING(pPlayer->pev->netname),
						GETPLAYERUSERID(pPlayer->edict()), GETPLAYERAUTHID(pPlayer->edict()));
				}

				SendHostageEventMsg();

				MESSAGE_BEGIN(MSG_SPEC, SVC_DIRECTOR);
					WRITE_BYTE(9);
					WRITE_BYTE(DRC_CMD_EVENT);
					WRITE_SHORT(pPlayer ? pPlayer->entindex() : 0);
					WRITE_SHORT(entindex());
					WRITE_LONG(15);
				MESSAGE_END();

				pev->effects |= EF_NODRAW;
				Remove();

				CSGameRules()->m_iHostagesRescued++;
				CSGameRules()->CheckWinConditions();

				Broadcast(pPlayer ? "rescued" : "escaped");
			}
		}
	}

	if (m_improv)
	{
		m_improv->OnUpdate(updateRate);
	}
	else
	{
		DoFollow();

		if (gpGlobals->time >= m_flFlinchTime)
		{
			if (pev->velocity.Length() > 160.0f)
			{
				SetActivity(ACT_RUN);
			}
			else if (pev->velocity.Length() > 15.0f)
			{
				SetActivity(ACT_WALK);
			}
			else
			{
				SetActivity(ACT_IDLE);
			}
		}
	}

	if (pev->deadflag != DEAD_DEAD && !(pev->effects & EF_NODRAW))
	{
		if (m_flNextRadarTime <= gpGlobals->time)
		{
			Vector vDistance = m_vOldPos - pev->origin;

			if (vDistance.Length() > 1.0f)
			{
				m_vOldPos = pev->origin;

				if (!CSGameRules()->m_flRestartRoundTime)
				{
					SendHostagePositionMsg();
				}
			}

			m_flNextRadarTime = gpGlobals->time + 1.0f;
		}
	}
}

void CHostage::Remove()
{
	pev->movetype = MOVETYPE_NONE;
	pev->solid = SOLID_NOT;
	pev->takedamage = DAMAGE_NO;

#ifdef REGAMEDLL_FIXES
	pev->deadflag = DEAD_DEAD;
#endif

	UTIL_SetSize(pev, Vector(0, 0, 0), Vector(0, 0, 0));
	pev->nextthink = -1;
	m_flNextFullThink = -1;
}

void CHostage::RePosition()
{
	pev->health = pev->max_health;
	pev->movetype = MOVETYPE_STEP;
	pev->solid = SOLID_SLIDEBOX;
	pev->takedamage = DAMAGE_YES;
	pev->deadflag = DEAD_NO;
	pev->velocity = Vector(0, 0, 0);
	pev->angles = m_vStartAngles;
	pev->effects &= ~EF_NODRAW;

	m_hTargetEnt = nullptr;
	m_hStoppedTargetEnt = nullptr;

	m_bTouched = FALSE;
	m_bRescueMe = FALSE;

	m_flNextRadarTime = 0;
	m_vOldPos = Vector(9999, 9999, 9999);

	UTIL_SetOrigin(pev, m_vStart);
	UTIL_SetSize(pev, VEC_HOSTAGE_HULL_MIN, VEC_HOSTAGE_HULL_MAX);

	DROP_TO_FLOOR(edict());
	SetActivity(ACT_IDLE);

	SetThink(&CHostage::IdleThink);
	pev->nextthink = gpGlobals->time + RANDOM_FLOAT(0.1, 0.2);

	m_fHasPath = FALSE;
	m_nTargetNode = NODE_INVALID_EMPTY;

	m_flLastPathCheck = -1;
	m_flPathAcquired = -1;
	m_flPathCheckInterval = 0.1f;
	m_flNextFullThink = gpGlobals->time + RANDOM_FLOAT(0.1, 0.2);
}

bool CHostage::CanTakeDamage(entvars_t *pevAttacker)
{
	bool bCanTakeDmg = true; // default behaviour

#ifdef REGAMEDLL_ADD
	CBasePlayer *pAttacker = CBasePlayer::Instance(pevAttacker);
	switch ((int)hostagehurtable.value)
	{
	case 0:
		bCanTakeDmg = false;
		break;
	case 2:
		bCanTakeDmg = (pAttacker && pAttacker->IsPlayer() && pAttacker->m_iTeam == CT);
		break;
	case 3:
		bCanTakeDmg = (pAttacker && pAttacker->IsPlayer() && pAttacker->m_iTeam == TERRORIST);
		break;
	default:
		break;
	}
#endif

	return bCanTakeDmg;
}

void CHostage::TraceAttack(entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int bitsDamageType)
{
	if (!CanTakeDamage(pevAttacker))
		return;

	CBaseMonster::TraceAttack(pevAttacker, flDamage, vecDir, ptr, bitsDamageType);
}

BOOL CHostage::TakeDamage(entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, int bitsDamageType)
{
#ifdef REGAMEDLL_ADD
	if (!CanTakeDamage(pevAttacker))
		return FALSE;
#endif

	float flActualDamage = GetModifiedDamage(flDamage, m_LastHitGroup);

	if (flActualDamage > pev->health)
		flActualDamage = pev->health;

	pev->health -= flActualDamage;

	if (m_improv)
	{
		m_improv->OnInjury(flActualDamage);
	}

	PlayPainSound();

	CBasePlayer *pAttacker = nullptr;
	if (pevAttacker)
	{
		CBaseEntity *pAttackingEnt = GetClassPtr<CCSEntity>((CBaseEntity *)pevAttacker);
		if (pAttackingEnt->Classify() == CLASS_VEHICLE)
		{
			CBaseEntity *pDriver = ((CFuncVehicle *)pAttackingEnt)->m_pDriver;
			if (pDriver)
			{
				pevAttacker = pDriver->pev;
			}
		}

		if (pAttackingEnt->IsPlayer())
		{
			pAttacker = GetClassPtr<CCSPlayer>((CBasePlayer *)pevAttacker);
		}
	}

	if (pev->health > 0.0f)
	{
		m_flFlinchTime = gpGlobals->time + 0.75f;
		SetFlinchActivity();

		if (pAttacker)
		{
			pAttacker->AddAccount(-20 * int(flActualDamage), RT_HOSTAGE_DAMAGED);

			if (TheBots)
			{
				TheBots->OnEvent(EVENT_HOSTAGE_DAMAGED, this, pAttacker);
			}

			ClientPrint(pAttacker->pev, HUD_PRINTCENTER, "#Injured_Hostage");
			if (!(pAttacker->m_flDisplayHistory & DHF_HOSTAGE_INJURED))
			{
				pAttacker->HintMessage("#Hint_careful_around_hostages");
				pAttacker->m_flDisplayHistory |= DHF_HOSTAGE_INJURED;
			}

			return TRUE;
		}
	}
	else
	{
		pev->health = 0;
		pev->movetype = MOVETYPE_TOSS;
		pev->flags &= ~FL_ONGROUND;
		SetDeathActivity();

		if (pAttacker)
		{
			pAttacker->AddAccount(20 * (-25 - int(flActualDamage)), RT_HOSTAGE_KILLED);
			AnnounceDeath(pAttacker);
			ApplyHostagePenalty(pAttacker);
		}

		pev->takedamage = DAMAGE_NO;
		pev->deadflag = DEAD_DEAD;
		pev->solid = SOLID_NOT;

		if (TheBots)
		{
			TheBots->OnEvent(EVENT_HOSTAGE_KILLED, this, pAttacker);
		}

		if (m_improv)
		{
			m_improv->Chatter(HOSTAGE_CHATTER_DEATH_CRY);
		}

		CSGameRules()->CheckWinConditions();

		if (!CSGameRules()->m_flRestartRoundTime)
			SendHostageEventMsg();

		pev->nextthink = gpGlobals->time + 3.0f;
		SetThink(&CHostage::Remove);
	}

	return FALSE;
}

float CHostage::GetModifiedDamage(float flDamage, int nHitGroup)
{
	switch (nHitGroup)
	{
	case HITGROUP_GENERIC: flDamage *= 1.75; break;
	case HITGROUP_HEAD: flDamage *= 2.5; break;
	case HITGROUP_CHEST: flDamage *= 1.5; break;
	case HITGROUP_STOMACH: flDamage *= 1.75; break;
	case HITGROUP_LEFTARM:
	case HITGROUP_RIGHTARM: flDamage *= 0.75; break;
	case HITGROUP_LEFTLEG:
	case HITGROUP_RIGHTLEG: flDamage *= 0.6; break;
	default: flDamage *= 1.5; break;
	}

	return flDamage;
}

void CHostage::PlayPainSound()
{
	if (m_LastHitGroup != HITGROUP_HEAD)
		return;

	switch (RANDOM_LONG(0, 1))
	{
	case 0: EMIT_SOUND(edict(), CHAN_VOICE, "player/headshot1.wav", VOL_NORM, ATTN_NORM); break;
	case 1: EMIT_SOUND(edict(), CHAN_VOICE, "player/headshot2.wav", VOL_NORM, ATTN_NORM); break;
	}
}

void CHostage::SetFlinchActivity()
{
	Activity activity = ACT_SMALL_FLINCH;

	if (m_improv)
	{
		m_improv->Flinch(activity);
		return;
	}

	SetActivity(activity);
}

void CHostage::SetDeathActivity()
{
	if (m_improv && m_improv->IsCrouching())
	{
		m_improv->CrouchDie();
		return;
	}

	if (AreImprovAllowed())
	{
		switch (m_LastHitGroup)
		{
		case HITGROUP_GENERIC:
		case HITGROUP_LEFTARM:
		case HITGROUP_RIGHTARM:
		case HITGROUP_LEFTLEG:
		case HITGROUP_RIGHTLEG:
			SetActivity(ACT_DIESIMPLE);
			break;
		case HITGROUP_HEAD:
			SetActivity(ACT_DIE_HEADSHOT);
			break;
		case HITGROUP_CHEST:
			SetActivity(ACT_DIE_CHESTSHOT);
			break;
		case HITGROUP_STOMACH:
			SetActivity(ACT_DIE_GUTSHOT);
			break;
		}

		return;
	}

	// for CS 1.6
	switch (m_LastHitGroup)
	{
	case HITGROUP_GENERIC:
	case HITGROUP_HEAD:
		SetActivity(ACT_DIE_HEADSHOT);
		break;
	case HITGROUP_CHEST:
	case HITGROUP_RIGHTARM:
		SetActivity(ACT_DIESIMPLE);
		break;
	case HITGROUP_STOMACH:
	case HITGROUP_RIGHTLEG:
		SetActivity(ACT_DIEFORWARD);
		break;
	case HITGROUP_LEFTARM:
	case HITGROUP_LEFTLEG:
		SetActivity(ACT_DIEBACKWARD);
		break;
	}
}

void CHostage::AnnounceDeath(CBasePlayer *pAttacker)
{
	ClientPrint(pAttacker->pev, HUD_PRINTCENTER, "#Killed_Hostage");

	if (!(pAttacker->m_flDisplayHistory & DHF_HOSTAGE_KILLED))
	{
		pAttacker->HintMessage("#Hint_lost_money");
		pAttacker->m_flDisplayHistory |= DHF_HOSTAGE_KILLED;
	}

	if (!g_pGameRules->IsMultiplayer())
	{
		CHalfLifeTraining::HostageDied();
	}

	UTIL_LogPrintf("\"%s<%i><%s><%s>\" triggered \"Killed_A_Hostage\"\n", STRING(pAttacker->pev->netname), GETPLAYERUSERID(pAttacker->edict()),
		GETPLAYERAUTHID(pAttacker->edict()), GetTeam(pAttacker->m_iTeam));

	MESSAGE_BEGIN(MSG_SPEC, SVC_DIRECTOR);
		WRITE_BYTE(9);
		WRITE_BYTE(DRC_CMD_EVENT);
		WRITE_SHORT(ENTINDEX(pAttacker->edict()));
		WRITE_SHORT(ENTINDEX(edict()));
		WRITE_LONG(15);
	MESSAGE_END();
}

void CHostage::ApplyHostagePenalty(CBasePlayer *pAttacker)
{
	if (pAttacker->m_iTeam != TERRORIST)
		return;

	int iHostagePenalty = int(CVAR_GET_FLOAT("mp_hostagepenalty"));
	if (iHostagePenalty)
	{
		if (pAttacker->m_iHostagesKilled++ == iHostagePenalty)
		{
			pAttacker->HintMessage("#Hint_removed_for_next_hostage_killed", TRUE);
		}
		else if (pAttacker->m_iHostagesKilled >= iHostagePenalty)
		{
#ifdef REGAMEDLL_FIXES
			SERVER_COMMAND(UTIL_VarArgs("kick #%d \"For killing too many hostages\"\n", GETPLAYERUSERID(pAttacker->edict())));
#else
			CLIENT_COMMAND(pAttacker->edict(), "disconnect\n");
#endif
		}
	}
}

void CHostage::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	if (!pActivator->IsPlayer())
		return;

#ifdef REGAMEDLL_FIXES
	if (!IsAlive())
		return;
#else
	if (pev->takedamage == DAMAGE_NO)
		return;
#endif

	CBasePlayer *pPlayer = (CBasePlayer *)pActivator;
	if (pPlayer->m_iTeam != CT)
	{
		if (!(pPlayer->m_flDisplayHistory & DHF_HOSTAGE_CTMOVE))
		{
			pPlayer->m_flDisplayHistory |= DHF_HOSTAGE_CTMOVE;
			pPlayer->HintMessage("#Only_CT_Can_Move_Hostages", FALSE, TRUE);
		}

		return;
	}

	if (gpGlobals->time >= m_flNextChange)
	{
		m_flNextChange = gpGlobals->time + 1.0f;

		if (m_improv)
		{
			if (m_improv->IsFollowing() && pActivator == m_improv->GetFollowLeader())
			{
				m_improv->Agree();
				m_improv->Idle();
				m_improv->Chatter(HOSTAGE_CHATTER_STOP_FOLLOW);
			}
			else
			{
				m_improv->Follow(pPlayer);

				if (TheBots)
				{
					TheBots->OnEvent(EVENT_HOSTAGE_USED, pActivator);
				}
			}
		}
		else
		{
			m_flPathAcquired = gpGlobals->time;

			if (pActivator != m_hTargetEnt)
			{
				m_State = FOLLOW;
				m_hTargetEnt = pActivator;
				m_hStoppedTargetEnt = nullptr;
			}
			else if (m_State == FOLLOW)
			{
				m_State = STAND;
				m_hTargetEnt = nullptr;
				m_hStoppedTargetEnt = static_cast<CBasePlayer *>(pActivator);
			}
			else
				m_State = FOLLOW;

			if (m_State == FOLLOW)
			{
				PlayFollowRescueSound();
				if (TheBots)
				{
					TheBots->OnEvent(EVENT_HOSTAGE_USED, pActivator);
				}
			}
		}

		GiveCTTouchBonus(pPlayer);
		pPlayer->HostageUsed();
	}
}

void CHostage::PlayFollowRescueSound()
{
	switch (RANDOM_LONG(0, 4))
	{
	case 0: EMIT_SOUND(ENT(pev), CHAN_VOICE, "hostage/hos1.wav", VOL_NORM, ATTN_NORM); break;
	case 1: EMIT_SOUND(ENT(pev), CHAN_VOICE, "hostage/hos2.wav", VOL_NORM, ATTN_NORM); break;
	case 2: EMIT_SOUND(ENT(pev), CHAN_VOICE, "hostage/hos3.wav", VOL_NORM, ATTN_NORM); break;
	case 3: EMIT_SOUND(ENT(pev), CHAN_VOICE, "hostage/hos4.wav", VOL_NORM, ATTN_NORM); break;
	case 4: EMIT_SOUND(ENT(pev), CHAN_VOICE, "hostage/hos5.wav", VOL_NORM, ATTN_NORM); break;
	}
}

void CHostage::GiveCTTouchBonus(CBasePlayer *pPlayer)
{
	if (m_bTouched)
		return;

	m_bTouched = TRUE;
	CSGameRules()->m_iAccountCT += CSGameRules()->m_rgRewardAccountRules[RR_TOOK_HOSTAGE_ACC];

	pPlayer->AddAccount(CSGameRules()->m_rgRewardAccountRules[RR_TOOK_HOSTAGE], RT_HOSTAGE_TOOK);
	UTIL_LogPrintf("\"%s<%i><%s><CT>\" triggered \"Touched_A_Hostage\"\n", STRING(pPlayer->pev->netname), GETPLAYERUSERID(pPlayer->edict()), GETPLAYERAUTHID(pPlayer->edict()));
}

int CHostage::ObjectCaps()
{
	return (CBaseMonster::ObjectCaps() | FCAP_MUST_SPAWN | FCAP_ONOFF_USE);
}

void CHostage::Touch(CBaseEntity *pOther)
{
	Vector2D vPush;
	const float pushForce = 50.0f;

	if (m_improv)
	{
		m_improv->OnTouch(pOther);
		return;
	}

	CBasePlayer *pPlayer = (CBasePlayer *)pOther;
	if (pPlayer->IsPlayer())
	{
		if (pPlayer->m_iTeam != CT)
			return;
	}
	else
	{
		if (!FClassnameIs(pPlayer->pev, "hostage_entity"))
			return;
	}

	vPush = (pev->origin - pOther->pev->origin).Make2D();

#ifndef PLAY_GAMEDLL
	vPush = vPush.Normalize() * pushForce;

	pev->velocity.x += vPush.x;
	pev->velocity.y += vPush.y;
#else
	// TODO: fix test demo
	pev->velocity = pev->velocity + NormalizeMulScalar<real_t, real_t, float>(vPush, pushForce);
#endif
}

void CHostage::DoFollow()
{
	CBaseEntity *pFollowing;
	Vector vecDest;
	float flRadius = 0;
	float flDistToDest;

	if (!m_hTargetEnt)
		return;

	if (cv_hostage_stop.value > 0.0f)
	{
		m_State = STAND;
		m_hTargetEnt = nullptr;
		m_hStoppedTargetEnt = nullptr;
		return;
	}

	pFollowing = GetClassPtr<CCSEntity>((CBaseEntity *)m_hTargetEnt->pev);
	m_LocalNav->SetTargetEnt(pFollowing);

	vecDest = pFollowing->pev->origin;
	vecDest.z += pFollowing->pev->mins.z;
	flDistToDest = (vecDest - pev->origin).Length();

	if (flDistToDest < 80.0f && (m_fHasPath || m_LocalNav->PathTraversable(pev->origin, vecDest, TRUE)))
		return;

	if (pev->flags & FL_ONGROUND)
	{
		if (m_flPathCheckInterval + m_flLastPathCheck < gpGlobals->time)
		{
			if (!m_fHasPath || pFollowing->pev->velocity.Length2D() > 1.0f)
			{
				m_flLastPathCheck = gpGlobals->time;
				m_LocalNav->RequestNav(this);
			}
		}
	}

	if (m_fHasPath)
	{
		m_nTargetNode = m_LocalNav->GetFurthestTraversableNode(pev->origin, vecNodes, m_nPathNodes, TRUE);

		if (!m_nTargetNode)
		{
			if ((vecNodes[m_nTargetNode] - pev->origin).Length2D() < HOSTAGE_STEPSIZE)
				m_nTargetNode = NODE_INVALID_EMPTY;
		}

		if (m_nTargetNode == NODE_INVALID_EMPTY)
		{
			m_fHasPath = FALSE;
			m_flPathCheckInterval = 0.1f;
		}
	}

	if (gpGlobals->time < m_flFlinchTime)
		return;

	if (m_nTargetNode != NODE_INVALID_EMPTY)
	{
		if (pev->flags & FL_ONGROUND)
			PointAt(vecNodes[m_nTargetNode]);

		if (pev->movetype == MOVETYPE_FLY)
			pev->v_angle.x = -60;

		MoveToward(vecNodes[m_nTargetNode]);
		m_bStuck = FALSE;
	}
	else if (IsAlive())
	{
		if (IsFollowingSomeone())
		{
			if (!m_bStuck && flDistToDest > 200.0f)
			{
				m_bStuck = TRUE;
				m_flStuckTime = gpGlobals->time;
			}
		}
	}

	if (pev->flags & FL_ONGROUND)
	{
		if (m_flPathAcquired != -1 && m_flPathAcquired + 2 > gpGlobals->time)
		{
			if (pev->velocity.Length2D() < 1 || m_nTargetNode == NODE_INVALID_EMPTY)
			{
				Wiggle();
			}
		}
	}
}

void CHostage::PointAt(const Vector &vecLoc)
{
	pev->angles.x = 0;
	pev->angles.y = UTIL_VecToAngles(vecLoc - pev->origin).y;
	pev->angles.z = 0;
}

void CHostage::MoveToward(const Vector &vecLoc)
{
	Vector vecFwd;
	Vector vecbigDest;
	Vector vecMove;
	CBaseEntity *pFollowing;
	real_t flDist;

	pFollowing = GetClassPtr<CCSEntity>((CBaseEntity *)m_hTargetEnt->pev);
	vecMove = vecLoc - pev->origin;

	Vector vecAng(0, UTIL_VecToAngles(vecMove).y, 0);
	UTIL_MakeVectorsPrivate(vecAng, vecFwd, nullptr, nullptr);

	if ((vecFwd * m_LocalNav->m_flStepSize).Length2D() <= (vecLoc - pev->origin).Length2D())
		flDist = (vecFwd * m_LocalNav->m_flStepSize).Length2D();
	else
		flDist = (vecLoc - pev->origin).Length2D();

	vecbigDest = pev->origin + (vecFwd * flDist);

	auto nFwdMove = m_LocalNav->PathTraversable(pev->origin, vecbigDest, FALSE);
	if (nFwdMove != PTRAVELS_EMPTY)
	{
		real_t flSpeed = 250;

		vecbigDest = pFollowing->pev->origin;
		vecbigDest.z += pFollowing->pev->mins.z;

		if (pev->flags & FL_ONGROUND)
		{
			flSpeed = (vecbigDest - pev->origin).Length();

			if (flSpeed >= 110)
			{
				if (flSpeed >= 250)
					flSpeed = 400;
				else
					flSpeed = 300;
			}
		}

		pev->velocity.x = vecFwd.x * flSpeed;
		pev->velocity.y = vecFwd.y * flSpeed;

		if (nFwdMove == PTRAVELS_STEPJUMPABLE)
		{
			if (pev->flags & FL_ONGROUND)
			{
				pev->velocity.z = 270;
			}
		}
	}
}

BOOL CHostage::IsOnLadder()
{
	return pev->movetype == MOVETYPE_FLY;
}

void CHostage::NavReady()
{
	CBaseEntity *pFollowing;
	Vector vecDest;
	float flRadius = 40.0f;

	if (!m_hTargetEnt)
	{
		return;
	}

	pFollowing = GetClassPtr<CCSEntity>((CBaseEntity *)m_hTargetEnt->pev);
	vecDest = pFollowing->pev->origin;

	if (!(pFollowing->pev->flags & FL_ONGROUND))
	{
		TraceResult tr;
		Vector vecDropDest = (pFollowing->pev->origin - Vector(0, 0, 300));
		UTIL_TraceHull(vecDest, vecDropDest, ignore_monsters, human_hull, pFollowing->edict(), &tr);

		if (tr.fStartSolid || tr.flFraction == 1.0f)
		{
			return;
		}

		vecDest = tr.vecEndPos;
	}

	vecDest.z += pFollowing->pev->mins.z;
	m_LocalNav->SetTargetEnt(pFollowing);

	node_index_t nindexPath = m_LocalNav->FindPath(pev->origin, vecDest, flRadius, TRUE);
	if (nindexPath == NODE_INVALID_EMPTY)
	{
		if (!m_fHasPath)
		{
			m_flPathCheckInterval += 0.1f;

			if (m_flPathCheckInterval >= 0.5f)
			{
				m_flPathCheckInterval = 0.5f;
			}
		}
	}
	else
	{
		m_fHasPath = TRUE;
		m_nTargetNode = NODE_INVALID_EMPTY;
		m_flPathAcquired = gpGlobals->time;
		m_flPathCheckInterval = 0.5f;

		m_nPathNodes = m_LocalNav->SetupPathNodes(nindexPath, vecNodes, 1);
	}
}

void CHostage::SendHostagePositionMsg()
{
	CBaseEntity *pEntity = nullptr;
	while ((pEntity = UTIL_FindEntityByClassname(pEntity, "player")))
	{
		if (FNullEnt(pEntity->edict()))
			break;

		if (!pEntity->IsPlayer())
			continue;

		if (pEntity->pev->flags == FL_DORMANT)
			continue;

		CBasePlayer *pTempPlayer = GetClassPtr<CCSPlayer>((CBasePlayer *)pEntity->pev);

		if (pTempPlayer->pev->deadflag == DEAD_NO && pTempPlayer->m_iTeam == CT)
		{
			MESSAGE_BEGIN(MSG_ONE, gmsgHostagePos, nullptr, pTempPlayer->pev);
				WRITE_BYTE(0);
				WRITE_BYTE(m_iHostageIndex);
				WRITE_COORD(pev->origin.x);
				WRITE_COORD(pev->origin.y);
				WRITE_COORD(pev->origin.z);
			MESSAGE_END();
		}
	}
}

void CHostage::SendHostageEventMsg()
{
	CBaseEntity *pEntity = nullptr;
	while ((pEntity = UTIL_FindEntityByClassname(pEntity, "player")))
	{
		if (FNullEnt(pEntity->edict()))
			break;

		if (!pEntity->IsPlayer())
			continue;

		if (pEntity->pev->flags == FL_DORMANT)
			continue;

		CBasePlayer *pTempPlayer = GetClassPtr<CCSPlayer>((CBasePlayer *)pEntity->pev);

		if (pTempPlayer->pev->deadflag == DEAD_NO && pTempPlayer->m_iTeam == CT)
		{
			MESSAGE_BEGIN(MSG_ONE, gmsgHostageK, nullptr, pTempPlayer->pev);
				WRITE_BYTE(m_iHostageIndex);
			MESSAGE_END();
		}

		if (pTempPlayer->pev->deadflag == DEAD_NO)
			pTempPlayer->SendHostageIcons();
	}
}

void CHostage::Wiggle()
{
	Vector vec(0, 0, 0);
	Vector wiggle_directions[] =
	{
		Vector(50, 0, 0),
		Vector(-50, 0, 0),
		Vector(0, 50, 0),
		Vector(0, -50, 0),
		Vector(50, 50, 0),
		Vector(50, -50, 0),
		Vector(-50, 50, 0),
		Vector(-50, -50, 0)
	};

	for (auto& dir : wiggle_directions) {
		Vector dest = pev->origin + dir;
		if (m_LocalNav->PathTraversable(pev->origin, dest, TRUE) == PTRAVELS_EMPTY)
			vec = vec - dir;
	}

#ifndef PLAY_GAMEDLL
	vec = vec + Vector(RANDOM_FLOAT(-3, 3), RANDOM_FLOAT(-3, 3), 0);
#else
	// TODO: fix test demo
	vec.y = vec.y + RANDOM_FLOAT(-3.0, 3.0);
	vec.x = vec.x + RANDOM_FLOAT(-3.0, 3.0);

#endif

	pev->velocity = pev->velocity + (vec.Normalize() * 100);
}

void CHostage::PreThink()
{
	Vector vecSrc;
	Vector vecDest;
	TraceResult tr;
	float flOrigDist;
	float flRaisedDist;
	float flInterval;

	if (m_improv)
	{
		return;
	}

	if (!(pev->flags & FL_ONGROUND))
	{
		return;
	}

	if (pev->velocity.Length2D() < 1)
	{
		return;
	}

	vecSrc = pev->origin;

	flInterval = m_LocalNav->m_flStepSize;
	vecDest = vecSrc + pev->velocity * gpGlobals->frametime;
	vecDest.z = vecSrc.z;

	TRACE_MONSTER_HULL(edict(), vecSrc, vecDest, dont_ignore_monsters, edict(), &tr);

	if (tr.fStartSolid || tr.flFraction == 1.0f || tr.vecPlaneNormal.z > MaxUnitZSlope)
	{
		return;
	}

	flOrigDist = (tr.vecEndPos - pev->origin).Length2D();
	vecSrc.z += flInterval;
	vecDest = vecSrc + (pev->velocity.Normalize() * 0.1f);
	vecDest.z = vecSrc.z;

	TRACE_MONSTER_HULL(edict(), vecSrc, vecDest, dont_ignore_monsters, edict(), &tr);

	if (tr.fStartSolid)
	{
		return;
	}

	vecSrc = tr.vecEndPos;
	vecDest = tr.vecEndPos;
	vecDest.z -= flInterval;

	TRACE_MONSTER_HULL(edict(), vecSrc, vecDest, dont_ignore_monsters, edict(), &tr);

	if (tr.vecPlaneNormal.z < MaxUnitZSlope)
	{
		return;
	}

	flRaisedDist = (tr.vecEndPos - pev->origin).Length2D();

	if (flRaisedDist > flOrigDist)
	{
		Vector vecNewOrigin(pev->origin);
		vecNewOrigin.z = tr.vecEndPos.z;

		UTIL_SetOrigin(pev, vecNewOrigin);
		pev->velocity.z += pev->gravity * g_psv_gravity->value * gpGlobals->frametime;
	}
}

void Hostage_RegisterCVars()
{
// These cvars are only used in czero
#ifdef REGAMEDLL_FIXES
	if (!AreImprovAllowed())
		return;
#endif

	CVAR_REGISTER(&cv_hostage_debug);
	CVAR_REGISTER(&cv_hostage_stop);
}

void InstallHostageManager()
{
	if (g_pHostages)
	{
		delete g_pHostages;
		g_pHostages = nullptr;
	}

	g_pHostages = new CHostageManager;
}

CHostageManager::CHostageManager()
{
	Q_memset(&m_chatter, 0, sizeof(m_chatter));
	m_hostageCount = 0;
}

void CHostageManager::ServerActivate()
{
	m_hostageCount = 0;

	CHostage *pHostage = nullptr;
	while ((pHostage = UTIL_FindEntityByClassname(pHostage, "hostage_entity")))
	{
		AddHostage(pHostage);
	}

	if (AreImprovAllowed())
	{
		for (auto& snd : hostageSoundStruct) {
			m_chatter.AddSound(snd.type, snd.fileName);
		}

#ifdef REGAMEDLL_ADD
		if (!AreRunningCZero()) {
			LoadNavigationMap();
		}
#endif
	}
}

void CHostageManager::ServerDeactivate()
{
	;
}

void CHostageManager::RestartRound()
{
	for (int i = 0; i < m_hostageCount; i++)
	{
		if (m_hostage[i]->m_improv)
		{
			m_hostage[i]->m_improv->OnReset();
		}
	}
}

void CHostageManager::AddHostage(CHostage *hostage)
{
	if (m_hostageCount >= MAX_HOSTAGES)
		return;

	int i;
	for (i = 0; i < m_hostageCount; i++)
	{
		if (m_hostage[i] == hostage)
		{
			break;
		}
	}

	if (i == m_hostageCount)
	{
		m_hostage[m_hostageCount] = hostage;
		m_hostageCount++;
	}
}

bool CHostageManager::IsNearbyHostageTalking(CHostageImprov *improv)
{
	for (int i = 0; i < m_hostageCount; i++)
	{
		const float closeRange = 500.0f;
		const CHostageImprov *pHostage = m_hostage[i]->m_improv;

		if (!pHostage)
			continue;

		if (!pHostage->IsAlive() || pHostage == improv)
			continue;

		if (!(improv->GetCentroid() - pHostage->GetCentroid()).IsLengthGreaterThan(closeRange) && !pHostage->IsTalking())
		{
			return true;
		}
	}

	return false;
}

bool CHostageManager::IsNearbyHostageJumping(CHostageImprov *improv)
{
	for (int i = 0; i < m_hostageCount; i++)
	{
		const CHostageImprov *pHostage = m_hostage[i]->m_improv;

		if (!pHostage)
			continue;

		if (!pHostage->IsAlive() || pHostage == improv)
			continue;

		const float closeRange = 500.0f;
		if (!(improv->GetCentroid() - pHostage->GetCentroid()).IsLengthGreaterThan(closeRange) && pHostage->IsJumping())
		{
			return true;
		}
	}

	return false;
}

void CHostageManager::OnEvent(GameEventType event, CBaseEntity *pEntity, CBaseEntity *pOther)
{
	for (int i = 0; i < m_hostageCount; i++)
	{
		CHostageImprov *improv = m_hostage[i]->m_improv;
		if (improv)
		{
			improv->OnGameEvent(event, pEntity, pOther);
		}
	}
}

SimpleChatter::SimpleChatter()
{
	for (auto& chatter : m_chatter)
	{
		chatter.count = 0;
		chatter.index = 0;
		chatter.needsShuffle = false;
	}
}

SimpleChatter::~SimpleChatter()
{
	for (auto& chatter : m_chatter)
	{
		for (int f = 0; f < chatter.count; f++)
		{
			delete[] chatter.file[f].filename;
			chatter.file[f].filename = nullptr;
		}
	}
}

void SimpleChatter::AddSound(HostageChatterType type, char *filename)
{
	char actualFilename[128];
	auto chatter = &m_chatter[type];

	Q_snprintf(actualFilename, sizeof(actualFilename), "sound\\%s", filename);

	chatter->file[chatter->count].filename = CloneString(filename);
	chatter->file[chatter->count].duration = (double)GET_APPROX_WAVE_PLAY_LEN(actualFilename) / 1000.0;

	chatter->needsShuffle = true;
	chatter->count++;

	PRECACHE_SOUND(filename);
}

void SimpleChatter::Shuffle(ChatterSet *chatter)
{
	if (!chatter->needsShuffle)
		return;

	for (int i = 1; i < chatter->count; i++)
	{
		for (int j = i; j < chatter->count; j++)
		{
			if (RANDOM_LONG(0, 100) < 50)
			{
				SoundFile tmp;
				tmp.filename = chatter->file[i - 1].filename;
				tmp.duration = chatter->file[i - 1].duration;

				chatter->file[i - 1] = chatter->file[j];
				chatter->file[j].filename = tmp.filename;
				chatter->file[j].duration = tmp.duration;
			}
		}
	}

	chatter->needsShuffle = false;
}

char *SimpleChatter::GetSound(HostageChatterType type, float *duration)
{
	ChatterSet *chatter = &m_chatter[type];
	char *sound;

	Shuffle(chatter);
	sound = chatter->file[chatter->index].filename;
	*duration = chatter->file[chatter->index].duration;

	if (++chatter->index >= chatter->count)
	{
		chatter->index = 0;
	}

	return sound;
}

float SimpleChatter::PlaySound(CBaseEntity *pEntity, HostageChatterType type)
{
	float duration;
	char *pszSoundName = GetSound(type, &duration);
	CHostage *pHostage = static_cast<CHostage *>(pEntity);

	if (!pszSoundName)
	{
		return 0;
	}

	int pitch;
	int attenuation = 1;

	switch (pHostage->m_whichModel)
	{
	case CHostage::REGULAR_GUY:
		pitch = 92;
		break;
	case CHostage::BLACK_GUY:
		pitch = 86;
		break;
	case CHostage::GOOFY_GUY:
		pitch = 100;
		break;
	case CHostage::OLD_GUY:
	default:
		pitch = 88;
		break;
	}

	EMIT_SOUND_DYN(ENT(pHostage->pev), CHAN_VOICE, pszSoundName, VOL_NORM, attenuation, 0, pitch);

	if (type == HOSTAGE_CHATTER_CALL_TO_RESCUER)
	{
		if (TheBots)
		{
			TheBots->OnEvent(EVENT_HOSTAGE_CALLED_FOR_HELP, pHostage);
		}
	}

	return duration;
}
