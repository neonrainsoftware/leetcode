#include <string>

struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution_24 {
	public:
	
    ListNode* swapPairs(ListNode* head) {
		//first check if head doesn't exist or if the next node is empty
        if (head == nullptr || head->next == nullptr) return head;
		//then create two nodes, one that has the current head
		//the next has the next node
		//this is not ideal memory wise, but is best for ease of access
		//since the head of the list will never change, we only technically 
		//need to return the new head after the first swap, but writing this out for completeness
        ListNode* temp = head;
        ListNode* newHead = head->next;

		//check if we're at the end or nearing it
        while(temp != nullptr && temp->next !=nullptr) {
            //swapping logic
			//create new node where we are, set the head to the next node
			//then set the node after the new head to the node we just created
			ListNode* curr = temp;
            temp = temp->next;
            curr->next = temp->next;
            temp->next = curr;
            temp = curr->next;

			//have we reached the end or nearing it? if not, we go to the third node
            if (temp != nullptr && temp->next != nullptr)
                curr->next = temp->next;
        }
        return newHead;
    }
};

class Solution_19 {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (head == nullptr) return head;
		//create two pointers, one at the head, the other pointing to the first pointer
        ListNode* result = new ListNode(0, head);
        ListNode* ptrOne = result;

		//navigate the head n times through the linked list
        for (int i = 0; i < n; i++) {
            head = head->next;
        }

		//the idea is that if we move the head n times, then all we have to do is
		//have the head continue to the end of the list, moving both pointers at the same time
		//if we reach the end, then the second pointer will be n times from the end of the list
        while(head != nullptr) {
            head = head->next;
            ptrOne = ptrOne->next;
        }

		//set the next node equal to the next one after that to avoid memory issues
        ptrOne->next = ptrOne->next->next;

		//simple deletion of a node where we know where it is
        ListNode* temp = result->next;
        delete result;
        return temp;
    }
};


int main(){
	//Problem 19: Delete nth node from the end of a Linked List 
	//Problem 24: Swap Nodes in Linked List (without modifying values)
}