#include <iostream>

// merge sorted linked-list example
// recursive approach

struct ListNode{
    int val;
    ListNode* next;
    ListNode():val(0),next(nullptr){}
    ListNode(int x):val(x), next(nullptr){}
    ListNode(int x, ListNode* next):val(x),next(next){}
};


class Solution
{
    public:
        ListNode* mergeTwoList(ListNode* list1, ListNode* list2)
        {

            if(list1 == nullptr) return list2;
            if(list2 == nullptr) return list1;

            if(list1->val < list2->val)
            {
                list1->next = mergeTwoList(list1->next, list2);
                return list1;
            }
            else
            {
                list2->next = mergeTwoList(list1, list2->next);
                return list2;
            }
        }
};

int main()
{
    ListNode* lastNode = new ListNode(22);
    ListNode* secondNode = new ListNode(12, lastNode);
    ListNode* firstNode = new ListNode(3, secondNode);

    ListNode* list1 = firstNode;

    ListNode* list2LastNode = new ListNode(16);
    ListNode* list2secondNode = new ListNode(6, list2LastNode);
    ListNode* list2firstNode = new ListNode(1, list2secondNode);
    
    ListNode* list2 = list2firstNode;

    ListNode* resultList = Solution().mergeTwoList(list1, list2);
    
    ListNode* node;
    node = resultList;
    for(int i{0}; i<6; i++)
    {    
        std::cout<<node->val<<" ";
        node = node->next;
    }

}

