cmake_minimum_required(VERSION 3.1)
project(regamedll CXX)

option(DEBUG "Build debug application." OFF)
option(USE_INTEL_COMPILER "Use the Intel compiler." OFF)
option(USE_CLANG_COMPILER "Use the Clang compiler." OFF)
option(USE_STATIC_LIBSTDC "Enables static linking libstdc++." OFF)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (USE_INTEL_COMPILER)
	set(CMAKE_C_COMPILER	"/opt/intel/bin/icc")
	set(CMAKE_CXX_COMPILER	"/opt/intel/bin/icpc")
elseif (USE_CLANG_COMPILER)
	set(CMAKE_C_COMPILER	"/usr/bin/clang")
	set(CMAKE_CXX_COMPILER	"/usr/bin/clang++")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions")

if (USE_INTEL_COMPILER OR USE_CLANG_COMPILER)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fasm-blocks")
endif()

if (DEBUG)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -ggdb -O3 -Wall -ffunction-sections -fdata-sections")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g0 -O3 -fno-rtti -ffunction-sections -fdata-sections")
endif()

if (USE_INTEL_COMPILER)
	set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static-intel -no-intel-extensions")
else()
	## Produce code optimized for the most common IA32/AMD64/EM64T processors.
	## As new processors are deployed in the marketplace, the behavior of this option will change.
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}\
		-mtune=generic -msse3\
		-Wno-write-strings -Wno-invalid-offsetof\
		-Wno-unused-variable -Wno-unused-function\
		-Wno-unused-result -Wno-invalid-offsetof\
		-fpermissive -Wno-switch -Wno-enum-compare\
		-Wno-unknown-pragmas -Wno-unused-value")

	if (USE_CLANG_COMPILER)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}\
			-Wno-unused-local-typedef\
			-Wno-unused-private-field\
			-fno-strict-vtable-pointers\
			-Wno-overloaded-virtual")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}\
			-Wno-unused-local-typedefs\
			-Wno-sign-compare\
			-Wno-strict-aliasing\
			-Wno-unused-but-set-variable\
			-fno-devirtualize")
	endif()
endif()

if (NOT DEBUG AND USE_STATIC_LIBSTDC)
	set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-gc-sections -Wl,--version-script=${PROJECT_SOURCE_DIR}/../version_script.lds")
endif()

if (USE_STATIC_LIBSTDC)
	add_definitions(-DBUILD_STATIC_LIBSTDC)
	set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static-libgcc -static-libstdc++")
endif()

set(PROJECT_SRC_DIR
	"${PROJECT_SOURCE_DIR}"
	"${PROJECT_SOURCE_DIR}/engine"
	"${PROJECT_SOURCE_DIR}/common"
	"${PROJECT_SOURCE_DIR}/dlls"
	"${PROJECT_SOURCE_DIR}/game_shared"
	"${PROJECT_SOURCE_DIR}/pm_shared"
	"${PROJECT_SOURCE_DIR}/regamedll"
)

set(PROJECT_PUBLIC_DIR
	"${PROJECT_SOURCE_DIR}/public"
	"${PROJECT_SOURCE_DIR}/public/regamedll"
)

set(ENGINE_SRCS
	"engine/unicode_strtools.cpp"
)

file(GLOB SHARED_SRCS
	"game_shared/bot/*.cpp"
	"game_shared/*.cpp"
	"pm_shared/*.cpp"
	"regamedll/*.cpp"
	"public/FileSystem.cpp"
	"public/interface.cpp"
	"public/MemPool.cpp"
	"version/version.cpp"
)

list(REMOVE_ITEM SHARED_SRCS EXCLUDE "${PROJECT_SOURCE_DIR}/regamedll/classes_dummy.cpp")

file(GLOB GAMEDLL_SRCS
	"dlls/*.cpp"
	"dlls/API/*.cpp"
	"dlls/addons/*.cpp"
	"dlls/wpn_shared/*.cpp"
	"dlls/bot/*.cpp"
	"dlls/bot/states/*.cpp"
	"dlls/hostage/*.cpp"
	"dlls/hostage/states/*.cpp"
)

include_directories(
	${PROJECT_SRC_DIR}
	${PROJECT_PUBLIC_DIR}
)

link_directories(${PROJECT_SOURCE_DIR}/lib/linux32)

add_definitions(
	-DREGAMEDLL_FIXES
	-DBUILD_LATEST
	-DREGAMEDLL_ADD
	-DREGAMEDLL_API
	-DUNICODE_FIXES
	-DCLIENT_WEAPONS
	-DUSE_QSTRING
	-DGNUC
	-DPOSIX
	-D_LINUX
	-DLINUX
	-D_stricmp=strcasecmp
	-D_strnicmp=strncasecmp
	-D_strdup=strdup
	-D_unlink=unlink
	-D_vsnprintf=vsnprintf
	-D_write=write
	-D_close=close
	-D_access=access
	-D_vsnwprintf=vswprintf
)

add_library(regamedll SHARED ${appversion.sh} ${GAMEDLL_SRCS} ${ENGINE_SRCS} ${SHARED_SRCS})
set_property(TARGET regamedll PROPERTY LIBRARY_OUTPUT_NAME cs)
add_custom_target(appversion COMMAND ${PROJECT_SOURCE_DIR}/version/appversion.sh ${PROJECT_SOURCE_DIR} regamedll)
set_target_properties(regamedll PROPERTIES PREFIX "" COMPILE_FLAGS "-m32" LINK_FLAGS "-m32" POSITION_INDEPENDENT_CODE ON)
target_link_libraries(regamedll dl aelf32)
add_dependencies(regamedll appversion)
