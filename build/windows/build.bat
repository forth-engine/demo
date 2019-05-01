@echo off
cd ../cmake
devenv Forth-Engine-Master.sln /Build Release
IF ERRORLEVEL 1 GOTO back
cd demo/Release/
cls
demo.exe
cd ../..
:back
cd ../windows
@echo on