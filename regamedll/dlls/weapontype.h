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

#pragma once

enum WeaponIdType
{
	WEAPON_NONE,
	WEAPON_P228,
	WEAPON_GLOCK,
	WEAPON_SCOUT,
	WEAPON_HEGRENADE,
	WEAPON_XM1014,
	WEAPON_C4,
	WEAPON_MAC10,
	WEAPON_AUG,
	WEAPON_SMOKEGRENADE,
	WEAPON_ELITE,
	WEAPON_FIVESEVEN,
	WEAPON_UMP45,
	WEAPON_SG550,
	WEAPON_GALIL,
	WEAPON_FAMAS,
	WEAPON_USP,
	WEAPON_GLOCK18,
	WEAPON_AWP,
	WEAPON_MP5N,
	WEAPON_M249,
	WEAPON_M3,
	WEAPON_M4A1,
	WEAPON_TMP,
	WEAPON_G3SG1,
	WEAPON_FLASHBANG,
	WEAPON_DEAGLE,
	WEAPON_SG552,
	WEAPON_AK47,
	WEAPON_KNIFE,
	WEAPON_P90,
	WEAPON_SHIELDGUN = 99
};

enum AutoBuyClassType
{
	AUTOBUYCLASS_NONE           = 0,
	AUTOBUYCLASS_PRIMARY        = BIT(0),
	AUTOBUYCLASS_SECONDARY      = BIT(1),
	AUTOBUYCLASS_AMMO           = BIT(2),
	AUTOBUYCLASS_ARMOR          = BIT(3),
	AUTOBUYCLASS_DEFUSER        = BIT(4),
	AUTOBUYCLASS_PISTOL         = BIT(5),
	AUTOBUYCLASS_SMG            = BIT(6),
	AUTOBUYCLASS_RIFLE          = BIT(7),
	AUTOBUYCLASS_SNIPERRIFLE    = BIT(8),
	AUTOBUYCLASS_SHOTGUN        = BIT(9),
	AUTOBUYCLASS_MACHINEGUN     = BIT(10),
	AUTOBUYCLASS_GRENADE        = BIT(11),
	AUTOBUYCLASS_NIGHTVISION    = BIT(12),
	AUTOBUYCLASS_SHIELD         = BIT(13),
};

enum ItemCostType
{
	ASSAULTSUIT_PRICE   = 1000,
	FLASHBANG_PRICE     = 200,
	HEGRENADE_PRICE     = 300,
	SMOKEGRENADE_PRICE  = 300,
	KEVLAR_PRICE        = 650,
	HELMET_PRICE        = 350,
	NVG_PRICE           = 1250,
	DEFUSEKIT_PRICE     = 200,
};

enum AmmoCostType
{
	AMMO_338MAG_PRICE       = 125,
	AMMO_357SIG_PRICE       = 50,
	AMMO_45ACP_PRICE        = 25,
	AMMO_50AE_PRICE         = 40,
	AMMO_556MM_PRICE        = 60,
	AMMO_57MM_PRICE         = 50,
	AMMO_762MM_PRICE        = 80,
	AMMO_9MM_PRICE          = 20,
	AMMO_BUCKSHOT_PRICE     = 65,
	AMMO_FLASHBANG_PRICE    = FLASHBANG_PRICE,
	AMMO_HEGRENADE_PRICE    = HEGRENADE_PRICE,
	AMMO_SMOKEGRENADE_PRICE = SMOKEGRENADE_PRICE,
};

enum WeaponCostType
{
	AK47_PRICE      = 2500,
	AWP_PRICE       = 4750,
	DEAGLE_PRICE    = 650,
	G3SG1_PRICE     = 5000,
	SG550_PRICE     = 4200,
	GLOCK18_PRICE   = 400,
	M249_PRICE      = 5750,
	M3_PRICE        = 1700,
	M4A1_PRICE      = 3100,
	AUG_PRICE       = 3500,
	MP5NAVY_PRICE   = 1500,
	P228_PRICE      = 600,
	P90_PRICE       = 2350,
	UMP45_PRICE     = 1700,
	MAC10_PRICE     = 1400,
	SCOUT_PRICE     = 2750,
	SG552_PRICE     = 3500,
	TMP_PRICE       = 1250,
	USP_PRICE       = 500,
	ELITE_PRICE     = 800,
	FIVESEVEN_PRICE = 750,
	XM1014_PRICE    = 3000,
	GALIL_PRICE     = 2000,
	FAMAS_PRICE     = 2250,
	SHIELDGUN_PRICE = 2200,
};

enum WeaponState
{
	WPNSTATE_USP_SILENCED       = BIT(0),
	WPNSTATE_GLOCK18_BURST_MODE = BIT(1),
	WPNSTATE_M4A1_SILENCED      = BIT(2),
	WPNSTATE_ELITE_LEFT         = BIT(3),
	WPNSTATE_FAMAS_BURST_MODE   = BIT(4),
	WPNSTATE_SHIELD_DRAWN       = BIT(5),
};

// custom enum
// the default amount of ammo that comes with each gun when it spawns
enum ClipGiveDefault
{
	P228_DEFAULT_GIVE           = 13,
	GLOCK18_DEFAULT_GIVE        = 20,
	SCOUT_DEFAULT_GIVE          = 10,
	HEGRENADE_DEFAULT_GIVE      = 1,
	XM1014_DEFAULT_GIVE         = 7,
	C4_DEFAULT_GIVE             = 1,
	MAC10_DEFAULT_GIVE          = 30,
	AUG_DEFAULT_GIVE            = 30,
	SMOKEGRENADE_DEFAULT_GIVE   = 1,
	ELITE_DEFAULT_GIVE          = 30,
	FIVESEVEN_DEFAULT_GIVE      = 20,
	UMP45_DEFAULT_GIVE          = 25,
	SG550_DEFAULT_GIVE          = 30,
	GALIL_DEFAULT_GIVE          = 35,
	FAMAS_DEFAULT_GIVE          = 25,
	USP_DEFAULT_GIVE            = 12,
	AWP_DEFAULT_GIVE            = 10,
	MP5NAVY_DEFAULT_GIVE        = 30,
	M249_DEFAULT_GIVE           = 100,
	M3_DEFAULT_GIVE             = 8,
	M4A1_DEFAULT_GIVE           = 30,
	TMP_DEFAULT_GIVE            = 30,
	G3SG1_DEFAULT_GIVE          = 20,
	FLASHBANG_DEFAULT_GIVE      = 1,
	DEAGLE_DEFAULT_GIVE         = 7,
	SG552_DEFAULT_GIVE          = 30,
	AK47_DEFAULT_GIVE           = 30,
	//KNIFE_DEFAULT_GIVE        = 1,
	P90_DEFAULT_GIVE            = 50,
};

enum ClipSizeType
{
	P228_MAX_CLIP       = 13,
	GLOCK18_MAX_CLIP    = 20,
	SCOUT_MAX_CLIP      = 10,
	XM1014_MAX_CLIP     = 7,
	MAC10_MAX_CLIP      = 30,
	AUG_MAX_CLIP        = 30,
	ELITE_MAX_CLIP      = 30,
	FIVESEVEN_MAX_CLIP  = 20,
	UMP45_MAX_CLIP      = 25,
	SG550_MAX_CLIP      = 30,
	GALIL_MAX_CLIP      = 35,
	FAMAS_MAX_CLIP      = 25,
	USP_MAX_CLIP        = 12,
	AWP_MAX_CLIP        = 10,
	MP5N_MAX_CLIP       = 30,
	M249_MAX_CLIP       = 100,
	M3_MAX_CLIP         = 8,
	M4A1_MAX_CLIP       = 30,
	TMP_MAX_CLIP        = 30,
	G3SG1_MAX_CLIP      = 20,
	DEAGLE_MAX_CLIP     = 7,
	SG552_MAX_CLIP      = 30,
	AK47_MAX_CLIP       = 30,
	P90_MAX_CLIP        = 50,
};

enum WeightWeapon
{
	P228_WEIGHT         = 5,
	GLOCK18_WEIGHT      = 5,
	SCOUT_WEIGHT        = 30,
	HEGRENADE_WEIGHT    = 2,
	XM1014_WEIGHT       = 20,
	C4_WEIGHT           = 3,
	MAC10_WEIGHT        = 25,
	AUG_WEIGHT          = 25,
	SMOKEGRENADE_WEIGHT = 1,
	ELITE_WEIGHT        = 5,
	FIVESEVEN_WEIGHT    = 5,
	UMP45_WEIGHT        = 25,
	SG550_WEIGHT        = 20,
	GALIL_WEIGHT        = 25,
	FAMAS_WEIGHT        = 75,
	USP_WEIGHT          = 5,
	AWP_WEIGHT          = 30,
	MP5NAVY_WEIGHT      = 25,
	M249_WEIGHT         = 25,
	M3_WEIGHT           = 20,
	M4A1_WEIGHT         = 25,
	TMP_WEIGHT          = 25,
	G3SG1_WEIGHT        = 20,
	FLASHBANG_WEIGHT    = 1,
	DEAGLE_WEIGHT       = 7,
	SG552_WEIGHT        = 25,
	AK47_WEIGHT         = 25,
	P90_WEIGHT          = 26,
	KNIFE_WEIGHT        = 0,
};

enum MaxAmmoType
{
	MAX_AMMO_BUCKSHOT   = 32,
	MAX_AMMO_9MM        = 120,
	MAX_AMMO_556NATO    = 90,
	MAX_AMMO_556NATOBOX = 200,
	MAX_AMMO_762NATO    = 90,
	MAX_AMMO_45ACP      = 100,
	MAX_AMMO_50AE       = 35,
	MAX_AMMO_338MAGNUM  = 30,
	MAX_AMMO_57MM       = 100,
	MAX_AMMO_357SIG     = 52,

	// custom
	MAX_AMMO_SMOKEGRENADE = 1,
	MAX_AMMO_HEGRENADE    = 1,
	MAX_AMMO_FLASHBANG    = 2,
	MAX_AMMO_C4           = 1,
};

enum AmmoType
{
	AMMO_NONE,
	AMMO_338MAGNUM,
	AMMO_762NATO,
	AMMO_556NATOBOX,
	AMMO_556NATO,
	AMMO_BUCKSHOT,
	AMMO_45ACP,
	AMMO_57MM,
	AMMO_50AE,
	AMMO_357SIG,
	AMMO_9MM,
	AMMO_FLASHBANG,
	AMMO_HEGRENADE,
	AMMO_SMOKEGRENADE,
	AMMO_C4,

	AMMO_MAX_TYPES
};

enum WeaponClassType
{
	WEAPONCLASS_NONE,
	WEAPONCLASS_KNIFE,
	WEAPONCLASS_PISTOL,
	WEAPONCLASS_GRENADE,
	WEAPONCLASS_SUBMACHINEGUN,
	WEAPONCLASS_SHOTGUN,
	WEAPONCLASS_MACHINEGUN,
	WEAPONCLASS_RIFLE,
	WEAPONCLASS_SNIPERRIFLE,
	WEAPONCLASS_MAX,
};

enum AmmoBuyAmount
{
	AMMO_338MAG_BUY       = 10,
	AMMO_357SIG_BUY       = 13,
	AMMO_45ACP_BUY        = 12,
	AMMO_50AE_BUY         = 7,
	AMMO_556NATO_BUY      = 30,
	AMMO_556NATOBOX_BUY   = 30,
	AMMO_57MM_BUY         = 50,
	AMMO_762NATO_BUY      = 30,
	AMMO_9MM_BUY          = 30,
	AMMO_BUCKSHOT_BUY     = 8,
	AMMO_FLASHBANG_BUY    = 1,
	AMMO_HEGRENADE_BUY    = 1,
	AMMO_SMOKEGRENADE_BUY = 1,
};

enum shieldgun_e
{
	SHIELDGUN_IDLE,
	SHIELDGUN_SHOOT1,
	SHIELDGUN_SHOOT2,
	SHIELDGUN_SHOOT_EMPTY,
	SHIELDGUN_RELOAD,
	SHIELDGUN_DRAW,
	SHIELDGUN_DRAWN_IDLE,
	SHIELDGUN_UP,
	SHIELDGUN_DOWN,
};

// custom
enum shieldgren_e
{
	SHIELDREN_IDLE = 4,
	SHIELDREN_UP,
	SHIELDREN_DOWN
};

enum InventorySlotType
{
	NONE_SLOT,
	PRIMARY_WEAPON_SLOT,
	PISTOL_SLOT,
	KNIFE_SLOT,
	GRENADE_SLOT,
	C4_SLOT,
};

enum Bullet
{
	BULLET_NONE,
	BULLET_PLAYER_9MM,
	BULLET_PLAYER_MP5,
	BULLET_PLAYER_357,
	BULLET_PLAYER_BUCKSHOT,
	BULLET_PLAYER_CROWBAR,
	BULLET_MONSTER_9MM,
	BULLET_MONSTER_MP5,
	BULLET_MONSTER_12MM,
	BULLET_PLAYER_45ACP,
	BULLET_PLAYER_338MAG,
	BULLET_PLAYER_762MM,
	BULLET_PLAYER_556MM,
	BULLET_PLAYER_50AE,
	BULLET_PLAYER_57MM,
	BULLET_PLAYER_357SIG,
};

struct WeaponStruct
{
	int m_type;
	int m_price;
	int m_side;
	int m_slot;
	int m_ammoPrice;
};

struct AutoBuyInfoStruct
{
	int m_class;
	char *m_command;
	char *m_classname;
};

struct WeaponAliasInfo
{
	char *alias;
	WeaponIdType id;
};

struct WeaponBuyAliasInfo
{
	char *alias;
	WeaponIdType id;
	char *failName;
};

struct WeaponClassAliasInfo
{
	char *alias;
	WeaponClassType id;
};

struct WeaponInfoStruct
{
	int id;
	int cost;
	int clipCost;
	int buyClipSize;
	int gunClipSize;
	int maxRounds;
	AmmoType ammoType;
	char *entityName;

	// custom
	const char *ammoName1;
	const char *ammoName2;
};

struct AmmoInfoStruct
{
	AmmoType ammoType;

	int clipCost;
	int buyClipSize;
	int maxRounds;

	const char *ammoName1;
	const char *ammoName2;
};

struct WeaponSlotInfo
{
	WeaponIdType id;
	InventorySlotType slot;
	const char *weaponName;
};

extern AutoBuyInfoStruct g_autoBuyInfo[35];
extern WeaponStruct g_weaponStruct[MAX_WEAPONS];

// WeaponType
WeaponIdType AliasToWeaponID(const char *alias);
const char *BuyAliasToWeaponID(const char *alias, WeaponIdType &id);
const char *WeaponIDToAlias(int id);
WeaponClassType AliasToWeaponClass(const char *alias);
WeaponClassType WeaponIDToWeaponClass(int id);
WeaponClassType WeaponIDToWeaponClass(ArmouryItemPack id);
bool IsPrimaryWeapon(int id);
bool IsSecondaryWeapon(int id);
bool IsGrenadeWeapon(int id);
bool CanBuyWeaponByMaptype(int playerTeam, WeaponIdType weaponID, bool useAssasinationRestrictions);
void WeaponInfoReset();

WeaponInfoStruct *GetWeaponInfo(int weaponID);
WeaponInfoStruct *GetWeaponInfo(const char *weaponName);

AmmoInfoStruct *GetAmmoInfo(AmmoType ammoID);
AmmoInfoStruct *GetAmmoInfo(const char *ammoName);

WeaponSlotInfo *GetWeaponSlot(WeaponIdType weaponID);
WeaponSlotInfo *GetWeaponSlot(const char *weaponName);
