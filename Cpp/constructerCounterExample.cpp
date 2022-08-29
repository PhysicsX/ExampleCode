#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

template <typename T>
struct instance_counter {

    instance_counter() noexcept { ++icounter.num_construct; }
    instance_counter(const instance_counter&) noexcept { ++icounter.num_copy; }
    instance_counter(instance_counter&&) noexcept { ++icounter.num_move; }
    // Simulate both copy-assign and move-assign
    instance_counter& operator=(instance_counter) noexcept
    {
        return *this;
    }
    ~instance_counter() { ++icounter.num_destruct; }

private:
    static struct counter {
        int num_construct = 0;
        int num_copy = 0;
        int num_move = 0;
        int num_destruct = 0;

        ~counter()
        {
            std::cout<<"number of constructions " <<num_construct<<std::endl;
            std::cout<<"number of copies "<< num_copy<<std::endl;
            std::cout<<"number of moves "<< num_move<<std::endl;
            const int total_construct = num_construct + num_copy + num_move;
            std::cout<<"total constructions "<< total_construct<<std::endl;
            std::cout<<"destructions "<<num_destruct<<std::endl;
            if (total_construct == num_destruct) {
                std::cout<<"no leaks"<<std::endl;
            } else {
                std::cout<<"WARNING: potential leak"<<std::endl;
            }
        }
    } icounter;
};

template <typename T>
typename instance_counter<T>::counter instance_counter<T>::icounter{};

template <typename T>
struct counted : T, private instance_counter<T>
{
    using T::T;
};

counted<std::vector<int>> foo()
{
    counted<std::vector<int>> vecLocal;

    return vecLocal;
}

const counted<std::vector<int>>& foo2(const counted<std::vector<int>>& vec)
{
    return vec;
}

class example
{
    public:

    // if foo3 return locall variable then there will be no copy
    // or foo3 should return const reference if vecLocal is needed
    // to be returned
    counted<std::vector<int>> vecLocal;

    counted<std::vector<int>> foo3()
    {
        return vecLocal;
    }
};

int main()
{
    // this will copy the vector. Should be moved = std::move(vec);
    // counted<std::vector<int>> vec;
    // counted<std::vector<int>> vec2 = vec;

    // this will not copy either - copy ellision - rvo
    //counted<std::vector<int>> vec2 = foo();

    // this will not copy either as long as const-reference is used
    // without reference it will create the copy again
    //counted<std::vector<int>> vec;
    //const counted<std::vector<int>>& vec2 = foo2(vec);

    // this will copy const reference should be used for the foo3
    counted<std::vector<int>> vec4 = example{}.foo3();
}

/*
    number of constructions 1
    number of copies 1
    number of moves 0
    total constructions 2
    destructions 2
    no leaks
/*