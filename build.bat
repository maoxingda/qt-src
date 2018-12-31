@echo off

color 0b

call "C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\bin\vcvars32.bat"

:loop

echo    --------------------------------
echo    -  (q)	quit
echo    -  (b)	build
echo    -  (c)	configure
echo    -  (a)	configure and build
echo    --------------------------------

choice -cs -n -c qbca -m "Please select:"

if errorlevel 4 goto all
if errorlevel 3 goto configure
if errorlevel 2 goto build
if errorlevel 1 goto quit
	
:all
	configure -opensource -confirm-license -debug -shared -fast -no-qt3support && nmake -nologo
	goto loop

:build
	nmake -nologo
	goto loop
	
:configure
	configure -opensource -confirm-license -debug -shared -fast -no-qt3support -vcproj
	goto loop
	
:quit