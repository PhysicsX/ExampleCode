#include <iostream>

// leetcode 24. Swap Nodes in Pairs

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
ListNode* swapPairs(ListNode* head) {

        if(head==NULL)
            return head;

        ListNode* dummy = new ListNode(-1);
        dummy->next = head;
        ListNode* prev = dummy;

        while(head != NULL && head->next!=NULL)
        { 
            ListNode *firstNode = head;
            ListNode *secondNode = head->next;

            prev->next = secondNode;
            firstNode->next = secondNode->next;
            secondNode->next = firstNode;

            prev = firstNode;
            head = firstNode->next;
        }
        
        return dummy->next;
    }
};

int main()
{
    ListNode* tmp;
    ListNode* list = new ListNode(0);
    tmp = list;

    for(int i = 1; i<6; i++)
    {
        tmp->next = new ListNode(i);
        tmp = tmp->next;
    }

    ListNode* res = Solution{}.swapPairs(list);

    tmp = res;

    while(tmp != NULL)
    {
        std::cout<<tmp->val;
        tmp = tmp->next;
    }

    return 0;
}