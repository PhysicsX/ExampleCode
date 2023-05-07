#include <stdio.h>
#include <stdlib.h>
#include <iostream>

typedef struct value_tag
{
    int x;
    int y;
}value;

typedef struct st1_tag
{
    unsigned int size;
    value* array;
}st1;

typedef struct st2_tag
{
    unsigned int size;
    st1* array;
}st2;

st2 foo(int size)
{
    st2 st2Struct;
    st2Struct.size = size;
    st2Struct.array = (st1*)malloc(size*sizeof(st1));

    for(int i = 0; i < size; ++i)
    {
        st1 st1Struct;
        st1Struct.size = size;
        st1Struct.array = (value*)malloc(size*sizeof(value));

        for(int j = 0; j < size; ++j)
        {
            value val;
            val.x = j;
            val.y = j+1;
            st1Struct.array[j] = val;
        }   
        st2Struct.array[i] = st1Struct;
    }

    return st2Struct;
}

int main()
{

    st2 st = foo(10);

    for(int i = 0; i < 10; ++i)
    {
        for(int j = 0; j < 10; ++j)
        {
        printf("%d ",st.array[i].array[j].x);
        }
        std::endl(std::cout);
    }

    // free the memory
    for(int i = 0; i < 10; ++i)
    {
        free(st.array[i].array);
    }
    free(st.array);
    
    return 0;
}