// #include "my_math.h"
#include <iostream>

extern double reciprocal(double d);

int main(){
    std::cout << reciprocal(2.0) << std::endl;
    return 0;
}

/*

g++ -c main.cpp -o main.o

ulas@ulas:~/staticTest$ cat my_math.cpp
#include "my_math.h"

double reciprocal(double d) {
    return 1.0 / d;
}

g++ -c my_math.cpp -o my_math.o
g++ main.o my_math.o -o a.out

ar cr libmy_math.a my_math.o
g++ -static -static-libgcc -static-libstdc++ main.o libmy_math.a -o a.out

ulas@ulas:~/staticTest$ ldd staticTest
    linux-vdso.so.1 (0x00007ffc4c5d0000)
    libstdc++.so.6 => /lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007fac8f1af000)
    libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007fac8ef87000)
    libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007fac8eea0000)
    /lib64/ld-linux-x86-64.so.2 (0x00007fac8f3fd000)
    libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007fac8ee80000)


g++ -shared -o libmy_math.so my_math.o
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/ulas/staticTest/
ulas@ulas:~/staticTest$ ldd staticTest
    linux-vdso.so.1 (0x00007ffd5ece8000)
    libmy_math.so => not found
    libstdc++.so.6 => /lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007f3f17796000)
    libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f3f1756e000)
    libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007f3f17487000)
    /lib64/ld-linux-x86-64.so.2 (0x00007f3f179e4000)
    libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007f3f17467000)

*/
