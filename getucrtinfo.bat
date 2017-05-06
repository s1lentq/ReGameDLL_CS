@echo off

if defined VS150COMNTOOLS (
	if not exist "%VS150COMNTOOLS%vcvarsqueryregistry.bat" goto NoVS
	call "%VS150COMNTOOLS%vcvarsqueryregistry.bat"
	goto :run
) else if defined VS140COMNTOOLS (
	if not exist "%VS140COMNTOOLS%vcvarsqueryregistry.bat" goto NoVS
	call "%VS140COMNTOOLS%vcvarsqueryregistry.bat"
	goto :run
)

:NoVS
echo Error: Visual Studio 2015 or 2017 required.
exit /b 1

:run
echo %UniversalCRTSdkDir%
echo %UCRTVersion%
