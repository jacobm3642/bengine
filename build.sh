wd=$(pwd)

export LD_LIBRARY_PATH=$wd/renderer:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$wd/datastructs:$LD_LIBRARY_PATH

main_flags=" -Wall -Werror -lX11 -lGL -lGLU -lGLEW -L./renderer -lobjects -L./datastructs -lheap"
shared_flags="-shared"

gcc $shared_flags ./datastructs/heap.c -o ./datastructs/libheap.so
gcc $shared_flags ./renderer/objects.c -o ./renderer/libobjects.so
gcc $main_flags main.c -o ./build/main 
./build/main