#include <iostream>
#include <vector>
#include <memory>

std::shared_ptr<std::vector<int>> foo()
{
    std::shared_ptr<std::vector<int>> ptrVec;
    
    ptrVec = std::make_shared<std::vector<int>>();

    for(int i = 0; i < 100; ++i)
        ptrVec->push_back(i);

    return ptrVec;
}

int main()
{
    const auto vec = *foo();
    for(const auto& x : vec) //it is okay.
        std::cout<<x<<" ";
    std::endl(std::cout);
    // in the range expression, temp objects life time can not be extended.
    for(const auto& x : *foo()) // undefined behaviour
        std::cout<<x<<" ";

    return 0;
}

/*

valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./a.out

==4767== 1 errors in context 1 of 3:
==4767== Invalid read of size 8
==4767==    at 0x10A394: __gnu_cxx::__normal_iterator<int*, std::vector<int, std::allocator<int> > >::__normal_iterator(int* const&) (in /home/jnano/files/ExampleCode/Cpp/a.out)
==4767==    by 0x109C3B: std::vector<int, std::allocator<int> >::end() (in /home/jnano/files/ExampleCode/Cpp/a.out)
==4767==    by 0x10950C: main (in /home/jnano/files/ExampleCode/Cpp/a.out)
==4767==  Address 0x4dc3928 is 24 bytes inside a block of size 40 free'd
==4767==    at 0x483CFBF: operator delete(void*) (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==4767==    by 0x10B4D7: __gnu_cxx::new_allocator<std::_Sp_counted_ptr_inplace<std::vector<int, std::allocator<int> >, std::allocator<std::vector<int, std::allocator<int> > >, (__gnu_cxx::_Lock_policy)2> >::deallocate(std::_Sp_counted_ptr_inplace<std::vector<int, std::allocator<int> >, std::allocator<std::vector<int, std::allocator<int> > >, (__gnu_cxx::_Lock_policy)2>*, unsigned long) (in /home/jnano/files/ExampleCode/Cpp/a.out)

*/