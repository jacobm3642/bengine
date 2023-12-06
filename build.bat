call "E:\VS\VC\Auxiliary\Build\vcvarsall.bat" x64
set "folderPath=E:\Bengine\bengine"
if not exist "%folderPath%\build" (
    mkdir "%folderPath%\build"
)
set "compilerFlag=E:\glew-2.2.0\lib\Release\x64\glew32.lib user32.lib gdi32.lib opengl32.lib"
set "libraryPath=/LIBPATH:\"./renderer\""
set "outputFile=%folderPath%\build\main.exe"
set "shared_flags=/LD"
cl %shared_flags% %folderPath%/renderer/objects.c /Fe:%folderPath%/renderer/libobjects.dll
cl E:\Bengine\bengine\main.c /EHsc /I"E:\glew-2.2.0\include" /I"E:\glew-2.2.0\lib" /Fe:%outputFile% /link %compilerFlag% %libraryPath%
del main.obj
del objects.obj