#include "sll.h"
#include<iostream>

using namespace std;

void print_ll(ListNode* node) {
	while (node != nullptr) {
		cout << node->val << " ";
		node = node->next;
	}
	cout << endl;
}


class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        
        ListNode* last = nullptr; 
    	ListNode* out = head;
    	ListNode* node = head;

    	if ( head == nullptr ) 
    		return out;

    	while (node != nullptr) {
    		if ( node->val == val ) {
    			if ( node == out ) 
    				out = node->next;
    			if ( last != nullptr ) 
    				last->next = node->next;
    		} else {
    			last = node;
    		}
    		node = node->next;
    	}

    	return out;
    }
};


int main() {
	Solution s = Solution();
	ListNode* out;

	ListNode six   = ListNode(6);
	ListNode five  = ListNode(5, &six);
	ListNode four  = ListNode(4, &five);
	ListNode three = ListNode(3, &four);
	ListNode six_2 = ListNode(6, &three);
	ListNode two   = ListNode(2, &six_2);
	ListNode head  = ListNode(1, &two);

	print_ll(&head);
	out = s.removeElements(&head, 6);
	print_ll(out);

	out = s.removeElements(&head, 1);
	print_ll(out);
	return 0;

}