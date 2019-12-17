#include "precompiled.h"

WeaponStruct g_weaponStruct[MAX_WEAPONS] =
{
	{ 0, 0, 0, 0, 0 },

	{ WEAPON_P228,      P228_PRICE,         TERRORIST|CT,   AUTOBUYCLASS_SECONDARY, AMMO_357SIG_PRICE   },
	{ WEAPON_SCOUT,     SCOUT_PRICE,        TERRORIST|CT,   AUTOBUYCLASS_PRIMARY,   AMMO_762MM_PRICE    },
	{ WEAPON_XM1014,    XM1014_PRICE,       TERRORIST|CT,   AUTOBUYCLASS_PRIMARY,   AMMO_BUCKSHOT_PRICE },
	{ WEAPON_MAC10,     MAC10_PRICE,        CT,             AUTOBUYCLASS_PRIMARY,   AMMO_45ACP_PRICE    },
	{ WEAPON_AUG,       AUG_PRICE,          TERRORIST,      AUTOBUYCLASS_PRIMARY,   AMMO_556MM_PRICE    },
	{ WEAPON_ELITE,     ELITE_PRICE,        CT,             AUTOBUYCLASS_SECONDARY, AMMO_9MM_PRICE      },
	{ WEAPON_FIVESEVEN, FIVESEVEN_PRICE,    TERRORIST|CT,   AUTOBUYCLASS_SECONDARY, AMMO_57MM_PRICE     },
	{ WEAPON_UMP45,     UMP45_PRICE,        TERRORIST,      AUTOBUYCLASS_PRIMARY,   AMMO_45ACP_PRICE    },
	{ WEAPON_SG550,     SG550_PRICE,        TERRORIST,      AUTOBUYCLASS_PRIMARY,   AMMO_556MM_PRICE    },
	{ WEAPON_USP,       USP_PRICE,          TERRORIST|CT,   AUTOBUYCLASS_SECONDARY, AMMO_45ACP_PRICE    },
	{ WEAPON_GLOCK18,   GLOCK18_PRICE,      TERRORIST|CT,   AUTOBUYCLASS_SECONDARY, AMMO_9MM_PRICE      },
	{ WEAPON_MP5N,      MP5NAVY_PRICE,      TERRORIST|CT,   AUTOBUYCLASS_PRIMARY,   AMMO_9MM_PRICE      },
	{ WEAPON_AWP,       AWP_PRICE,          TERRORIST|CT,   AUTOBUYCLASS_PRIMARY,   AMMO_338MAG_PRICE   },
	{ WEAPON_M249,      M249_PRICE,         TERRORIST|CT,   AUTOBUYCLASS_PRIMARY,   AMMO_556MM_PRICE    },
	{ WEAPON_M3,        M3_PRICE,           TERRORIST|CT,   AUTOBUYCLASS_PRIMARY,   AMMO_BUCKSHOT_PRICE },
	{ WEAPON_M4A1,      M4A1_PRICE,         TERRORIST,      AUTOBUYCLASS_PRIMARY,   AMMO_556MM_PRICE    },
	{ WEAPON_TMP,       TMP_PRICE,          TERRORIST,      AUTOBUYCLASS_PRIMARY,   AMMO_9MM_PRICE      },
	{ WEAPON_G3SG1,     G3SG1_PRICE,        CT,             AUTOBUYCLASS_PRIMARY,   AMMO_762MM_PRICE    },
	{ WEAPON_DEAGLE,    DEAGLE_PRICE,       TERRORIST|CT,   AUTOBUYCLASS_SECONDARY, AMMO_50AE_PRICE     },
	{ WEAPON_SG552,     SG552_PRICE,        CT,             AUTOBUYCLASS_PRIMARY,   AMMO_556MM_PRICE    },
	{ WEAPON_AK47,      AK47_PRICE,         CT,             AUTOBUYCLASS_PRIMARY,   AMMO_762MM_PRICE    },
	{ WEAPON_P90,       P90_PRICE,          TERRORIST|CT,   AUTOBUYCLASS_PRIMARY,   AMMO_57MM_PRICE     },
	{ WEAPON_FAMAS,     FAMAS_PRICE,        TERRORIST,      AUTOBUYCLASS_PRIMARY,   AMMO_556MM_PRICE    },
	{ WEAPON_GALIL,     GALIL_PRICE,        CT,             AUTOBUYCLASS_PRIMARY,   AMMO_556MM_PRICE    },
				// FIX: there is a bug, the cost of galil $2000 instead $2250

	{ WEAPON_SHIELDGUN, SHIELDGUN_PRICE,    TERRORIST,      AUTOBUYCLASS_PRIMARY,   0                   },

	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
};

AutoBuyInfoStruct g_autoBuyInfo[] =
{
	{ AUTOBUYCLASS_PRIMARY|AUTOBUYCLASS_RIFLE,      "galil",    "weapon_galil"          },
	{ AUTOBUYCLASS_PRIMARY|AUTOBUYCLASS_RIFLE,      "ak47",     "weapon_ak47"           },
	{ AUTOBUYCLASS_PRIMARY|AUTOBUYCLASS_SNIPERRIFLE,"scout",    "weapon_scout"          },
	{ AUTOBUYCLASS_PRIMARY|AUTOBUYCLASS_RIFLE,      "sg552",    "weapon_sg552"          },
	{ AUTOBUYCLASS_PRIMARY|AUTOBUYCLASS_SNIPERRIFLE,"awp",      "weapon_awp"            },
	{ AUTOBUYCLASS_PRIMARY|AUTOBUYCLASS_SNIPERRIFLE,"g3sg1",    "weapon_g3sg1"          },
	{ AUTOBUYCLASS_PRIMARY|AUTOBUYCLASS_RIFLE,      "famas",    "weapon_famas"          },
	{ AUTOBUYCLASS_PRIMARY|AUTOBUYCLASS_RIFLE,      "m4a1",     "weapon_m4a1"           },
	{ AUTOBUYCLASS_PRIMARY|AUTOBUYCLASS_RIFLE,      "aug",      "weapon_aug"            },
	{ AUTOBUYCLASS_PRIMARY|AUTOBUYCLASS_SNIPERRIFLE,"sg550",    "weapon_sg550"          },
	{ AUTOBUYCLASS_SECONDARY|AUTOBUYCLASS_PISTOL,   "glock",    "weapon_glock18"        },
	{ AUTOBUYCLASS_SECONDARY|AUTOBUYCLASS_PISTOL,   "usp",      "weapon_usp"            },
	{ AUTOBUYCLASS_SECONDARY|AUTOBUYCLASS_PISTOL,   "p228",     "weapon_p228"           },
	{ AUTOBUYCLASS_SECONDARY|AUTOBUYCLASS_PISTOL,   "deagle",   "weapon_deagle"         },
	{ AUTOBUYCLASS_SECONDARY|AUTOBUYCLASS_PISTOL,   "elites",   "weapon_elite"          },
	{ AUTOBUYCLASS_SECONDARY|AUTOBUYCLASS_PISTOL,   "fn57",     "weapon_fiveseven"      },
	{ AUTOBUYCLASS_PRIMARY|AUTOBUYCLASS_SHOTGUN,    "m3",       "weapon_m3"             },
	{ AUTOBUYCLASS_PRIMARY|AUTOBUYCLASS_SHOTGUN,    "xm1014",   "weapon_xm1014"         },
	{ AUTOBUYCLASS_PRIMARY|AUTOBUYCLASS_SMG,        "mac10",    "weapon_mac10"          },
	{ AUTOBUYCLASS_PRIMARY|AUTOBUYCLASS_SMG,        "tmp",      "weapon_tmp"            },
	{ AUTOBUYCLASS_PRIMARY|AUTOBUYCLASS_SMG,        "mp5",      "weapon_mp5navy"        },
	{ AUTOBUYCLASS_PRIMARY|AUTOBUYCLASS_SMG,        "ump45",    "weapon_ump45"          },
	{ AUTOBUYCLASS_PRIMARY|AUTOBUYCLASS_SMG,        "p90",      "weapon_p90"            },
	{ AUTOBUYCLASS_PRIMARY|AUTOBUYCLASS_MACHINEGUN, "m249",     "weapon_m249"           },
	{ AUTOBUYCLASS_PRIMARY|AUTOBUYCLASS_AMMO,       "primammo", "primammo"              },
	{ AUTOBUYCLASS_SECONDARY|AUTOBUYCLASS_AMMO,     "secammo",  "secammo"               },
	{ AUTOBUYCLASS_ARMOR,                           "vest",     "item_kevlar"           },
	{ AUTOBUYCLASS_ARMOR,                           "vesthelm", "item_assaultsuit"      },
	{ AUTOBUYCLASS_GRENADE,                         "flash",    "weapon_flashbang"      },
	{ AUTOBUYCLASS_GRENADE,                         "hegren",   "weapon_hegrenade"      },
	{ AUTOBUYCLASS_GRENADE,                         "sgren",    "weapon_smokegrenade"   },
	{ AUTOBUYCLASS_NIGHTVISION,                     "nvgs",     "nvgs"                  },
	{ AUTOBUYCLASS_DEFUSER,                         "defuser",  "defuser"               },
	{ AUTOBUYCLASS_PRIMARY|AUTOBUYCLASS_SHIELD,     "shield",   "shield"                },
	{ AUTOBUYCLASS_NONE,                            nullptr,     nullptr                },
};

WeaponAliasInfo g_weaponAliasInfo[] =
{
	{ "p228",       WEAPON_P228         },
	{ "???",        WEAPON_GLOCK        },
	{ "scout",      WEAPON_SCOUT        },
	{ "hegren",     WEAPON_HEGRENADE    },
	{ "xm1014",     WEAPON_XM1014       },
	{ "c4",         WEAPON_C4           },
	{ "mac10",      WEAPON_MAC10        },
	{ "aug",        WEAPON_AUG          },
	{ "sgren",      WEAPON_SMOKEGRENADE },
	{ "elites",     WEAPON_ELITE        },
	{ "fn57",       WEAPON_FIVESEVEN    },
	{ "ump45",      WEAPON_UMP45        },
	{ "sg550",      WEAPON_SG550        },
	{ "galil",      WEAPON_GALIL        },
	{ "famas",      WEAPON_FAMAS        },
	{ "usp",        WEAPON_USP          },
	{ "glock",      WEAPON_GLOCK18      },
	{ "awp",        WEAPON_AWP          },
	{ "mp5",        WEAPON_MP5N         },
	{ "m249",       WEAPON_M249         },
	{ "m3",         WEAPON_M3           },
	{ "m4a1",       WEAPON_M4A1         },
	{ "tmp",        WEAPON_TMP          },
	{ "g3sg1",      WEAPON_G3SG1        },
	{ "flash",      WEAPON_FLASHBANG    },
	{ "deagle",     WEAPON_DEAGLE       },
	{ "sg552",      WEAPON_SG552        },
	{ "ak47",       WEAPON_AK47         },
	{ "knife",      WEAPON_KNIFE        },
	{ "p90",        WEAPON_P90          },
	{ "shield",     WEAPON_SHIELDGUN    },
	{ "none",       WEAPON_NONE         },
	{ "grenade",    WEAPON_HEGRENADE    },
	{ "hegrenade",  WEAPON_HEGRENADE    },
	{ "glock18",    WEAPON_GLOCK18      },
	{ "elite",      WEAPON_ELITE        },
	{ "fiveseven",  WEAPON_FIVESEVEN    },
	{ "mp5navy",    WEAPON_MP5N         },
	{ nullptr,      WEAPON_NONE         },
};

WeaponBuyAliasInfo g_weaponBuyAliasInfo[] =
{
	{ "galil",      WEAPON_GALIL,       "#Galil"        },
	{ "defender",   WEAPON_GALIL,       "#Galil"        },
	{ "ak47",       WEAPON_AK47,        "#AK47"         },
	{ "cv47",       WEAPON_AK47,        "#AK47"         },
	{ "scout",      WEAPON_SCOUT,       nullptr         },
	{ "sg552",      WEAPON_SG552,       "#SG552"        },
	{ "krieg552",   WEAPON_SG552,       "#SG552"        },
	{ "awp",        WEAPON_AWP,         nullptr         },
	{ "magnum",     WEAPON_AWP,         nullptr         },
	{ "g3sg1",      WEAPON_G3SG1,       "#G3SG1"        },
	{ "d3au1",      WEAPON_G3SG1,       "#G3SG1"        },
	{ "famas",      WEAPON_FAMAS,       "#Famas"        },
	{ "clarion",    WEAPON_FAMAS,       "#Famas"        },
	{ "m4a1",       WEAPON_M4A1,        "#M4A1"         },
	{ "aug",        WEAPON_AUG,         "#Aug"          },
	{ "bullpup",    WEAPON_AUG,         "#Aug"          },
	{ "sg550",      WEAPON_SG550,       "#SG550"        },
	{ "krieg550",   WEAPON_SG550,       "#SG550"        },
	{ "glock",      WEAPON_GLOCK18,     nullptr         },
	{ "9x19mm",     WEAPON_GLOCK18,     nullptr         },
	{ "usp",        WEAPON_USP,         nullptr         },
	{ "km45",       WEAPON_USP,         nullptr         },
	{ "p228",       WEAPON_P228,        nullptr         },
	{ "228compact", WEAPON_P228,        nullptr         },
	{ "deagle",     WEAPON_DEAGLE,      nullptr         },
	{ "nighthaw",   WEAPON_DEAGLE,      nullptr         },
	{ "elites",     WEAPON_ELITE,       "#Beretta96G"   },
	{ "fn57",       WEAPON_FIVESEVEN,   "#FiveSeven"    },
	{ "fiveseven",  WEAPON_FIVESEVEN,   "#FiveSeven"    },
	{ "m3",         WEAPON_M3,          nullptr         },
	{ "12gauge",    WEAPON_M3,          nullptr         },
	{ "xm1014",     WEAPON_XM1014,      nullptr         },
	{ "autoshotgun",WEAPON_XM1014,      nullptr         },
	{ "mac10",      WEAPON_MAC10,       "#Mac10"        },
	{ "tmp",        WEAPON_TMP,         "#tmp"          },
	{ "mp",         WEAPON_TMP,         "#tmp"          },
	{ "mp5",        WEAPON_MP5N,        nullptr         },
	{ "smg",        WEAPON_MP5N,        nullptr         },
	{ "ump45",      WEAPON_UMP45,       nullptr         },
	{ "p90",        WEAPON_P90,         nullptr         },
	{ "c90",        WEAPON_P90,         nullptr         },
	{ "m249",       WEAPON_M249,        nullptr         },
	{ nullptr,      WEAPON_NONE,        nullptr         },
};

WeaponClassAliasInfo g_weaponClassAliasInfo[] =
{
	{ "p228",       WEAPONCLASS_PISTOL          },
	{ "???",        WEAPONCLASS_PISTOL          },
	{ "scout",      WEAPONCLASS_SNIPERRIFLE     },
	{ "hegren",     WEAPONCLASS_GRENADE         },
	{ "xm1014",     WEAPONCLASS_SHOTGUN         },
	{ "c4",         WEAPONCLASS_GRENADE         },
	{ "mac10",      WEAPONCLASS_SUBMACHINEGUN   },
	{ "aug",        WEAPONCLASS_RIFLE           },
	{ "sgren",      WEAPONCLASS_GRENADE         },
	{ "elites",     WEAPONCLASS_PISTOL          },
	{ "fn57",       WEAPONCLASS_PISTOL          },
	{ "ump45",      WEAPONCLASS_SUBMACHINEGUN   },
	{ "sg550",      WEAPONCLASS_SNIPERRIFLE     },
	{ "galil",      WEAPONCLASS_RIFLE           },
	{ "famas",      WEAPONCLASS_RIFLE           },
	{ "usp",        WEAPONCLASS_PISTOL          },
	{ "glock",      WEAPONCLASS_PISTOL          },
	{ "awp",        WEAPONCLASS_SNIPERRIFLE     },
	{ "mp5",        WEAPONCLASS_SUBMACHINEGUN   },
	{ "m249",       WEAPONCLASS_MACHINEGUN      },
	{ "m3",         WEAPONCLASS_SHOTGUN         },
	{ "m4a1",       WEAPONCLASS_RIFLE           },
	{ "tmp",        WEAPONCLASS_SUBMACHINEGUN   },
	{ "g3sg1",      WEAPONCLASS_SNIPERRIFLE     },
	{ "flash",      WEAPONCLASS_GRENADE         },
	{ "deagle",     WEAPONCLASS_PISTOL          },
	{ "sg552",      WEAPONCLASS_RIFLE           },
	{ "ak47",       WEAPONCLASS_RIFLE           },
	{ "knife",      WEAPONCLASS_KNIFE           },
	{ "p90",        WEAPONCLASS_SUBMACHINEGUN   },
	{ "shield",     WEAPONCLASS_PISTOL          },
	{ "grenade",    WEAPONCLASS_GRENADE         },
	{ "hegrenade",  WEAPONCLASS_GRENADE         },
	{ "glock18",    WEAPONCLASS_PISTOL          },
	{ "elite",      WEAPONCLASS_PISTOL          },
	{ "fiveseven",  WEAPONCLASS_PISTOL          },
	{ "mp5navy",    WEAPONCLASS_SUBMACHINEGUN   },
	{ "grenade",    WEAPONCLASS_GRENADE         },
	{ "pistol",     WEAPONCLASS_PISTOL          },
	{ "SMG",        WEAPONCLASS_SUBMACHINEGUN   },
	{ "machinegun", WEAPONCLASS_MACHINEGUN      },
	{ "shotgun",    WEAPONCLASS_SHOTGUN         },
	{ "rifle",      WEAPONCLASS_RIFLE           },
	{ "sniper",     WEAPONCLASS_SNIPERRIFLE     },
	{ "none",       WEAPONCLASS_NONE            },
	{ nullptr,      WEAPONCLASS_NONE            },
};

WeaponInfoStruct g_weaponInfo_default[] =
{
	{ WEAPON_P228,      P228_PRICE,         AMMO_357SIG_PRICE,                           AMMO_357SIG_BUY,       P228_MAX_CLIP,      MAX_AMMO_357SIG,        AMMO_357SIG,        "weapon_p228",         "ammo_357sig",     "357SIG"       },

// fix collision with glock18
#ifdef REGAMEDLL_FIXES
	{ WEAPON_GLOCK,     GLOCK18_PRICE,      AMMO_9MM_PRICE,                              AMMO_9MM_BUY,          GLOCK18_MAX_CLIP,   MAX_AMMO_9MM,           AMMO_9MM,           "weapon_glock",        "ammo_9mm",        "9mm"          },
#else
	{ WEAPON_GLOCK,     GLOCK18_PRICE,      AMMO_9MM_PRICE,                              AMMO_9MM_BUY,          GLOCK18_MAX_CLIP,   MAX_AMMO_9MM,           AMMO_9MM,           "weapon_glock18",      "ammo_9mm",        "9mm"          },
#endif

	{ WEAPON_GLOCK18,   GLOCK18_PRICE,      AMMO_9MM_PRICE,                              AMMO_9MM_BUY,          GLOCK18_MAX_CLIP,   MAX_AMMO_9MM,           AMMO_9MM,           "weapon_glock18",      "ammo_9mm",        "9mm"          },
	{ WEAPON_SCOUT,     SCOUT_PRICE,        AMMO_762MM_PRICE,                            AMMO_762NATO_BUY,      SCOUT_MAX_CLIP,     MAX_AMMO_762NATO,       AMMO_762NATO,       "weapon_scout",        "ammo_762nato",    "762Nato"      },
	{ WEAPON_XM1014,    XM1014_PRICE,       AMMO_BUCKSHOT_PRICE,                         AMMO_BUCKSHOT_BUY,     XM1014_MAX_CLIP,    MAX_AMMO_BUCKSHOT,      AMMO_BUCKSHOT,      "weapon_xm1014",       "ammo_buckshot",   "buckshot"     },
	{ WEAPON_MAC10,     MAC10_PRICE,        AMMO_45ACP_PRICE,                            AMMO_45ACP_BUY,        MAC10_MAX_CLIP,     MAX_AMMO_45ACP,         AMMO_45ACP,         "weapon_mac10",        "ammo_45acp",      "45acp"        },
	{ WEAPON_AUG,       AUG_PRICE,          AMMO_556MM_PRICE,                            AMMO_556NATO_BUY,      AUG_MAX_CLIP,       MAX_AMMO_556NATO,       AMMO_556NATO,       "weapon_aug",          "ammo_556nato",    "556Nato"      },
	{ WEAPON_ELITE,     ELITE_PRICE,        AMMO_9MM_PRICE,                              AMMO_9MM_BUY,          ELITE_MAX_CLIP,     MAX_AMMO_9MM,           AMMO_9MM,           "weapon_elite",        "ammo_9mm",        "9mm"          },
	{ WEAPON_FIVESEVEN, FIVESEVEN_PRICE,    AMMO_57MM_PRICE,                             AMMO_57MM_BUY,         FIVESEVEN_MAX_CLIP, MAX_AMMO_57MM,          AMMO_57MM,          "weapon_fiveseven",    "ammo_57mm",       "57mm"         },
	{ WEAPON_UMP45,     UMP45_PRICE,        AMMO_45ACP_PRICE,                            AMMO_45ACP_BUY,        UMP45_MAX_CLIP,     MAX_AMMO_45ACP,         AMMO_45ACP,         "weapon_ump45",        "ammo_45acp",      "45acp"        },
	{ WEAPON_SG550,     SG550_PRICE,        AMMO_556MM_PRICE,                            AMMO_556NATO_BUY,      SG550_MAX_CLIP,     MAX_AMMO_556NATO,       AMMO_556NATO,       "weapon_sg550",        "ammo_556nato",    "556Nato"      },
	{ WEAPON_GALIL,     GALIL_PRICE,        AMMO_556MM_PRICE,                            AMMO_556NATO_BUY,      GALIL_MAX_CLIP,     MAX_AMMO_556NATO,       AMMO_556NATO,       "weapon_galil",        "ammo_556nato",    "556Nato"      },
	{ WEAPON_FAMAS,     FAMAS_PRICE,        AMMO_556MM_PRICE,                            AMMO_556NATO_BUY,      FAMAS_MAX_CLIP,     MAX_AMMO_556NATO,       AMMO_556NATO,       "weapon_famas",        "ammo_556nato",    "556Nato"      },
	{ WEAPON_USP,       USP_PRICE,          AMMO_45ACP_PRICE,                            AMMO_45ACP_BUY,        USP_MAX_CLIP,       MAX_AMMO_45ACP,         AMMO_45ACP,         "weapon_usp",          "ammo_45acp",      "45acp"        },
	{ WEAPON_AWP,       AWP_PRICE,          AMMO_338MAG_PRICE,                           AMMO_338MAG_BUY,       AWP_MAX_CLIP,       MAX_AMMO_338MAGNUM,     AMMO_338MAGNUM,     "weapon_awp",          "ammo_338magnum",  "338Magnum"    },
	{ WEAPON_MP5N,      MP5NAVY_PRICE,      AMMO_9MM_PRICE,                              AMMO_9MM_BUY,          MP5N_MAX_CLIP,      MAX_AMMO_9MM,           AMMO_9MM,           "weapon_mp5navy",      "ammo_9mm",        "9mm"          },
	{ WEAPON_M249,      M249_PRICE,         AMMO_556MM_PRICE,                            AMMO_556NATOBOX_BUY,   M249_MAX_CLIP,      MAX_AMMO_556NATOBOX,    AMMO_556NATOBOX,    "weapon_m249",         "ammo_556natobox", "556NatoBox"   },
	{ WEAPON_M3,        M3_PRICE,           AMMO_BUCKSHOT_PRICE,                         AMMO_BUCKSHOT_BUY,     M3_MAX_CLIP,        MAX_AMMO_BUCKSHOT,      AMMO_BUCKSHOT,      "weapon_m3",           "ammo_buckshot",   "buckshot"     },
	{ WEAPON_M4A1,      M4A1_PRICE,         AMMO_556MM_PRICE,                            AMMO_556NATO_BUY,      M4A1_MAX_CLIP,      MAX_AMMO_556NATO,       AMMO_556NATO,       "weapon_m4a1",         "ammo_556nato",    "556Nato"      },
	{ WEAPON_TMP,       TMP_PRICE,          AMMO_9MM_PRICE,                              AMMO_9MM_BUY,          TMP_MAX_CLIP,       MAX_AMMO_9MM,           AMMO_9MM,           "weapon_tmp",          "ammo_9mm",        "9mm"          },
	{ WEAPON_G3SG1,     G3SG1_PRICE,        AMMO_762MM_PRICE,                            AMMO_762NATO_BUY,      G3SG1_MAX_CLIP,     MAX_AMMO_762NATO,       AMMO_762NATO,       "weapon_g3sg1",        "ammo_762nato",    "762Nato"      },
	{ WEAPON_DEAGLE,    DEAGLE_PRICE,       AMMO_50AE_PRICE,                             AMMO_50AE_BUY,         DEAGLE_MAX_CLIP,    MAX_AMMO_50AE,          AMMO_50AE,          "weapon_deagle",       "ammo_50ae",       "50AE"         },
	{ WEAPON_SG552,     SG552_PRICE,        AMMO_556MM_PRICE,                            AMMO_556NATO_BUY,      SG552_MAX_CLIP,     MAX_AMMO_556NATO,       AMMO_556NATO,       "weapon_sg552",        "ammo_556nato",    "556Nato"      },
	{ WEAPON_AK47,      AK47_PRICE,         AMMO_762MM_PRICE,                            AMMO_762NATO_BUY,      AK47_MAX_CLIP,      MAX_AMMO_762NATO,       AMMO_762NATO,       "weapon_ak47",         "ammo_762nato",    "762Nato"      },
	{ WEAPON_P90,       P90_PRICE,          AMMO_57MM_PRICE,                             AMMO_57MM_BUY,         P90_MAX_CLIP,       MAX_AMMO_57MM,          AMMO_57MM,          "weapon_p90",          "ammo_57mm",       "57mm"         },

#ifdef REGAMEDLL_FIXES
	{ WEAPON_C4,            0,                                  0,                       0,                     0,                  MAX_AMMO_C4,            AMMO_C4,            "weapon_c4",           nullptr,           "C4"           },
	{ WEAPON_KNIFE,         0,                                  0,                       0,                     0,                  0,                      AMMO_NONE,          "weapon_knife",        nullptr,           nullptr        },
	{ WEAPON_HEGRENADE,     (WeaponCostType)HEGRENADE_PRICE,    AMMO_HEGRENADE_PRICE,    AMMO_HEGRENADE_BUY,    0,                  MAX_AMMO_HEGRENADE,     AMMO_HEGRENADE,     "weapon_hegrenade",    nullptr,           "HEGrenade"    },
	{ WEAPON_SMOKEGRENADE,  (WeaponCostType)SMOKEGRENADE_PRICE, AMMO_SMOKEGRENADE_PRICE, AMMO_SMOKEGRENADE_BUY, 0,                  MAX_AMMO_SMOKEGRENADE,  AMMO_SMOKEGRENADE,  "weapon_smokegrenade", nullptr,           "SmokeGrenade" },
	{ WEAPON_FLASHBANG,     (WeaponCostType)FLASHBANG_PRICE,    AMMO_FLASHBANG_PRICE,    AMMO_FLASHBANG_BUY,    0,                  MAX_AMMO_FLASHBANG,     AMMO_FLASHBANG,     "weapon_flashbang",    nullptr,           "Flashbang"    },
#endif

	{ WEAPON_SHIELDGUN,      SHIELDGUN_PRICE,                   0,                       0,                     0,                  0,                      AMMO_NONE,          "weapon_shield",       nullptr,           nullptr        },
#ifndef REGAMEDLL_FIXES
	{ 0,                     0,                                 0,                       0,                     0,                  0,                      AMMO_NONE,          nullptr,               nullptr,           nullptr        },
#endif
};

WeaponInfoStruct g_weaponInfo[ARRAYSIZE(g_weaponInfo_default)];

AmmoInfoStruct g_ammoInfo_default[] =
{
	{ AMMO_338MAGNUM,    AMMO_338MAG_PRICE,       AMMO_338MAG_BUY,       MAX_AMMO_338MAGNUM,    "ammo_338magnum",  "338Magnum"    },
	{ AMMO_762NATO,      AMMO_762MM_PRICE,        AMMO_762NATO_BUY,      MAX_AMMO_762NATO,      "ammo_762nato",    "762Nato"      },
	{ AMMO_556NATOBOX,   AMMO_556MM_PRICE,        AMMO_556NATOBOX_BUY,   MAX_AMMO_556NATOBOX,   "ammo_556natobox", "556NatoBox"   },
	{ AMMO_556NATO,      AMMO_556MM_PRICE,        AMMO_556NATO_BUY,      MAX_AMMO_556NATO,      "ammo_556nato",    "556Nato"      },
	{ AMMO_BUCKSHOT,     AMMO_BUCKSHOT_PRICE,     AMMO_BUCKSHOT_BUY,     MAX_AMMO_BUCKSHOT,     "ammo_buckshot",   "buckshot"     },
	{ AMMO_45ACP,        AMMO_45ACP_PRICE,        AMMO_45ACP_BUY,        MAX_AMMO_45ACP,        "ammo_45acp",      "45acp"        },
	{ AMMO_57MM,         AMMO_57MM_PRICE,         AMMO_57MM_BUY,         MAX_AMMO_57MM,         "ammo_57mm",       "57mm"         },
	{ AMMO_50AE,         AMMO_50AE_PRICE,         AMMO_50AE_BUY,         MAX_AMMO_50AE,         "ammo_50ae",       "50AE"         },
	{ AMMO_357SIG,       AMMO_357SIG_PRICE,       AMMO_357SIG_BUY,       MAX_AMMO_357SIG,       "ammo_357sig",     "357SIG"       },
	{ AMMO_9MM,          AMMO_9MM_PRICE,          AMMO_9MM_BUY,          MAX_AMMO_9MM,          "ammo_9mm",        "9mm"          },
	{ AMMO_FLASHBANG,    AMMO_FLASHBANG_PRICE,    AMMO_FLASHBANG_BUY,    MAX_AMMO_FLASHBANG,    nullptr,           "Flashbang"    },
	{ AMMO_HEGRENADE,    AMMO_HEGRENADE_PRICE,    AMMO_HEGRENADE_BUY,    MAX_AMMO_HEGRENADE,    nullptr,           "HEGrenade"    },
	{ AMMO_SMOKEGRENADE, AMMO_SMOKEGRENADE_PRICE, AMMO_SMOKEGRENADE_BUY, MAX_AMMO_SMOKEGRENADE, nullptr,           "SmokeGrenade" },
	{ AMMO_C4,           0,                       0,                     MAX_AMMO_C4,           nullptr,           "C4"           },
};

AmmoInfoStruct g_ammoInfo[ARRAYSIZE(g_ammoInfo_default)];

WeaponSlotInfo g_weaponSlotInfo[] = {
	{ WEAPON_C4,            C4_SLOT,                "weapon_c4"             },
	{ WEAPON_KNIFE,         KNIFE_SLOT,             "weapon_knife"          },
	{ WEAPON_P228,          PISTOL_SLOT,            "weapon_p228"           },
	{ WEAPON_GLOCK,         PISTOL_SLOT,            "weapon_glock"          },
	{ WEAPON_ELITE,         PISTOL_SLOT,            "weapon_elite"          },
	{ WEAPON_FIVESEVEN,     PISTOL_SLOT,            "weapon_fiveseven"      },
	{ WEAPON_USP,           PISTOL_SLOT,            "weapon_usp"            },
	{ WEAPON_GLOCK18,       PISTOL_SLOT,            "weapon_glock18"        },
	{ WEAPON_DEAGLE,        PISTOL_SLOT,            "weapon_deagle"         },
	{ WEAPON_HEGRENADE,     GRENADE_SLOT,           "weapon_hegrenade"      },
	{ WEAPON_SMOKEGRENADE,  GRENADE_SLOT,           "weapon_smokegrenade"   },
	{ WEAPON_FLASHBANG,     GRENADE_SLOT,           "weapon_flashbang"      },
	{ WEAPON_SCOUT,         PRIMARY_WEAPON_SLOT,    "weapon_scout"          },
	{ WEAPON_XM1014,        PRIMARY_WEAPON_SLOT,    "weapon_xm1014"         },
	{ WEAPON_MAC10,         PRIMARY_WEAPON_SLOT,    "weapon_mac10"          },
	{ WEAPON_AUG,           PRIMARY_WEAPON_SLOT,    "weapon_aug"            },
	{ WEAPON_UMP45,         PRIMARY_WEAPON_SLOT,    "weapon_ump45"          },
	{ WEAPON_SG550,         PRIMARY_WEAPON_SLOT,    "weapon_sg550"          },
	{ WEAPON_GALIL,         PRIMARY_WEAPON_SLOT,    "weapon_galil"          },
	{ WEAPON_FAMAS,         PRIMARY_WEAPON_SLOT,    "weapon_famas"          },
	{ WEAPON_AWP,           PRIMARY_WEAPON_SLOT,    "weapon_awp"            },
	{ WEAPON_MP5N,          PRIMARY_WEAPON_SLOT,    "weapon_mp5navy"        },
	{ WEAPON_M249,          PRIMARY_WEAPON_SLOT,    "weapon_m249"           },
	{ WEAPON_M3,            PRIMARY_WEAPON_SLOT,    "weapon_m3"             },
	{ WEAPON_M4A1,          PRIMARY_WEAPON_SLOT,    "weapon_m4a1"           },
	{ WEAPON_TMP,           PRIMARY_WEAPON_SLOT,    "weapon_tmp"            },
	{ WEAPON_G3SG1,         PRIMARY_WEAPON_SLOT,    "weapon_g3sg1"          },
	{ WEAPON_SG552,         PRIMARY_WEAPON_SLOT,    "weapon_sg552"          },
	{ WEAPON_AK47,          PRIMARY_WEAPON_SLOT,    "weapon_ak47"           },
	{ WEAPON_P90,           PRIMARY_WEAPON_SLOT,    "weapon_p90"            },
	{ WEAPON_SHIELDGUN,     NONE_SLOT,              "weapon_shield"         },
};

// Given an alias, return the associated weapon ID
WeaponIdType AliasToWeaponID(const char *alias)
{
	if (alias)
	{
		for (int i = 0; g_weaponAliasInfo[i].alias; i++)
		{
			if (!Q_stricmp(g_weaponAliasInfo[i].alias, alias))
				return g_weaponAliasInfo[i].id;
		}
	}

	return WEAPON_NONE;
}

const char *BuyAliasToWeaponID(const char *alias, WeaponIdType &id)
{
	if (alias)
	{
		for (int i = 0; g_weaponBuyAliasInfo[i].alias; i++)
		{
			if (!Q_stricmp(g_weaponBuyAliasInfo[i].alias, alias))
			{
				id = g_weaponBuyAliasInfo[i].id;
				return g_weaponBuyAliasInfo[i].failName;
			}
		}
	}

	id = WEAPON_NONE;
	return nullptr;
}

// Given a weapon ID, return its alias
const char *WeaponIDToAlias(int id)
{
	for (int i = 0; g_weaponAliasInfo[i].alias; i++)
	{
		if (g_weaponAliasInfo[i].id == id)
			return g_weaponAliasInfo[i].alias;
	}

	return nullptr;
}

WeaponClassType AliasToWeaponClass(const char *alias)
{
	if (alias)
	{
		for (int i = 0; g_weaponClassAliasInfo[i].alias; i++)
		{
			if (!Q_stricmp(g_weaponClassAliasInfo[i].alias, alias))
				return g_weaponClassAliasInfo[i].id;
		}
	}

	return WEAPONCLASS_NONE;
}

WeaponClassType WeaponIDToWeaponClass(int id)
{
	return AliasToWeaponClass(WeaponIDToAlias(id));
}

WeaponClassType WeaponIDToWeaponClass(ArmouryItemPack id)
{
	switch (id)
	{
	case ARMOURY_AUG:
	case ARMOURY_GALIL:
	case ARMOURY_M4A1:
	case ARMOURY_SG552:
	case ARMOURY_AK47:
	case ARMOURY_FAMAS:
		return WEAPONCLASS_RIFLE;

	case ARMOURY_GLOCK18:
	case ARMOURY_USP:
	case ARMOURY_ELITE:
	case ARMOURY_FIVESEVEN:
	case ARMOURY_P228:
	case ARMOURY_DEAGLE:
		return WEAPONCLASS_PISTOL;

	case ARMOURY_MP5NAVY:
	case ARMOURY_MAC10:
	case ARMOURY_TMP:
	case ARMOURY_UMP45:
	case ARMOURY_P90:
		return WEAPONCLASS_SUBMACHINEGUN;

	case ARMOURY_SCOUT:
	case ARMOURY_SG550:
	case ARMOURY_AWP:
	case ARMOURY_G3SG1:
		return WEAPONCLASS_SNIPERRIFLE;

	case ARMOURY_FLASHBANG:
	case ARMOURY_HEGRENADE:
	case ARMOURY_SMOKEGRENADE:
		return WEAPONCLASS_GRENADE;

	case ARMOURY_M3:
	case ARMOURY_XM1014:
		return WEAPONCLASS_SHOTGUN;

	case ARMOURY_M249:
		return WEAPONCLASS_MACHINEGUN;

	default:
		break;
	}

	return WEAPONCLASS_NONE;
}

// Return true if given weapon ID is a primary weapon
bool IsPrimaryWeapon(int id)
{
	switch (id)
	{
	case WEAPON_SCOUT:
	case WEAPON_XM1014:
	case WEAPON_MAC10:
	case WEAPON_AUG:
	case WEAPON_UMP45:
	case WEAPON_SG550:
	case WEAPON_GALIL:
	case WEAPON_FAMAS:
	case WEAPON_AWP:
	case WEAPON_MP5N:
	case WEAPON_M249:
	case WEAPON_M3:
	case WEAPON_M4A1:
	case WEAPON_TMP:
	case WEAPON_G3SG1:
	case WEAPON_SG552:
	case WEAPON_AK47:
	case WEAPON_P90:
	case WEAPON_SHIELDGUN:
		return true;
	default:
		break;
	}

	return false;
}

// Return true if given weapon ID is a secondary weapon
bool IsSecondaryWeapon(int id)
{
	switch (id)
	{
	case WEAPON_P228:
	case WEAPON_ELITE:
	case WEAPON_FIVESEVEN:
	case WEAPON_USP:
	case WEAPON_GLOCK18:
	case WEAPON_DEAGLE:
		return true;
	default:
		break;
	}

	return false;
}

// Return true if given weapon ID is a grenade
bool IsGrenadeWeapon(int id)
{
	switch (id)
	{
	case WEAPON_HEGRENADE:
	case WEAPON_FLASHBANG:
	case WEAPON_SMOKEGRENADE:
		return true;
	default:
		break;
	}

	return false;
}

WeaponInfoStruct *GetWeaponInfo(int weaponID)
{
	for (auto& info : g_weaponInfo) {
		if (info.id == weaponID) {
			return &info;
		}
	}

	return nullptr;
}

WeaponInfoStruct *GetWeaponInfo(const char *weaponName)
{
	for (auto& info : g_weaponInfo) {
		if (!Q_stricmp(info.entityName, weaponName)) {
			return &info;
		}
	}

	return nullptr;
}

AmmoInfoStruct *GetAmmoInfo(const char *ammoName)
{
	for (auto& info : g_ammoInfo) {
		if (!Q_stricmp(info.ammoName1, ammoName)) {
			return &info;
		}
	}

	return nullptr;
}

AmmoInfoStruct *GetAmmoInfo(AmmoType ammoID)
{
	for (auto& info : g_ammoInfo) {
		if (info.ammoType == ammoID) {
			return &info;
		}
	}

	return nullptr;
}

void WeaponInfoReset()
{
	Q_memcpy(g_weaponInfo, g_weaponInfo_default, sizeof(g_weaponInfo));
	Q_memcpy(g_ammoInfo, g_ammoInfo_default, sizeof(g_ammoInfo));
}

WeaponSlotInfo *GetWeaponSlot(WeaponIdType weaponID)
{
	for (auto& infoSlot : g_weaponSlotInfo) {
		if (infoSlot.id == weaponID) {
			return &infoSlot;
		}
	}

	return nullptr;
}

WeaponSlotInfo *GetWeaponSlot(const char *weaponName)
{
	for (auto& infoSlot : g_weaponSlotInfo) {
		if (!Q_stricmp(infoSlot.weaponName, weaponName)) {
			return &infoSlot;
		}
	}

	return nullptr;
}

bool CanBuyWeaponByMaptype(int playerTeam, WeaponIdType weaponID, bool useAssasinationRestrictions)
{
	if (useAssasinationRestrictions)
	{
		if (playerTeam == CT)
		{
			switch (weaponID)
			{
			case WEAPON_P228:
			case WEAPON_XM1014:
			case WEAPON_AUG:
			case WEAPON_FIVESEVEN:
			case WEAPON_UMP45:
			case WEAPON_SG550:
			case WEAPON_FAMAS:
			case WEAPON_USP:
			case WEAPON_GLOCK18:
			case WEAPON_MP5N:
			case WEAPON_M249:
			case WEAPON_M3:
			case WEAPON_M4A1:
			case WEAPON_TMP:
			case WEAPON_DEAGLE:
			case WEAPON_P90:
			case WEAPON_SHIELDGUN:
				return true;
			default:
				return false;
			}
		}
		else if (playerTeam == TERRORIST)
		{
			switch (weaponID)
			{
			case WEAPON_P228:
			case WEAPON_MAC10:
			case WEAPON_ELITE:
			case WEAPON_UMP45:
			case WEAPON_GALIL:
			case WEAPON_USP:
			case WEAPON_GLOCK18:
			case WEAPON_AWP:
			case WEAPON_DEAGLE:
			case WEAPON_AK47:
				return true;
			default:
				return false;
			}
		}

		return false;
	}
	if (playerTeam == CT)
	{
		switch (weaponID)
		{
		case WEAPON_P228:
		case WEAPON_SCOUT:
		case WEAPON_XM1014:
		case WEAPON_AUG:
		case WEAPON_FIVESEVEN:
		case WEAPON_UMP45:
		case WEAPON_SG550:
		case WEAPON_FAMAS:
		case WEAPON_USP:
		case WEAPON_GLOCK18:
		case WEAPON_AWP:
		case WEAPON_MP5N:
		case WEAPON_M249:
		case WEAPON_M3:
		case WEAPON_M4A1:
		case WEAPON_TMP:
		case WEAPON_DEAGLE:
		case WEAPON_P90:
		case WEAPON_SHIELDGUN:
			return true;
		default:
			return false;
		}
	}
	else if (playerTeam == TERRORIST)
	{
		switch (weaponID)
		{
		case WEAPON_P228:
		case WEAPON_SCOUT:
		case WEAPON_XM1014:
		case WEAPON_MAC10:
		case WEAPON_ELITE:
		case WEAPON_UMP45:
		case WEAPON_GALIL:
		case WEAPON_USP:
		case WEAPON_GLOCK18:
		case WEAPON_AWP:
		case WEAPON_MP5N:
		case WEAPON_M249:
		case WEAPON_M3:
		case WEAPON_G3SG1:
		case WEAPON_DEAGLE:
		case WEAPON_SG552:
		case WEAPON_AK47:
		case WEAPON_P90:
			return true;
		default:
			return false;
		}
	}

	return false;
}
