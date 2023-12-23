@echo off
setlocal enabledelayedexpansion
call "E:\VS\VC\Auxiliary\Build\vcvarsall.bat" x64
set "folderPath=E:\Bengine\bengine"
if not exist "%folderPath%\build" (
    mkdir "%folderPath%\build"
)
set "compilerFlag=E:\glew-2.2.0\lib\Release\x64\glew32.lib user32.lib gdi32.lib opengl32.lib"
set "outputFile=%folderPath%\build\main.exe"
set "dllOutputPath=%folderPath%\build"
set "cFiles=%folderPath%\renderer\objects.c %folderPath%\renderer\render.c %folderPath%\datastructs\heap.c"
for %%f in (%cFiles%) do (
    set "currentFile=%%~f"
    set "dllFile=!dllOutputPath!\%%~nf.dll"
    echo Compiling !currentFile! into !dllFile!
    cl /LD /WX !currentFile! /Fe:!dllFile!
)
cl /WX %folderPath%\main.c /EHsc /I"E:\glew-2.2.0\include" /Fe:%outputFile% /link %compilerFlag% /LIBPATH:%dllOutputPath% %dllOutputPath%\*.lib objects.lib
del /Q *.obj %dllOutputPath%\*.lib %dllOutputPath%\*.exp