#include <stdio.h>
#include <iostream>
#include <vector>

struct Node
{
    int data;
    struct Node* next;
};

struct Node* first = NULL;
struct Node* last = NULL;

void create(int A[], int n)
{
    if(first)
        return;
        
    Node* t = (struct Node*)malloc(sizeof(struct Node));
    first = t;
    t->data = A[0];
    t->next = NULL;
    last = first;
    
    for(int i = 1; i < n; i++)
    {
        t = (struct Node*)malloc(sizeof(struct Node));
        t->data = A[i];
        t->next = NULL;
        last->next = t;
        last = t;
    }
}


void print()
{
    if(first == NULL)
        return;

    struct Node* p;
    p = first;
    
    while(p)
    {
        std::cout<<p->data<<" ";
        p = p->next;
    }

}


void pushLast(int value)
{
    if(last == NULL)
        return;

    Node* t = (struct Node*)malloc(sizeof(struct Node));
    t->data = value;
    t->next = NULL;
    last->next = t;
    last = t;
}

void pushFirst(int value)
{
    if(first == NULL)
        return;
    
    Node* t = (struct Node*)malloc(sizeof(struct Node));
    t->data = value;
    t->next = first;
    first = t;
}

void findPalindrome(std::vector<int> &vec)
{

    if(first == NULL)
        return;

    struct Node* p;
    p = first;
    
    int n,d,s;
    
    while(p)
    {
        n = p->data;
        d = 0;
        s = 0;
        while(n > 0)
        {
            d = n % 10;
            s = s*10 + d;
            n = n / 10;
        }
        
        if(s == p->data)
            vec.push_back(p->data);
            
        p = p->next;
    }    
}

int main(int argc, char **argv)
{

    int A[] = {11,223,323,414,52};
    int n ; // sizeof(A)/sizeof(A[0]);
    n = sizeof(A)/sizeof(A[0]);
    
    pushLast(12);
    print();
    pushFirst(12);
    print();
    
    create(A,n);

    print();
    std::cout<<std::endl;
    pushLast(34);
    print();
    std::cout<<std::endl;
    pushFirst(1881);
    print();
    std::cout<<std::endl<<"palindrome numbers ";
    std::vector<int> vec;
    findPalindrome(vec);
    for(auto s : vec)
        std::cout<<s<<" ";
    
    return 0;
}
