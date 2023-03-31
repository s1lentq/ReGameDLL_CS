#----------------------------------------
# 1. Preparing build:
#    rm -rf build
#    mkdir build && cd build
#
# 2. Select compiler and build it
# - Compile with Clang:
#    CC="clang" CXX="clang++" cmake ..
#    make
#
# - Compile with Intel C++ Compiler:
#    CC="icc" CXX="icpc" cmake ..
#    make
#
# - Compile with GCC Compiler:
#    cmake ..
#    make
#----------------------------------------

cmake_minimum_required(VERSION 3.1)
project(regamedll CXX)

option(DEBUG "Build with debug information." OFF)
option(USE_STATIC_LIBSTDC "Enables static linking libstdc++." OFF)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Avoid -rdynamic -fPIC options
set(CMAKE_SHARED_LIBRARY_CXX_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

set(COMPILE_FLAGS "-m32 -U_FORTIFY_SOURCE")
set(LINK_FLAGS "-m32 -s")

set(COMPILE_FLAGS "${COMPILE_FLAGS} -Wall -fno-exceptions -fno-builtin -Wno-unknown-pragmas")

# Remove noxref code and data
set(COMPILE_FLAGS "${COMPILE_FLAGS} -ffunction-sections -fdata-sections")

if (DEBUG)
	set(COMPILE_FLAGS "${COMPILE_FLAGS} -g3 -O3 -ggdb")
else()
	set(COMPILE_FLAGS "${COMPILE_FLAGS} -g0 -O3 -fno-stack-protector")
endif()

# Check Intel C++ compiler
if ("$ENV{CXX}" MATCHES "icpc")
	#
	# -fp-model=precise
	# ICC uses -fp-model fast=1 by default for more aggressive optimizations on floating-point calculations
	# https://software.intel.com/content/www/us/en/develop/documentation/cpp-compiler-developer-guide-and-reference/top/compiler-reference/compiler-options/compiler-option-details/floating-point-options/fp-model-fp.html#fp-model-fp_GUID-99936BBA-1508-4E9F-AC09-FA98613CE2F5
	#
	set(COMPILE_FLAGS "${COMPILE_FLAGS} \
		-fp-model=precise\
		-fasm-blocks\
		-Qoption,cpp,--treat_func_as_string_literal_cpp")

	#
	# -qno-opt-class-analysis
	# Don't use c++ class hierarchy for analyze and resolve C++ virtual function calls at compile time
	#
	# Example issue:
	# Expected: FF .. call dword ptr + offset, pEntity->Spawn();
	# Got:      E8 .. call CBaseEntity::Spawn();
	#
	set(LINK_FLAGS "${LINK_FLAGS} \
		-qno-opt-class-analysis\
		-static-intel\
		-no-intel-extensions")

	if (NOT DEBUG)
		set(COMPILE_FLAGS "${COMPILE_FLAGS} -ipo")
		set(LINK_FLAGS "${LINK_FLAGS} -ipo")
	endif()
else()
	# Produce code optimized for the most common IA32/AMD64/EM64T processors.
	# As new processors are deployed in the marketplace, the behavior of this option will change.
	set(COMPILE_FLAGS "${COMPILE_FLAGS} \
		-mtune=generic -msse3\
		-fpermissive -fno-sized-deallocation\
		-Wno-delete-non-virtual-dtor -Wno-invalid-offsetof\
		-Wno-unused-variable -Wno-unused-value -Wno-unused-result -Wno-unused-function\
		-Wno-write-strings -Wno-switch -Wno-enum-compare\
		-Wno-sign-compare -Wno-format -Wno-ignored-attributes -Wno-strict-aliasing")

	# Check Clang compiler
	if ("$ENV{CXX}" MATCHES "clang")
		set(COMPILE_FLAGS "${COMPILE_FLAGS} \
			-Wno-unused-local-typedef\
			-Wno-unused-private-field\
			-fno-strict-vtable-pointers\
			-Wno-overloaded-virtual")
	else()
		set(COMPILE_FLAGS "${COMPILE_FLAGS} \
			-fno-plt\
			-fno-devirtualize\
			-Wno-unused-local-typedefs\
			-Wno-unused-but-set-variable")

		# GCC >= 8.3
		if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 8.0)
			set(COMPILE_FLAGS "${COMPILE_FLAGS} -Wno-stringop-truncation -Wno-format-truncation -Wno-class-memaccess")
		endif()
	endif()
endif()

# GCC >= 8.3
if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 8.0)
	set(COMPILE_FLAGS "${COMPILE_FLAGS} -fcf-protection=none")
endif()

if (NOT DEBUG)
	set(LINK_FLAGS "${LINK_FLAGS} \
		-Wl,-gc-sections -Wl,--version-script=\"${PROJECT_SOURCE_DIR}/../version_script.lds\"")
endif()

set(PROJECT_SRC_DIR
	"${PROJECT_SOURCE_DIR}"
	"${PROJECT_SOURCE_DIR}/engine"
	"${PROJECT_SOURCE_DIR}/common"
	"${PROJECT_SOURCE_DIR}/dlls"
	"${PROJECT_SOURCE_DIR}/game_shared"
	"${PROJECT_SOURCE_DIR}/pm_shared"
	"${PROJECT_SOURCE_DIR}/regamedll"
	"${PROJECT_SOURCE_DIR}/unittests"
)

set(PROJECT_CPPUNITLITE_DIR
	"${PROJECT_SOURCE_DIR}/../dep/cppunitlite/include"
)

set(PROJECT_PUBLIC_DIR
	"${PROJECT_SOURCE_DIR}/public"
	"${PROJECT_SOURCE_DIR}/public/regamedll"
)

set(ENGINE_SRCS
	"engine/unicode_strtools.cpp"
)

set(SHARED_SRCS
	"game_shared/shared_util.cpp"
	"game_shared/voice_gamemgr.cpp"
	"game_shared/bot/bot.cpp"
	"game_shared/bot/bot_manager.cpp"
	"game_shared/bot/bot_profile.cpp"
	"game_shared/bot/bot_util.cpp"
	"game_shared/bot/nav_area.cpp"
	"game_shared/bot/nav_file.cpp"
	"game_shared/bot/nav_node.cpp"
	"game_shared/bot/nav_path.cpp"
	"pm_shared/pm_debug.cpp"
	"pm_shared/pm_math.cpp"
	"pm_shared/pm_shared.cpp"
	"regamedll/regamedll.cpp"
	"regamedll/precompiled.cpp"
	"regamedll/public_amalgamation.cpp"
	"regamedll/hookchains_impl.cpp"
	"regamedll/sse_mathfun.cpp"
	"public/FileSystem.cpp"
	"public/interface.cpp"
	"public/MemPool.cpp"
)

set(GAMEDLL_SRCS
	"dlls/airtank.cpp"
	"dlls/ammo.cpp"
	"dlls/animating.cpp"
	"dlls/animation.cpp"
	"dlls/basemonster.cpp"
	"dlls/bmodels.cpp"
	"dlls/buttons.cpp"
	"dlls/career_tasks.cpp"
	"dlls/cbase.cpp"
	"dlls/client.cpp"
	"dlls/cmdhandler.cpp"
	"dlls/combat.cpp"
	"dlls/debug.cpp"
	"dlls/doors.cpp"
	"dlls/effects.cpp"
	"dlls/explode.cpp"
	"dlls/func_break.cpp"
	"dlls/func_tank.cpp"
	"dlls/game.cpp"
	"dlls/gamerules.cpp"
	"dlls/ggrenade.cpp"
	"dlls/gib.cpp"
	"dlls/globals.cpp"
	"dlls/h_battery.cpp"
	"dlls/h_cycler.cpp"
	"dlls/h_export.cpp"
	"dlls/healthkit.cpp"
	"dlls/hintmessage.cpp"
	"dlls/items.cpp"
	"dlls/lights.cpp"
	"dlls/mapinfo.cpp"
	"dlls/maprules.cpp"
	"dlls/mortar.cpp"
	"dlls/multiplay_gamerules.cpp"
	"dlls/observer.cpp"
	"dlls/pathcorner.cpp"
	"dlls/plats.cpp"
	"dlls/player.cpp"
	"dlls/revert_saved.cpp"
	"dlls/saverestore.cpp"
	"dlls/singleplay_gamerules.cpp"
	"dlls/skill.cpp"
	"dlls/sound.cpp"
	"dlls/soundent.cpp"
	"dlls/spectator.cpp"
	"dlls/subs.cpp"
	"dlls/training_gamerules.cpp"
	"dlls/triggers.cpp"
	"dlls/tutor.cpp"
	"dlls/tutor_base_states.cpp"
	"dlls/tutor_base_tutor.cpp"
	"dlls/tutor_cs_states.cpp"
	"dlls/tutor_cs_tutor.cpp"
	"dlls/util.cpp"
	"dlls/vehicle.cpp"
	"dlls/weapons.cpp"
	"dlls/weapontype.cpp"
	"dlls/world.cpp"
	"dlls/API/CAPI_Impl.cpp"
	"dlls/API/CSEntity.cpp"
	"dlls/API/CSPlayer.cpp"
	"dlls/API/CSPlayerItem.cpp"
	"dlls/addons/item_airbox.cpp"
	"dlls/addons/point_command.cpp"
	"dlls/addons/trigger_random.cpp"
	"dlls/addons/trigger_setorigin.cpp"
	"dlls/wpn_shared/wpn_ak47.cpp"
	"dlls/wpn_shared/wpn_aug.cpp"
	"dlls/wpn_shared/wpn_awp.cpp"
	"dlls/wpn_shared/wpn_c4.cpp"
	"dlls/wpn_shared/wpn_deagle.cpp"
	"dlls/wpn_shared/wpn_elite.cpp"
	"dlls/wpn_shared/wpn_famas.cpp"
	"dlls/wpn_shared/wpn_fiveseven.cpp"
	"dlls/wpn_shared/wpn_flashbang.cpp"
	"dlls/wpn_shared/wpn_g3sg1.cpp"
	"dlls/wpn_shared/wpn_galil.cpp"
	"dlls/wpn_shared/wpn_glock18.cpp"
	"dlls/wpn_shared/wpn_hegrenade.cpp"
	"dlls/wpn_shared/wpn_knife.cpp"
	"dlls/wpn_shared/wpn_m3.cpp"
	"dlls/wpn_shared/wpn_m4a1.cpp"
	"dlls/wpn_shared/wpn_m249.cpp"
	"dlls/wpn_shared/wpn_mac10.cpp"
	"dlls/wpn_shared/wpn_mp5navy.cpp"
	"dlls/wpn_shared/wpn_p90.cpp"
	"dlls/wpn_shared/wpn_p228.cpp"
	"dlls/wpn_shared/wpn_scout.cpp"
	"dlls/wpn_shared/wpn_sg550.cpp"
	"dlls/wpn_shared/wpn_sg552.cpp"
	"dlls/wpn_shared/wpn_smokegrenade.cpp"
	"dlls/wpn_shared/wpn_tmp.cpp"
	"dlls/wpn_shared/wpn_ump45.cpp"
	"dlls/wpn_shared/wpn_usp.cpp"
	"dlls/wpn_shared/wpn_xm1014.cpp"
	"dlls/bot/cs_bot.cpp"
	"dlls/bot/cs_bot_chatter.cpp"
	"dlls/bot/cs_bot_event.cpp"
	"dlls/bot/cs_bot_init.cpp"
	"dlls/bot/cs_bot_learn.cpp"
	"dlls/bot/cs_bot_listen.cpp"
	"dlls/bot/cs_bot_manager.cpp"
	"dlls/bot/cs_bot_nav.cpp"
	"dlls/bot/cs_bot_pathfind.cpp"
	"dlls/bot/cs_bot_radio.cpp"
	"dlls/bot/cs_bot_statemachine.cpp"
	"dlls/bot/cs_bot_update.cpp"
	"dlls/bot/cs_bot_vision.cpp"
	"dlls/bot/cs_bot_weapon.cpp"
	"dlls/bot/cs_gamestate.cpp"
	"dlls/bot/states/cs_bot_attack.cpp"
	"dlls/bot/states/cs_bot_buy.cpp"
	"dlls/bot/states/cs_bot_defuse_bomb.cpp"
	"dlls/bot/states/cs_bot_escape_from_bomb.cpp"
	"dlls/bot/states/cs_bot_fetch_bomb.cpp"
	"dlls/bot/states/cs_bot_follow.cpp"
	"dlls/bot/states/cs_bot_hide.cpp"
	"dlls/bot/states/cs_bot_hunt.cpp"
	"dlls/bot/states/cs_bot_idle.cpp"
	"dlls/bot/states/cs_bot_investigate_noise.cpp"
	"dlls/bot/states/cs_bot_move_to.cpp"
	"dlls/bot/states/cs_bot_plant_bomb.cpp"
	"dlls/bot/states/cs_bot_use_entity.cpp"
	"dlls/hostage/hostage.cpp"
	"dlls/hostage/hostage_improv.cpp"
	"dlls/hostage/hostage_localnav.cpp"
	"dlls/hostage/states/hostage_animate.cpp"
	"dlls/hostage/states/hostage_escape.cpp"
	"dlls/hostage/states/hostage_follow.cpp"
	"dlls/hostage/states/hostage_idle.cpp"
	"dlls/hostage/states/hostage_retreat.cpp"
)

set(UNITTESTS_SRCS
	"unittests/animation_tests.cpp"
	"unittests/struct_offsets_tests.cpp"
	"unittests/TestRunner.cpp"
)

if (CMAKE_BUILD_TYPE MATCHES Unittests)
	if (NOT TARGET cppunitlite)
		add_subdirectory(../dep/cppunitlite cppunitlite)
	endif()

	set(LINK_FLAGS "${LINK_FLAGS} -no-pie -Wl,--no-export-dynamic")
	add_executable(regamedll ${appversion.sh})
else()
	add_library(regamedll SHARED ${appversion.sh})
endif()

if (NOT TARGET appversion)
	add_custom_target(appversion DEPENDS COMMAND "${PROJECT_SOURCE_DIR}/version/appversion.sh" "${PROJECT_SOURCE_DIR}/..")
endif()

add_dependencies(regamedll appversion)

target_include_directories(regamedll PRIVATE
	${PROJECT_SRC_DIR}
	${PROJECT_CPPUNITLITE_DIR}
	${PROJECT_PUBLIC_DIR}
)

target_compile_definitions(regamedll PRIVATE
	REGAMEDLL_FIXES
	REGAMEDLL_API
	REGAMEDLL_ADD
	UNICODE_FIXES
	BUILD_LATEST
	CLIENT_WEAPONS
	USE_QSTRING
	_LINUX
	LINUX
	NDEBUG
	_GLIBCXX_USE_CXX11_ABI=0
	_stricmp=strcasecmp
	_strnicmp=strncasecmp
	_strdup=strdup
	_unlink=unlink
	_vsnprintf=vsnprintf
	_write=write
	_close=close
	_access=access
	_vsnwprintf=vswprintf
)

target_sources(regamedll PRIVATE
	${GAMEDLL_SRCS}
	${ENGINE_SRCS}
	${SHARED_SRCS}

	$<$<CONFIG:Unittests>:
	${UNITTESTS_SRCS}>
)

target_link_libraries(regamedll PRIVATE
	dl
	aelf32

	$<$<CONFIG:Unittests>:cppunitlite>
)

if (USE_STATIC_LIBSTDC)
	target_compile_definitions(regamedll PRIVATE BUILD_STATIC_LIBSTDC)
	set(LINK_FLAGS "${LINK_FLAGS} -static-libgcc -static-libstdc++")
endif()

set(LINK_FLAGS "${LINK_FLAGS} \
	-Wl,-rpath,'$ORIGIN/.' \
	-L${PROJECT_SOURCE_DIR}/lib/linux32")

set_target_properties(regamedll PROPERTIES
	OUTPUT_NAME cs
	PREFIX ""
	COMPILE_FLAGS ${COMPILE_FLAGS}
	LINK_FLAGS ${LINK_FLAGS}
	POSITION_INDEPENDENT_CODE OFF
)
