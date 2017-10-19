/*
*
*    This program is free software; you can redistribute it and/or modify it
*    under the terms of the GNU General Public License as published by the
*    Free Software Foundation; either version 2 of the License, or (at
*    your option) any later version.
*
*    This program is distributed in the hope that it will be useful, but
*    WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*    General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program; if not, write to the Free Software Foundation,
*    Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*    In addition, as a special exception, the author gives permission to
*    link the code of this program with the Half-Life Game Engine ("HL
*    Engine") and Modified Game Libraries ("MODs") developed by Valve,
*    L.L.C ("Valve").  You must obey the GNU General Public License in all
*    respects for all of the code used other than the HL Engine and MODs
*    from Valve.  If you modify this file, you may extend this exception
*    to your version of the file, but you are not obligated to do so.  If
*    you do not wish to do so, delete this exception statement from your
*    version.
*
*/

#include "precompiled.h"

class CDummyWeaponClass:
	public CAK47, public CAUG, public CAWP, public CC4,
	public CDEAGLE, public CELITE, public CFamas, public CFiveSeven,
	public CFlashbang, public CG3SG1, public CGalil, public CGLOCK18,
	public CHEGrenade, public CKnife, public CM3, public CM4A1,
	public CM249, public CMAC10, public CMP5N, public CP90,
	public CP228, public CSCOUT, public CSG550, public CSG552,
	public CSmokeGrenade, public CTMP, public CUMP45, public CUSP,
	public CXM1014
{
public:
	virtual void Precache() {};
	virtual int Save(CSave &save) { return 0; };
	virtual int Restore(CRestore &restore) { return 0; };
	virtual int AddToPlayer(CBasePlayer *pPlayer) { return 0; };
	virtual int AddDuplicate(CBasePlayerItem *pItem) { return 0; };
	virtual BOOL CanDeploy() { return FALSE; };
	virtual BOOL IsWeapon() { return TRUE; }
	virtual void Holster(int skiplocal = 0) {};
	virtual void UpdateItemInfo() {};
	virtual void ItemPostFrame() {};
	virtual int PrimaryAmmoIndex() { return 0; };
	virtual int SecondaryAmmoIndex() { return 0; };
	virtual int UpdateClientData(CBasePlayer *pPlayer) { return 0; };
	virtual CBasePlayerItem *GetWeaponPtr() { return nullptr; }
	virtual int ExtractAmmo(CBasePlayerWeapon *pWeapon) { return 0; };
	virtual int ExtractClipAmmo(CBasePlayerWeapon *pWeapon) { return 0; };
	virtual int AddWeapon() { return 0; }
	virtual BOOL PlayEmptySound() { return FALSE; };
	virtual void ResetEmptySound() {};
	virtual void SendWeaponAnim(int iAnim, int skiplocal = 0) {};
	virtual BOOL IsUseable() { return FALSE; };
	virtual void PrimaryAttack() {};
	virtual void SecondaryAttack() {};
	virtual void Reload() {};
	virtual void WeaponIdle() {};
	virtual void RetireWeapon() {};
	virtual BOOL ShouldWeaponIdle() { return FALSE; }
	virtual BOOL UseDecrement() { return FALSE; }
};

class CDummyWeaponClassExtra:
	public CDummyWeaponClass
{
public:
	virtual void Precache() {};
	virtual int Save(CSave &save) { return 0; };
	virtual int Restore(CRestore &restore) { return 0; };
	virtual int AddToPlayer(CBasePlayer *pPlayer) { return 0; };
	virtual int AddDuplicate(CBasePlayerItem *pItem) { return 0; };
	virtual BOOL CanDeploy() { return FALSE; };
	virtual BOOL IsWeapon() { return TRUE; }
	virtual void Holster(int skiplocal = 0) {};
	virtual void UpdateItemInfo() {};
	virtual void ItemPostFrame() {};
	virtual int PrimaryAmmoIndex() { return 0; };
	virtual int SecondaryAmmoIndex() { return 0; };
	virtual int UpdateClientData(CBasePlayer *pPlayer) { return 0; };
	virtual CBasePlayerItem *GetWeaponPtr() { return nullptr; }
	virtual int ExtractAmmo(CBasePlayerWeapon *pWeapon) { return 0; };
	virtual int ExtractClipAmmo(CBasePlayerWeapon *pWeapon) { return 0; };
	virtual int AddWeapon() { return 0; }
	virtual BOOL PlayEmptySound() { return FALSE; };
	virtual void ResetEmptySound() {};
	virtual void SendWeaponAnim(int iAnim, int skiplocal = 0) {};
	virtual BOOL IsUseable() { return FALSE; };
	virtual void PrimaryAttack() {};
	virtual void SecondaryAttack() {};
	virtual void Reload() {};
	virtual void WeaponIdle() {};
	virtual void RetireWeapon() {};
	virtual BOOL ShouldWeaponIdle() { return FALSE; }
	virtual BOOL UseDecrement() { return FALSE; }
};

volatile CDummyWeaponClass *g_pDummyWeaponClass = &CDummyWeaponClass();
volatile CDummyWeaponClassExtra *g_pCDummyWeaponClassExtra = &CDummyWeaponClassExtra();
