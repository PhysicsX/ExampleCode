#include <iostream>
#include <string>
// Conditional move jump example with std::move
class Example
{
    public:
    int a;
        Example():a(20){std::cout<<"def const"<<std::endl;}
        Example(const Example& ex){std::cout<<"copy const"<<std::endl;}
        //Example(const Example&& ex):a(std::move(ex.a)){std::cout<<"move const"<<std::endl;}
        Example(const Example&& ex){std::cout<<"move const"<<std::endl;}

};

class Example2 : public Example
{
    public:
    //using Example::Example;
    int a2;
    Example2():a2(2){std::cout<<"def2 const"<<std::endl;}
    Example2(const Example2& ex):Example(ex) {std::cout<<"copy2 const"<<std::endl;}
    Example2(const Example2&& ex):Example(std::move(ex)){std::cout<<"move2 const"<<std::endl;}

};

int main()
{
    Example2 ex2;
    Example2 ex3 = std::move(ex2);
    ex3.a2 = 1;
    std::cout<<ex3.a2<<" "<<ex3.a<<std::endl;
    std::cout<<ex2.a2<<" "<<ex2.a<<std::endl;
    ex2.a = 3;
    std::cout<<ex2.a2<<" "<<ex2.a<<std::endl;
}


/*
user@project-129c1875-28de-4040-8e7d-469eee5a205b:~$ g++ example.cpp -o example && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./example
==603== Memcheck, a memory error detector
==603== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==603== Using Valgrind-3.15.0-608cb11914-20190413 and LibVEX; rerun with -h for copyright info
==603== Command: ./example
==603==
--603-- Valgrind options:
--603--    --leak-check=full
--603--    --show-leak-kinds=all
--603--    --track-origins=yes
--603--    --verbose
--603-- Contents of /proc/version:
--603--   Linux version 5.11.0-1020-gcp (buildd@lgw01-amd64-044) (gcc (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0, GNU ld (GNU Binutils for Ubuntu) 2.34) #22~20.04.1-Ubuntu SMP Tue Sep 21 10:54:26 UTC 2021
--603--
--603-- Arch and hwcaps: AMD64, LittleEndian, amd64-cx16-lzcnt-rdtscp-sse3-ssse3-avx-avx2-bmi-f16c-rdrand
--603-- Page sizes: currently 4096, max supported 4096
--603-- Valgrind library directory: /usr/lib/x86_64-linux-gnu/valgrind
--603-- Reading syms from /home/user/example
--603-- Reading syms from /lib/x86_64-linux-gnu/ld-2.31.so
--603--   Considering /lib/x86_64-linux-gnu/ld-2.31.so ..
--603--   .. CRC mismatch (computed b1e31cec wanted 7bd1f8ba)
--603--   Considering /lib/x86_64-linux-gnu/ld-2.31.so ..
--603--   .. CRC mismatch (computed b1e31cec wanted 7bd1f8ba)
--603--   Considering /usr/lib/debug/lib/x86_64-linux-gnu/ld-2.31.so ..
--603--   .. CRC is valid
--603-- Reading syms from /usr/lib/x86_64-linux-gnu/valgrind/memcheck-amd64-linux
--603--    object doesn't have a symbol table
--603--    object doesn't have a dynamic symbol table
--603-- Scheduler: using generic scheduler lock implementation.
--603-- Reading suppressions file: /usr/lib/x86_64-linux-gnu/valgrind/default.supp
==603== embedded gdbserver: reading from /tmp/vgdb-pipe-from-vgdb-to-603-by-user-on-project-129c1875-28de-4040-8e7d-469eee5a205b
==603== embedded gdbserver: writing to   /tmp/vgdb-pipe-to-vgdb-from-603-by-user-on-project-129c1875-28de-4040-8e7d-469eee5a205b
==603== embedded gdbserver: shared mem   /tmp/vgdb-pipe-shared-mem-vgdb-603-by-user-on-project-129c1875-28de-4040-8e7d-469eee5a205b
==603==
==603== TO CONTROL THIS PROCESS USING vgdb (which you probably
==603== don't want to do, unless you know exactly what you're doing,
==603== or are doing some strange experiment):
==603==   /usr/lib/x86_64-linux-gnu/valgrind/../../bin/vgdb --pid=603 ...command...
==603==
==603== TO DEBUG THIS PROCESS USING GDB: start GDB like this
==603==   /path/to/gdb ./example
==603== and then give GDB the following command
==603==   target remote | /usr/lib/x86_64-linux-gnu/valgrind/../../bin/vgdb --pid=603
==603== --pid is optional if only one valgrind process is running
==603==
--603-- REDIR: 0x4022f60 (ld-linux-x86-64.so.2:strlen) redirected to 0x580c9ce2 (???)
--603-- REDIR: 0x4022d30 (ld-linux-x86-64.so.2:index) redirected to 0x580c9cfc (???)
--603-- Reading syms from /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_core-amd64-linux.so
--603--    object doesn't have a symbol table
--603-- Reading syms from /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so
--603--    object doesn't have a symbol table
==603== WARNING: new redirection conflicts with existing -- ignoring it
--603--     old: 0x04022f60 (strlen              ) R-> (0000.0) 0x580c9ce2 ???
--603--     new: 0x04022f60 (strlen              ) R-> (2007.0) 0x0483f060 strlen
--603-- REDIR: 0x401f740 (ld-linux-x86-64.so.2:strcmp) redirected to 0x483ffd0 (strcmp)
--603-- REDIR: 0x40234c0 (ld-linux-x86-64.so.2:mempcpy) redirected to 0x4843a20 (mempcpy)
--603-- Reading syms from /lib/x86_64-linux-gnu/libstdc++.so.6.0.28
--603--    object doesn't have a symbol table
--603-- Reading syms from /lib/x86_64-linux-gnu/libc-2.31.so
--603--   Considering /lib/x86_64-linux-gnu/libc-2.31.so ..
--603--   .. CRC mismatch (computed 11759501 wanted 88150686)
--603--   Considering /lib/x86_64-linux-gnu/libc-2.31.so ..
--603--   .. CRC mismatch (computed 11759501 wanted 88150686)
--603--   Considering /usr/lib/debug/lib/x86_64-linux-gnu/libc-2.31.so ..
--603--   .. CRC is valid
--603-- Reading syms from /lib/x86_64-linux-gnu/libm-2.31.so
--603--   Considering /lib/x86_64-linux-gnu/libm-2.31.so ..
--603--   .. CRC mismatch (computed 5f7b2a42 wanted ffb185de)
--603--   Considering /lib/x86_64-linux-gnu/libm-2.31.so ..
--603--   .. CRC mismatch (computed 5f7b2a42 wanted ffb185de)
--603--   Considering /usr/lib/debug/lib/x86_64-linux-gnu/libm-2.31.so ..
--603--   .. CRC is valid
--603-- Reading syms from /lib/x86_64-linux-gnu/libgcc_s.so.1
--603--    object doesn't have a symbol table
--603-- REDIR: 0x4b0b600 (libc.so.6:memmove) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
--603-- REDIR: 0x4b0a900 (libc.so.6:strncpy) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
--603-- REDIR: 0x4b0b930 (libc.so.6:strcasecmp) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
--603-- REDIR: 0x4b0a220 (libc.so.6:strcat) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
--603-- REDIR: 0x4b0a960 (libc.so.6:rindex) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
--603-- REDIR: 0x4b0cdd0 (libc.so.6:rawmemchr) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
--603-- REDIR: 0x4b27e60 (libc.so.6:wmemchr) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
--603-- REDIR: 0x4b279a0 (libc.so.6:wcscmp) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
--603-- REDIR: 0x4b0b760 (libc.so.6:mempcpy) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
--603-- REDIR: 0x4b0b590 (libc.so.6:bcmp) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
--603-- REDIR: 0x4b0a890 (libc.so.6:strncmp) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
--603-- REDIR: 0x4b0a2d0 (libc.so.6:strcmp) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
--603-- REDIR: 0x4b0b6c0 (libc.so.6:memset) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
--603-- REDIR: 0x4b27960 (libc.so.6:wcschr) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
--603-- REDIR: 0x4b0a7f0 (libc.so.6:strnlen) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
--603-- REDIR: 0x4b0a3b0 (libc.so.6:strcspn) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
--603-- REDIR: 0x4b0b980 (libc.so.6:strncasecmp) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
--603-- REDIR: 0x4b0a350 (libc.so.6:strcpy) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
--603-- REDIR: 0x4b0bad0 (libc.so.6:memcpy@@GLIBC_2.14) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
--603-- REDIR: 0x4b290d0 (libc.so.6:wcsnlen) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
--603-- REDIR: 0x4b279e0 (libc.so.6:wcscpy) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
--603-- REDIR: 0x4b0a9a0 (libc.so.6:strpbrk) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
--603-- REDIR: 0x4b0a280 (libc.so.6:index) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
--603-- REDIR: 0x4b0a7b0 (libc.so.6:strlen) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
--603-- REDIR: 0x4b13d20 (libc.so.6:memrchr) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
--603-- REDIR: 0x4b0b9d0 (libc.so.6:strcasecmp_l) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
--603-- REDIR: 0x4b0b550 (libc.so.6:memchr) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
--603-- REDIR: 0x4b27ab0 (libc.so.6:wcslen) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
--603-- REDIR: 0x4b0ac60 (libc.so.6:strspn) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
--603-- REDIR: 0x4b0b8d0 (libc.so.6:stpncpy) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
--603-- REDIR: 0x4b0b870 (libc.so.6:stpcpy) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
--603-- REDIR: 0x4b0ce10 (libc.so.6:strchrnul) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
--603-- REDIR: 0x4b0ba20 (libc.so.6:strncasecmp_l) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
--603-- REDIR: 0x4bf3490 (libc.so.6:__strrchr_avx2) redirected to 0x483ea10 (rindex)
--603-- REDIR: 0x4b05260 (libc.so.6:malloc) redirected to 0x483b780 (malloc)
--603-- REDIR: 0x4bf3660 (libc.so.6:__strlen_avx2) redirected to 0x483ef40 (strlen)
--603-- REDIR: 0x4befc50 (libc.so.6:__memcmp_avx2_movbe) redirected to 0x48421e0 (bcmp)
--603-- REDIR: 0x4beeb60 (libc.so.6:__strcmp_avx2) redirected to 0x483fed0 (strcmp)
def const
--603-- REDIR: 0x4bf6650 (libc.so.6:__mempcpy_avx_unaligned_erms) redirected to 0x4843660 (mempcpy)
def2 const
move const
move2 const
==603== Conditional jump or move depends on uninitialised value(s)
==603==    at 0x49AB402: std::ostreambuf_iterator<char, std::char_traits<char> > std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long>(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /lib/x86_64-linux-gnu/libstdc++.so.6.0.28)
==603==    by 0x49B9D5E: std::ostream& std::ostream::_M_insert<long>(long) (in /lib/x86_64-linux-gnu/libstdc++.so.6.0.28)
==603==    by 0x109264: main (in /home/user/example)
==603==  Uninitialised value was created by a stack allocation
==603==    at 0x1091E9: main (in /home/user/example)
==603==
==603== Use of uninitialised value of size 8
==603==    at 0x49AB10B: ??? (in /lib/x86_64-linux-gnu/libstdc++.so.6.0.28)
==603==    by 0x49AB42C: std::ostreambuf_iterator<char, std::char_traits<char> > std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long>(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /lib/x86_64-linux-gnu/libstdc++.so.6.0.28)
==603==    by 0x49B9D5E: std::ostream& std::ostream::_M_insert<long>(long) (in /lib/x86_64-linux-gnu/libstdc++.so.6.0.28)
==603==    by 0x109264: main (in /home/user/example)
==603==  Uninitialised value was created by a stack allocation
==603==    at 0x1091E9: main (in /home/user/example)
==603==
==603== Conditional jump or move depends on uninitialised value(s)
==603==    at 0x49AB11D: ??? (in /lib/x86_64-linux-gnu/libstdc++.so.6.0.28)
==603==    by 0x49AB42C: std::ostreambuf_iterator<char, std::char_traits<char> > std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long>(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /lib/x86_64-linux-gnu/libstdc++.so.6.0.28)
==603==    by 0x49B9D5E: std::ostream& std::ostream::_M_insert<long>(long) (in /lib/x86_64-linux-gnu/libstdc++.so.6.0.28)
==603==    by 0x109264: main (in /home/user/example)
==603==  Uninitialised value was created by a stack allocation
==603==    at 0x1091E9: main (in /home/user/example)
==603==
==603== Conditional jump or move depends on uninitialised value(s)
==603==    at 0x49AB462: std::ostreambuf_iterator<char, std::char_traits<char> > std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long>(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /lib/x86_64-linux-gnu/libstdc++.so.6.0.28)
==603==    by 0x49B9D5E: std::ostream& std::ostream::_M_insert<long>(long) (in /lib/x86_64-linux-gnu/libstdc++.so.6.0.28)
==603==    by 0x109264: main (in /home/user/example)
==603==  Uninitialised value was created by a stack allocation
==603==    at 0x1091E9: main (in /home/user/example)
==603==
1 -16776032
2 20
2 3
--603-- REDIR: 0x4b05850 (libc.so.6:free) redirected to 0x483c9d0 (free)
==603==
==603== HEAP SUMMARY:
==603==     in use at exit: 0 bytes in 0 blocks
==603==   total heap usage: 2 allocs, 2 frees, 73,728 bytes allocated
==603==
==603== All heap blocks were freed -- no leaks are possible
==603==
==603== ERROR SUMMARY: 18 errors from 4 contexts (suppressed: 0 from 0)
==603==
==603== 1 errors in context 1 of 4:
==603== Conditional jump or move depends on uninitialised value(s)
==603==    at 0x49AB462: std::ostreambuf_iterator<char, std::char_traits<char> > std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long>(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /lib/x86_64-linux-gnu/libstdc++.so.6.0.28)
==603==    by 0x49B9D5E: std::ostream& std::ostream::_M_insert<long>(long) (in /lib/x86_64-linux-gnu/libstdc++.so.6.0.28)
==603==    by 0x109264: main (in /home/user/example)
==603==  Uninitialised value was created by a stack allocation
==603==    at 0x1091E9: main (in /home/user/example)
==603==
==603==
==603== 1 errors in context 2 of 4:
==603== Conditional jump or move depends on uninitialised value(s)
==603==    at 0x49AB402: std::ostreambuf_iterator<char, std::char_traits<char> > std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long>(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /lib/x86_64-linux-gnu/libstdc++.so.6.0.28)
==603==    by 0x49B9D5E: std::ostream& std::ostream::_M_insert<long>(long) (in /lib/x86_64-linux-gnu/libstdc++.so.6.0.28)
==603==    by 0x109264: main (in /home/user/example)
==603==  Uninitialised value was created by a stack allocation
==603==    at 0x1091E9: main (in /home/user/example)
==603==
==603==
==603== 8 errors in context 3 of 4:
==603== Conditional jump or move depends on uninitialised value(s)
==603==    at 0x49AB11D: ??? (in /lib/x86_64-linux-gnu/libstdc++.so.6.0.28)
==603==    by 0x49AB42C: std::ostreambuf_iterator<char, std::char_traits<char> > std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long>(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /lib/x86_64-linux-gnu/libstdc++.so.6.0.28)
==603==    by 0x49B9D5E: std::ostream& std::ostream::_M_insert<long>(long) (in /lib/x86_64-linux-gnu/libstdc++.so.6.0.28)
==603==    by 0x109264: main (in /home/user/example)
==603==  Uninitialised value was created by a stack allocation
==603==    at 0x1091E9: main (in /home/user/example)
==603==
==603==
==603== 8 errors in context 4 of 4:
==603== Use of uninitialised value of size 8
==603==    at 0x49AB10B: ??? (in /lib/x86_64-linux-gnu/libstdc++.so.6.0.28)
==603==    by 0x49AB42C: std::ostreambuf_iterator<char, std::char_traits<char> > std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long>(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /lib/x86_64-linux-gnu/libstdc++.so.6.0.28)
==603==    by 0x49B9D5E: std::ostream& std::ostream::_M_insert<long>(long) (in /lib/x86_64-linux-gnu/libstdc++.so.6.0.28)
==603==    by 0x109264: main (in /home/user/example)
==603==  Uninitialised value was created by a stack allocation
==603==    at 0x1091E9: main (in /home/user/example)
==603==
==603== ERROR SUMMARY: 18 errors from 4 contexts (suppressed: 0 from 0)
*/