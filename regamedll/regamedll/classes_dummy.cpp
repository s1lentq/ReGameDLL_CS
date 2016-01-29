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
	virtual void Precache(void) {};
	virtual int Save(CSave &save) { return 0; };
	virtual int Restore(CRestore &restore) { return 0; };
	virtual int AddToPlayer(CBasePlayer *pPlayer) { return 0; };
	virtual int AddDuplicate(CBasePlayerItem *pItem) { return 0; };
	virtual BOOL CanDeploy(void) { return FALSE; };
	virtual BOOL IsWeapon(void) { return TRUE; }
	virtual void Holster(int skiplocal = 0) {};
	virtual void UpdateItemInfo(void) {};
	virtual void ItemPostFrame(void) {};
	virtual int PrimaryAmmoIndex(void) { return 0; };
	virtual int SecondaryAmmoIndex(void) { return 0; };
	virtual int UpdateClientData(CBasePlayer *pPlayer) { return 0; };
	virtual CBasePlayerItem *GetWeaponPtr(void) { return NULL; }
	virtual int ExtractAmmo(CBasePlayerWeapon *pWeapon) { return 0; };
	virtual int ExtractClipAmmo(CBasePlayerWeapon *pWeapon) { return 0; };
	virtual int AddWeapon(void) { return 0; }
	virtual BOOL PlayEmptySound(void) { return FALSE; };
	virtual void ResetEmptySound(void) {};
	virtual void SendWeaponAnim(int iAnim, int skiplocal = 0) {};
	virtual BOOL IsUseable(void) { return FALSE; };
	virtual void PrimaryAttack(void) {};
	virtual void SecondaryAttack(void) {};
	virtual void Reload(void) {};
	virtual void WeaponIdle(void) {};
	virtual void RetireWeapon(void) {};
	virtual BOOL ShouldWeaponIdle(void) { return FALSE; }
	virtual BOOL UseDecrement(void) { return FALSE; }
};

class CDummyWeaponClassExtra:
	public CDummyWeaponClass
{
public:
	virtual void Precache(void) {};
	virtual int Save(CSave &save) { return 0; };
	virtual int Restore(CRestore &restore) { return 0; };
	virtual int AddToPlayer(CBasePlayer *pPlayer) { return 0; };
	virtual int AddDuplicate(CBasePlayerItem *pItem) { return 0; };
	virtual BOOL CanDeploy(void) { return FALSE; };
	virtual BOOL IsWeapon(void) { return TRUE; }
	virtual void Holster(int skiplocal = 0) {};
	virtual void UpdateItemInfo(void) {};
	virtual void ItemPostFrame(void) {};
	virtual int PrimaryAmmoIndex(void) { return 0; };
	virtual int SecondaryAmmoIndex(void) { return 0; };
	virtual int UpdateClientData(CBasePlayer *pPlayer) { return 0; };
	virtual CBasePlayerItem *GetWeaponPtr(void) { return NULL; }
	virtual int ExtractAmmo(CBasePlayerWeapon *pWeapon) { return 0; };
	virtual int ExtractClipAmmo(CBasePlayerWeapon *pWeapon) { return 0; };
	virtual int AddWeapon(void) { return 0; }
	virtual BOOL PlayEmptySound(void) { return FALSE; };
	virtual void ResetEmptySound(void) {};
	virtual void SendWeaponAnim(int iAnim, int skiplocal = 0) {};
	virtual BOOL IsUseable(void) { return FALSE; };
	virtual void PrimaryAttack(void) {};
	virtual void SecondaryAttack(void) {};
	virtual void Reload(void) {};
	virtual void WeaponIdle(void) {};
	virtual void RetireWeapon(void) {};
	virtual BOOL ShouldWeaponIdle(void) { return FALSE; }
	virtual BOOL UseDecrement(void) { return FALSE; }
};

volatile CDummyWeaponClass *g_pDummyWeaponClass = &CDummyWeaponClass();
volatile CDummyWeaponClassExtra *g_pCDummyWeaponClassExtra = &CDummyWeaponClassExtra();
