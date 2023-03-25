@ECHO OFF

if not exist Build mkdir Build

pushd Build

set PROGAM=Game
set INCLUDE_FLAGS=-I..\External\raylib\include
set COMPILER_FLAGS=-MD
set LINK_FLAGS=-LIBPATH:..\External\raylib\lib raylib.lib winmm.lib user32.lib gdi32.lib shell32.lib -SUBSYSTEM:CONSOLE

cl %COMPILER_FLAGS% -Fe%PROGAM% ..\Code\*.cpp %INCLUDE_FLAGS% -link%LINK_FLAGS%



popd