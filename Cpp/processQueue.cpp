#include <iostream>
#include <queue>
#include <thread>
#include <future>

// process queue example with condition variable
// check the notes for data race conditions with valgrind and clang at the end of the file

template <class T>
class queueProcess {
public:
    queueProcess():
        runFlag(false){}

    ~queueProcess() {
        {
        std::lock_guard<std::mutex> lock{mMutex};
        runFlag = true;
        mCondVar.notify_one();
        }
        if(fut.valid())
        {
            fut.wait();
        }
    }

  void addQueue(const T& process) {
    {
        std::lock_guard<std::mutex> lock{mMutex};
        mQueue.push(process);
        mCondVar.notify_one();
    }

  }

  void processQueue() {

    if(!fut.valid())
    {
    fut = std::async(std::launch::async, [&](){

      while (!runFlag) {
           std::unique_lock<std::mutex> lock{mMutex};

           mCondVar.wait(
                lock, [this]() { return !mQueue.empty() || runFlag; });

          if(runFlag)
          {
                return;
          }

           auto process = mQueue.front();
           mQueue.pop();
           lock.unlock();

           process();
      }

      });
    }

  }

  std::future<void> fut;
  std::queue<T> mQueue;
  std::mutex mMutex;
  bool runFlag;
  std::condition_variable mCondVar;
};

void dummyProcess(const std::string &msg) {
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::cout << "Finished: " << msg << "\n";
}

int main() {
    queueProcess<std::function<void()>> processor;

    processor.addQueue([]() { dummyProcess("1"); });
    processor.processQueue();
    processor.addQueue([]() { dummyProcess("2"); });
    processor.addQueue([]() { dummyProcess("3"); });
    processor.processQueue(); // no effect
    processor.addQueue([]() { dummyProcess("4"); });

    std::this_thread::sleep_for(std::chrono::seconds(5));
    processor.addQueue([]() { dummyProcess("12"); });

}


// - mCondVar.notify_one(); is moved to outside of the namespace then valgrind will give data race potential, in addQueue function,
// To see this run function should be processQueue before the adding sth to queue or middle of the queue adition.
// - processQueue function should not be assinged to fut in the constructor. If the run function is called inside the constructor,
// then valgrind will say potential data race. This is because, it is not good idea to run or call functions before object 
// creation complete. Constructor should be waited.

// g++ processQueue.cpp -lpthread -o process
// - to check the data race with valgrind
// valgrind --tool=helgrind --verbose ./process

// It is possible to check data race conditions with clang
// clang++ -fsanitize=thread -g -O1 processQueue.cpp -lpthread -o process
// ./process

// Here is the ouput of the valgrind for above code snippet

// ~$ valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./process
// ==1073== Memcheck, a memory error detector
// ==1073== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
// ==1073== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
// ==1073== Command: ./process
// ==1073== 
// Finished: 1
// Finished: 2
// Finished: 3
// Finished: 4
// ==1073== 
// ==1073== HEAP SUMMARY:
// ==1073==     in use at exit: 0 bytes in 0 blocks
// ==1073==   total heap usage: 8 allocs, 8 frees, 74,704 bytes allocated
// ==1073== 
// ==1073== All heap blocks were freed -- no leaks are possible
// ==1073== 
// ==1073== For lists of detected and suppressed errors, rerun with: -s
// ==1073== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
// (failed reverse-i-search)`helgr': valgrind --leak-c^Cck=full --show-leak-kinds=all --track-origins=yes ./process
// ~$ ^C
// (failed reverse-i-search)`val': ^Clgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./example
// ~$ ^C
// ~$ valgrind --tool=helgrind --verbose ./process 
// ==1149== Helgrind, a thread error detector
// ==1149== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
// ==1149== Using Valgrind-3.15.0-608cb11914-20190413 and LibVEX; rerun with -h for copyright info
// ==1149== Command: ./process
// ==1149== 
// --1149-- Valgrind options:
// --1149--    --tool=helgrind
// --1149--    --verbose
// --1149-- Contents of /proc/version:
// --1149--   Linux version 5.11.0-1020-gcp (buildd@lgw01-amd64-044) (gcc (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0, GNU ld (GNU Binutils for Ubuntu) 2.34) #22~20.04.1-Ubuntu SMP Tue Sep 21 10:54:26 UTC 2021
// --1149-- 
// --1149-- Arch and hwcaps: AMD64, LittleEndian, amd64-cx16-lzcnt-rdtscp-sse3-ssse3-avx-avx2-bmi-f16c-rdrand
// --1149-- Page sizes: currently 4096, max supported 4096
// --1149-- Valgrind library directory: /usr/lib/x86_64-linux-gnu/valgrind
// ==1149== helgrind --delta-stacktrace=yes only works with --vex-guest-chase-thresh=0
// ==1149== => (re-setting it to 0
// --1149-- Reading syms from /home/user/process
// --1149-- Reading syms from /lib/x86_64-linux-gnu/ld-2.31.so
// --1149--   Considering /lib/x86_64-linux-gnu/ld-2.31.so ..
// --1149--   .. CRC mismatch (computed 0306b78c wanted 8d362b37)
// --1149--   Considering /lib/x86_64-linux-gnu/ld-2.31.so ..
// --1149--   .. CRC mismatch (computed 0306b78c wanted 8d362b37)
// --1149--   Considering /usr/lib/debug/lib/x86_64-linux-gnu/ld-2.31.so ..
// --1149--   .. CRC is valid
// --1149-- Reading syms from /usr/lib/x86_64-linux-gnu/valgrind/helgrind-amd64-linux
// --1149--    object doesn't have a symbol table
// --1149--    object doesn't have a dynamic symbol table
// --1149-- Scheduler: using generic scheduler lock implementation.
// --1149-- Reading suppressions file: /usr/lib/x86_64-linux-gnu/valgrind/default.supp
// ==1149== embedded gdbserver: reading from /tmp/vgdb-pipe-from-vgdb-to-1149-by-user-on-project-0c7ed3d8-8a23-40a0-8ebc-58b9204fec36
// ==1149== embedded gdbserver: writing to   /tmp/vgdb-pipe-to-vgdb-from-1149-by-user-on-project-0c7ed3d8-8a23-40a0-8ebc-58b9204fec36
// ==1149== embedded gdbserver: shared mem   /tmp/vgdb-pipe-shared-mem-vgdb-1149-by-user-on-project-0c7ed3d8-8a23-40a0-8ebc-58b9204fec36
// ==1149== 
// ==1149== TO CONTROL THIS PROCESS USING vgdb (which you probably
// ==1149== don't want to do, unless you know exactly what you're doing,
// ==1149== or are doing some strange experiment):
// ==1149==   /usr/lib/x86_64-linux-gnu/valgrind/../../bin/vgdb --pid=1149 ...command...
// ==1149== 
// ==1149== TO DEBUG THIS PROCESS USING GDB: start GDB like this
// ==1149==   /path/to/gdb ./process
// ==1149== and then give GDB the following command
// ==1149==   target remote | /usr/lib/x86_64-linux-gnu/valgrind/../../bin/vgdb --pid=1149
// ==1149== --pid is optional if only one valgrind process is running
// ==1149== 
// --1149-- Reading syms from /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_core-amd64-linux.so
// --1149--    object doesn't have a symbol table
// --1149-- Reading syms from /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so
// --1149--    object doesn't have a symbol table
// --1149-- REDIR: 0x401f5f0 (ld-linux-x86-64.so.2:strcmp) redirected to 0x4845900 (strcmp)
// --1149-- REDIR: 0x4022e10 (ld-linux-x86-64.so.2:strlen) redirected to 0x4844d90 (strlen)
// --1149-- REDIR: 0x4023370 (ld-linux-x86-64.so.2:mempcpy) redirected to 0x4848a00 (mempcpy)
// --1149-- Reading syms from /lib/x86_64-linux-gnu/libpthread-2.31.so
// --1149--   Considering /usr/lib/debug/.build-id/f0/983025f0e0f327a6da752ff4ffa675e0be393f.debug ..
// --1149--   .. build-id is valid
// ==1149== WARNING: new redirection conflicts with existing -- ignoring it
// --1149--     old: 0x0489c8b0 (pthread_spin_init   ) W-> (0000.0) 0x04844340 pthread_spin_init
// --1149--     new: 0x0489c8b0 (pthread_spin_init   ) W-> (0000.0) 0x04844350 pthread_spin_unlock
// ==1149== WARNING: new redirection conflicts with existing -- ignoring it
// --1149--     old: 0x0489c8b0 (pthread_spin_init   ) W-> (0000.0) 0x04844340 pthread_spin_init
// --1149--     new: 0x0489c8b0 (pthread_spin_init   ) W-> (0000.0) 0x04844350 pthread_spin_unlock
// ==1149== WARNING: new redirection conflicts with existing -- ignoring it
// --1149--     old: 0x0489e530 (sem_wait@@GLIBC_2.2.) W-> (0000.0) 0x04844430 sem_wait@*
// --1149--     new: 0x0489e530 (sem_wait@@GLIBC_2.2.) W-> (0000.0) 0x04844420 sem_wait
// ==1149== WARNING: new redirection conflicts with existing -- ignoring it
// --1149--     old: 0x0489ea30 (sem_post@@GLIBC_2.2.) W-> (0000.0) 0x04844450 sem_post@*
// --1149--     new: 0x0489ea30 (sem_post@@GLIBC_2.2.) W-> (0000.0) 0x04844440 sem_post
// --1149-- Reading syms from /lib/x86_64-linux-gnu/libstdc++.so.6.0.28
// --1149--    object doesn't have a symbol table
// --1149-- Reading syms from /lib/x86_64-linux-gnu/libgcc_s.so.1
// --1149--    object doesn't have a symbol table
// --1149-- Reading syms from /lib/x86_64-linux-gnu/libc-2.31.so
// --1149--   Considering /lib/x86_64-linux-gnu/libc-2.31.so ..
// --1149--   .. CRC mismatch (computed ef41b1a0 wanted f854b801)
// --1149--   Considering /lib/x86_64-linux-gnu/libc-2.31.so ..
// --1149--   .. CRC mismatch (computed ef41b1a0 wanted f854b801)
// --1149--   Considering /usr/lib/debug/lib/x86_64-linux-gnu/libc-2.31.so ..
// --1149--   .. CRC is valid
// --1149-- Reading syms from /lib/x86_64-linux-gnu/libm-2.31.so
// --1149--   Considering /lib/x86_64-linux-gnu/libm-2.31.so ..
// --1149--   .. CRC mismatch (computed 3cfca93f wanted 658b15c9)
// --1149--   Considering /lib/x86_64-linux-gnu/libm-2.31.so ..
// --1149--   .. CRC mismatch (computed 3cfca93f wanted 658b15c9)
// --1149--   Considering /usr/lib/debug/lib/x86_64-linux-gnu/libm-2.31.so ..
// --1149--   .. CRC is valid
// --1149-- REDIR: 0x4b4c4b0 (libc.so.6:memmove) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
// --1149-- REDIR: 0x4b4b7b0 (libc.so.6:strncpy) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
// --1149-- REDIR: 0x4b4c7e0 (libc.so.6:strcasecmp) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
// --1149-- REDIR: 0x4b4b0d0 (libc.so.6:strcat) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
// --1149-- REDIR: 0x4b4b810 (libc.so.6:rindex) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
// --1149-- REDIR: 0x4b4dc80 (libc.so.6:rawmemchr) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
// --1149-- REDIR: 0x4b68d10 (libc.so.6:wmemchr) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
// --1149-- REDIR: 0x4b68850 (libc.so.6:wcscmp) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
// --1149-- REDIR: 0x4b4c610 (libc.so.6:mempcpy) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
// --1149-- REDIR: 0x4b4c440 (libc.so.6:bcmp) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
// --1149-- REDIR: 0x4b4b740 (libc.so.6:strncmp) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
// --1149-- REDIR: 0x4b4b180 (libc.so.6:strcmp) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
// --1149-- REDIR: 0x4b4c570 (libc.so.6:memset) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
// --1149-- REDIR: 0x4b68810 (libc.so.6:wcschr) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
// --1149-- REDIR: 0x4b4b6a0 (libc.so.6:strnlen) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
// --1149-- REDIR: 0x4b4b260 (libc.so.6:strcspn) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
// --1149-- REDIR: 0x4b4c830 (libc.so.6:strncasecmp) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
// --1149-- REDIR: 0x4b4b200 (libc.so.6:strcpy) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
// --1149-- REDIR: 0x4b4c980 (libc.so.6:memcpy@@GLIBC_2.14) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
// --1149-- REDIR: 0x4b69f80 (libc.so.6:wcsnlen) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
// --1149-- REDIR: 0x4b68890 (libc.so.6:wcscpy) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
// --1149-- REDIR: 0x4b4b850 (libc.so.6:strpbrk) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
// --1149-- REDIR: 0x4b4b130 (libc.so.6:index) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
// --1149-- REDIR: 0x4b4b660 (libc.so.6:strlen) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
// --1149-- REDIR: 0x4b54bd0 (libc.so.6:memrchr) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
// --1149-- REDIR: 0x4b4c880 (libc.so.6:strcasecmp_l) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
// --1149-- REDIR: 0x4b4c400 (libc.so.6:memchr) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
// --1149-- REDIR: 0x4b68960 (libc.so.6:wcslen) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
// --1149-- REDIR: 0x4b4bb10 (libc.so.6:strspn) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
// --1149-- REDIR: 0x4b4c780 (libc.so.6:stpncpy) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
// --1149-- REDIR: 0x4b4c720 (libc.so.6:stpcpy) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
// --1149-- REDIR: 0x4b4dcc0 (libc.so.6:strchrnul) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
// --1149-- REDIR: 0x4b4c8d0 (libc.so.6:strncasecmp_l) redirected to 0x48311d0 (_vgnU_ifunc_wrapper)
// --1149-- REDIR: 0x4c34410 (libc.so.6:__strrchr_avx2) redirected to 0x4844930 (rindex)
// --1149-- REDIR: 0x4b46110 (libc.so.6:malloc) redirected to 0x483c820 (malloc)
// --1149-- REDIR: 0x4c345e0 (libc.so.6:__strlen_avx2) redirected to 0x4844c70 (strlen)
// --1149-- REDIR: 0x4c30bd0 (libc.so.6:__memcmp_avx2_movbe) redirected to 0x4847870 (bcmp)
// --1149-- REDIR: 0x4c2fae0 (libc.so.6:__strcmp_avx2) redirected to 0x4845800 (strcmp)
// --1149-- REDIR: 0x4959b20 (libstdc++.so.6:operator new(unsigned long)) redirected to 0x483ce90 (operator new(unsigned long))
// --1149-- REDIR: 0x4896fc0 (libpthread.so.0:pthread_mutex_lock) redirected to 0x4843e40 (pthread_mutex_lock)
// --1149-- REDIR: 0x489bee0 (libpthread.so.0:pthread_cond_signal@@GLIBC_2.3.2) redirected to 0x4843ea0 (pthread_cond_signal@*)
// --1149-- REDIR: 0x48987b0 (libpthread.so.0:pthread_mutex_unlock) redirected to 0x4843e70 (pthread_mutex_unlock)
// --1149-- REDIR: 0x48948d0 (libpthread.so.0:pthread_create@@GLIBC_2.2.5) redirected to 0x4843a30 (pthread_create@*)
// --1149-- REDIR: 0x4b47b40 (libc.so.6:calloc) redirected to 0x483ed80 (calloc)
// --1149-- REDIR: 0x4c375d0 (libc.so.6:__mempcpy_avx_unaligned_erms) redirected to 0x4848880 (mempcpy)
// Finished: 1
// Finished: 2
// Finished: 3
// Finished: 4
// --1149-- REDIR: 0x489b160 (libpthread.so.0:pthread_cond_wait@@GLIBC_2.3.2) redirected to 0x4843e80 (pthread_cond_wait@*)
// --1149-- REDIR: 0x48959e0 (libpthread.so.0:pthread_join) redirected to 0x4843a40 (pthread_join)
// --1149-- REDIR: 0x4957d80 (libstdc++.so.6:operator delete(void*, unsigned long)) redirected to 0x483e200 (operator delete(void*, unsigned long))
// --1149-- REDIR: 0x4b46700 (libc.so.6:free) redirected to 0x483da70 (free)
// --1149-- REDIR: 0x489add0 (libpthread.so.0:pthread_cond_destroy@@GLIBC_2.3.2) redirected to 0x4843ed0 (pthread_cond_destroy@*)
// --1149-- REDIR: 0x4957d70 (libstdc++.so.6:operator delete(void*)) redirected to 0x483dff0 (operator delete(void*))
// ==1149== 
// ==1149== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 40 from 12)
// --1149-- 
// --1149-- used_suppression:     40 helgrind-glibc2X-005 /usr/lib/x86_64-linux-gnu/valgrind/default.supp:963
// ==1149== 
// ==1149== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 40 from 12)

// -------------------------------------------------------------------
// From this code if couts are not deleted valgrind give data race potential issue

// #include <queue>
// #include <mutex>
// #include <condition_variable>
// #include <iostream>
// #include <future>
// #include <string>

// using namespace std;

// template <class T>
// class concurrent_queue_cv {
//         std::mutex m;
//         std::queue<T> q;
//         std::condition_variable cv;
// public:
//         concurrent_queue_cv() = default;
//         void push(T value) {
//                 std::lock_guard<std::mutex> lg(m);
//                 q.push(value);
//                 cv.notify_one();
//         }

//         void pop(T& value) {
//                 std::unique_lock<std::mutex> lg(m);
//                 cv.wait(lg, [this] {return !q.empty();});
//                 value = q.front();
//                 q.pop();
//         }
// };

// concurrent_queue_cv<string> cq;

// // Waiting thread
// void reader() {
//         string sdata;
// //      cout << "Reader calling pop..." << endl;
//         cq.pop(sdata);                                       // Pop the data off the queue
// //      cout << "Reader received data: " << sdata << endl;
// }

// // Modyifing thread
// void writer() {
//         std::this_thread::sleep_for(2s);                     // Pretend to be busy...
// //      cout << "Writer calling push..." << endl;
//         cq.push("Populated");                                // Push the data onto the queue
// //      cout << "Writer returned from push..." << endl;
// }

// int main() {
// //      cout << "Starting reader" << endl;
//         auto r = async(std::launch::async, reader);
// //      cout << "Starting writer" << endl;
//         auto w = async(std::launch::async, writer);
//         r.wait();
//         w.wait();
// }

