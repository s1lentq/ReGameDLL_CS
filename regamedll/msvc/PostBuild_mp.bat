@echo OFF
::
:: Post-build auto-deploy script
:: Create and fill PublishPath_mp.txt file with path to deployment folder
:: I.e. PublishPath_mp.txt should contain one line with a folder path
:: Call it so:
:: IF EXIST "$(ProjectDir)PostBuild_mp.bat" (CALL "$(ProjectDir)PostBuild_mp.bat" "$(TargetDir)" "$(TargetName)" "$(TargetExt)" "$(ProjectDir)")
::

SET targetDir=%~1
SET targetDirPlay=%targetDir:Play=%

SET targetName=%~2
SET targetExt=%~3
SET projectDir=%~4
SET destination=PublishPath_mp

IF NOT "%targetDir%"=="%targetDirPlay%" (
	SET destination=PublishPath_mp_play
)

IF NOT EXIST "%projectDir%\%destination%.txt" (
	ECHO 	No deployment path specified. Create %destination%.txt near PostBuild_mp.bat with paths on separate lines for auto deployment.
	exit /B 0
)

FOR /f "tokens=* delims= usebackq" %%a IN ("%projectDir%\%destination%.txt") DO (
	ECHO Deploying to: %%a
	IF NOT "%%a" == "" (
		copy /Y "%targetDir%%targetName%%targetExt%" "%%a"
		IF NOT ERRORLEVEL 1 (
			IF EXIST "%targetDir%%targetName%.pdb" (
				copy /Y "%targetDir%%targetName%.pdb" "%%a"
			)
		) ELSE (
			ECHO PostBuild_mp.bat ^(27^) : warning : Can't copy '%targetName%%targetExt%' to deploy path '%%a'
		)
	)
)

IF "%%a" == "" (
	ECHO 	No deployment path specified.
)

exit /B 0