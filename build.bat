call "E:\VS\VC\Auxiliary\Build\vcvarsall.bat" x64

set "folderPath=E:\Bengine\bengine"
if not exist "%folderPath%\build" (
    mkdir "%folderPath%\build"
)

set "compilerFlag=E:\glew-2.2.0\lib\Release\x64\glew32.lib user32.lib gdi32.lib opengl32.lib"
set "outputFile=%folderPath%\build\main.exe"
set "inputFiles=%folderPath%\main.c"
set "dllFile=%folderPath%\build\objects.dll"
set "libFile=%folderPath%\build\objects.lib"

rem Compile objects.c into a DLL
cl /LD %folderPath%\renderer\objects.c /I"E:\glew-2.2.0\include" /Fe:%dllFile% /link %compilerFlag%

rem Link the main executable with the .lib file
cl %inputFiles% /EHsc /I"E:\glew-2.2.0\include" /Fe:%outputFile% /link %compilerFlag% /LIBPATH:%folderPath%\build %folderPath%\build\objects.lib
del *.obj