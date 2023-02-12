#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
// 142. Linked List Cycle ||
// return start point of the cycle in linked list
// Floyd`s algorithm is used
// there are two pointer slow and fast. Fast is 2x faster than slow.
// Meeting point in the circle(if it is exist) for fast a+b+c+b and for slow
// a+b, 2*d = (a+b+c+b), d = (a+b)
// 2a+2b = a+b+c+b
// a=c that means distance from beginning to start point is same with where
// slow and fast pointer is met to start point.
//

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        
        ListNode* slow = head;
        ListNode* fast = head;

        if(head == NULL || head->next == NULL)
            return NULL;

        slow = slow->next;
        fast = fast->next->next;

        while(fast && fast->next)
        {
            if(fast == slow)
                break;

            slow = slow->next;
            fast = fast->next->next;
        }
        
        if (slow != fast)
            return NULL;
        
        slow = head;

        while(fast != slow)
        {
            slow = slow->next;
            fast = fast->next;
        }

        return slow;
    }
};

int main()
{
	ListNode* node = new ListNode(0);
	
	ListNode* tmp;
	tmp = node;

	for(int i = 1; i < 10; i++)
	{
		tmp->next = new ListNode(i);
		tmp = tmp->next;	
	}
	// create a cycle from 3 as a start point
	tmp->next = node->next->next->next;

	ListNode* res = Solution{}.detectCycle(node);
	std::cout<<res->val<<std::endl;

	return 0;
}
