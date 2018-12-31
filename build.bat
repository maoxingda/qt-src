@echo off

echo    (1)	build
echo    (2)	configure
echo    (3)	configure and build
echo    (4)	quit

choice /n /c 1234 /m "Please select"

if errorlevel 4 goto quit
if errorlevel 3 goto all
if errorlevel 2 goto configure
if errorlevel 1 goto build
	
:all
	configure -opensource -confirm-license -debug -shared -fast -no-qt3support && jom -l -j 4
	goto quit

:build
	jom -j 4
	goto quit
	
:configure
	configure -opensource -confirm-license -debug -shared -fast -no-qt3support
	goto quit
	
:quit