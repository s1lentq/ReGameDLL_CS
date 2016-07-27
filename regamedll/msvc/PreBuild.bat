@setlocal enableextensions enabledelayedexpansion
@echo off
::
:: Pre-build auto-versioning script
::

set srcdir=%~1
set repodir=%~2

set old_version=
set old_specialbuild=""
set version_revision=0
set version_specialbuild=
set version_id_commit=
set version_author_commit=
set version_pdate_1=%date:~-4%-%date:~3,2%-%date:~0,2%
set version_pdate=%version_pdate_1%%time:~0,2%:%time:~3,2%:%time:~6,2%
set version_pdate_2=%time:~0,2%-%time:~3,2%-%time:~6,2%
set version_pdate_2=%version_pdate_2: =%
set version_date=%version_pdate_1%__%version_pdate_2%
set version_major=0
set version_minor=0
set version_specialversion=
set url_commit=
set branch_name=master

::
:: Check for git.exe presence
::
CALL git.exe describe >NUL 2>&1
set errlvl="%ERRORLEVEL%"

::
:: Read old appversion.h, if present
::
IF EXIST "%srcdir%\appversion.h" (
	FOR /F "usebackq tokens=1,2,3" %%i in ("%srcdir%\appversion.h") do (
		IF %%i==#define (
			IF %%j==APP_VERSION_C set old_version=%%k
			IF %%j==APP_VERSION_SPECIALBUILD set old_specialbuild=%%k
		)
	)
)

IF %errlvl% == "1" (
	echo can't locate git.exe - auto-versioning step won't be performed

	:: if we haven't appversion.h, we need to create it
	IF NOT "%old_version%" == "" (
		set version_revision=0
	)
)

::
:: Read major, minor and maintenance version components from Version.h
::
IF EXIST "%srcdir%\version.h" (
	FOR /F "usebackq tokens=1,2,3" %%i in ("%srcdir%\version.h") do (
		IF %%i==#define (
			IF %%j==VERSION_MAJOR set version_major=%%k
			IF %%j==VERSION_MINOR set version_minor=%%k
			IF %%j==VERSION_SPECIALVERSION set version_specialversion=%%k
		)
	)
) ELSE (
	FOR /F "usebackq tokens=1,2,3,* delims==" %%i in ("%repodir%..\gradle.properties") do (
		IF NOT [%%j] == [] (
			IF %%i==majorVersion set version_major=%%j
			IF %%i==minorVersion set version_minor=%%j
			IF %%i==specialVersion set version_specialversion=%%j
		)
	)
)

::
:: Read revision and release date from it
::
IF NOT %errlvl% == "1" (
	:: Get current branch
	FOR /F "tokens=*" %%i IN ('"git -C "%repodir%\." rev-parse --abbrev-ref HEAD"') DO (
		set branch_name=%%i
	)

	FOR /F "tokens=*" %%i IN ('"git -C "%repodir%\." rev-list --count !branch_name!"') DO (
		IF NOT [%%i] == [] (
			set version_revision=%%i
		)
	)
)

::
:: Now form full version string like 1.0.0.1
::

set new_version=%version_major%,%version_minor%,0,%version_revision%

::
:: Get remote url repository
::
IF NOT %errlvl% == "1" (

	set branch_remote=origin
	:: Get remote name by current branch
	FOR /F "tokens=*" %%i IN ('"git -C "%repodir%\." config branch.!branch_name!.remote"') DO (
		set branch_remote=%%i
	)
	:: Get remote url
	FOR /F "tokens=2 delims=@" %%i IN ('"git -C "%repodir%\." config remote.!branch_remote!.url"') DO (
		set url_commit=%%i
	)
	:: Get author last no-merge commit
	FOR /F "tokens=*" %%i IN ('"git -C "%repodir%\." log -1 --no-merges --pretty=format:%%an"') DO (
		set version_author_commit=%%i
	)
	:: Get commit id
	FOR /F "tokens=*" %%i IN ('"git -C "%repodir%\." rev-parse --verify HEAD"') DO (
		set var=%%i
		set version_id_commit=!var:~0,+7!
	)

	IF [!url_commit!] == [] (

		FOR /F "tokens=1" %%i IN ('"git -C "%repodir%\." config remote.!branch_remote!.url"') DO (
			set url_commit=%%i
		)

		:: strip .git
		if "x!url_commit:~-4!"=="x.git" (
			set url_commit=!url_commit:~0,-4!
		)

		:: append extra string
		If NOT "%url_commit%"=="%url_commit:bitbucket.org=%" (
			set url_commit=!url_commit!/commits/
		) ELSE (
			set url_commit=!url_commit!/commit/
		)

	) ELSE (
		:: strip .git
		if "x!url_commit:~-4!"=="x.git" (
			set url_commit=!url_commit:~0,-4!
		)
		:: replace : to /
		set url_commit=!url_commit::=/!

		:: append extra string
		If NOT "%url_commit%"=="%url_commit:bitbucket.org=%" (
			set url_commit=https://!url_commit!/commits/
		) ELSE (
			set url_commit=https://!url_commit!/commit/
		)
	)
)

::
:: Detect local modifications
::
set localChanged=0
IF NOT %errlvl% == "1" (
	FOR /F "tokens=*" %%i IN ('"git -C "%repodir%\." ls-files -m"') DO (
		set localChanged=1
	)
)

IF [%localChanged%]==[1] (
	IF NOT [%version_specialversion%] == [] (
		set version_specialbuild=%version_specialversion%
	) ELSE (
		set version_specialbuild=m
	)
) ELSE (
	set version_specialbuild=
)

::
:: Update appversion.h if version has changed or modifications/mixed revisions detected
::
IF NOT "%new_version%"=="%old_version%" goto _update
IF NOT "%version_specialbuild%"==%old_specialbuild% goto _update
goto _exit

:_update
echo Updating appversion.h, new version is "%new_version%", the old one was "%old_version%"
echo new special build is "%version_specialbuild%", the old one was %old_specialbuild%

echo #ifndef __APPVERSION_H__>"%srcdir%\appversion.h"
echo #define __APPVERSION_H__>>"%srcdir%\appversion.h"
echo.>>"%srcdir%\appversion.h"
echo // >>"%srcdir%\appversion.h"
echo // This file is generated automatically.>>"%srcdir%\appversion.h"
echo // Don't edit it.>>"%srcdir%\appversion.h"
echo // >>"%srcdir%\appversion.h"
echo.>>"%srcdir%\appversion.h"
echo // Version defines>>"%srcdir%\appversion.h"

IF "%version_specialversion%" == "" (
	echo #define APP_VERSION_D %version_major%.%version_minor%.%version_revision% >>"%srcdir%\appversion.h"
	echo #define APP_VERSION_STRD "%version_major%.%version_minor%.%version_revision%">>"%srcdir%\appversion.h"
	echo #define APP_VERSION_STRD_RC "%version_major%.%version_minor%.%version_revision%">>"%srcdir%\appversion.h"
	echo #define APP_VERSION_C %version_major%,%version_minor%,0,%version_revision% >>"%srcdir%\appversion.h"
	echo #define APP_VERSION_STRCS "%version_major%,%version_minor%,0,%version_revision%">>"%srcdir%\appversion.h"
) ELSE (
	echo #define APP_VERSION_D %version_major%.%version_minor%.%version_maintenance%.%version_revision% >>"%srcdir%\appversion.h"
	echo #define APP_VERSION_STRD "%version_major%.%version_minor%.%version_maintenance%.%version_revision%">>"%srcdir%\appversion.h"
	echo #define APP_VERSION_STRD_RC "%version_major%.%version_minor%.%version_maintenance%.%version_revision%">>"%srcdir%\appversion.h"
	echo #define APP_VERSION_C %version_major%,%version_minor%,%version_maintenance%,%version_revision% >>"%srcdir%\appversion.h"
	echo #define APP_VERSION_STRCS "%version_major%,%version_minor%,%version_maintenance%,%version_revision%">>"%srcdir%\appversion.h"
)

echo.>>"%srcdir%\appversion.h"
echo #define APP_VERSION_DATE %version_date%>>"%srcdir%\appversion.h"
echo #define APP_VERSION_DATE_STR "%version_date%">>"%srcdir%\appversion.h"
echo #define APP_VERSION_PDATE_STR "%version_pdate%">>"%srcdir%\appversion.h"
echo #define APP_VERSION_YMD_STR "%version_pdate_1%">>"%srcdir%\appversion.h"
echo.>>"%srcdir%\appversion.h"
echo #define APP_COMMIT_AUTHOR "(%version_author_commit%)">>"%srcdir%\appversion.h"
echo #define APP_COMMIT_ID "%version_id_commit%">>"%srcdir%\appversion.h"
echo #define APP_COMMITS_URL "%url_commit%">>"%srcdir%\appversion.h"
echo.>>"%srcdir%\appversion.h"

IF NOT "%version_specialbuild%" == "" (
	echo #define APP_VERSION_FLAGS VS_FF_SPECIALBUILD>>"%srcdir%\appversion.h"
	echo #define APP_VERSION_SPECIALBUILD "%version_specialbuild%">>"%srcdir%\appversion.h"
	echo #define APP_VERSION APP_VERSION_STRD "" APP_VERSION_SPECIALBUILD>>"%srcdir%\appversion.h"
) ELSE (
	echo #define APP_VERSION_FLAGS 0x0L>>"%srcdir%\appversion.h"
	echo #define APP_VERSION APP_VERSION_STRD>>"%srcdir%\appversion.h"
)
echo.>>"%srcdir%\appversion.h"

echo #endif //__APPVERSION_H__>>"%srcdir%\appversion.h"
echo.>>"%srcdir%\appversion.h"

::
:: Do update of version.cpp file last modify time to force it recompile
::
copy /b "%srcdir%\version.cpp"+,, "%srcdir%\version.cpp"
endlocal

:_exit
exit /B 0