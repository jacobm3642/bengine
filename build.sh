wd=$(pwd)

export LD_LIBRARY_PATH=$wd/renderer:$LD_LIBRARY_PATH

main_flags=" -Wall -Werror -lX11 -lGL -lGLU -lGLEW -L./renderer -lobjects"
shared_flags="-shared"

gcc $shared_flags ./renderer/objects.c -o ./renderer/libobjects.so
gcc $main_flags main.c -o ./build/main 
./build/main