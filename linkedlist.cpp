#include <string>
#include <set>
#include <stack>

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

class Solution_876 {
public:
    ListNode* middleNode(ListNode* head) {
        if (!head->next) return head;

        ListNode* fastPtr = head;
        ListNode* slowPtr = head;

        while (fastPtr && fastPtr->next) {
            fastPtr = fastPtr->next->next;
            slowPtr = slowPtr->next;
        }

        return slowPtr;
    }
};

class Solution_141 {
public:
    bool hasCycle(ListNode *head) {
        if (!head) return false;
        //create a sample node set to tell if we found a cycle
        std::set<ListNode*> nodeSet;

        //iterate through the linked list
        while (head->next) {
            //if we found that the head in the node set, that means there is a cycle in the list
            //return early
            if (nodeSet.find(head) != nodeSet.end()) return true;
           
            //otherwise, we append it to the nodeset with the node we have. the idea is that if we have
            //a cycle, it should eventually reach the head. by using a  set, we can guarentee that order
            //is preserved and we wont have to worry about indexes
            nodeSet.insert(head);
            head = head->next;
        }
        return false;
    }
};

class Solution_143 {
public:
    void reorderList(ListNode* head) {
        if (!head || !head->next) return;

        std::stack<ListNode*> nodeStack;
        ListNode* nodePtr = head;

        while(nodePtr) {
            nodeStack.push(nodePtr);
            nodePtr = nodePtr->next;            
        }

        ListNode* nextPtr = head;
        for (int i = 0; i < nodeStack.size() / 2; i++) {
            ListNode* curr = nodeStack.top();
            nodeStack.pop();
            curr->next = nextPtr->next;
            nextPtr->next = curr;
            nextPtr = nextPtr->next->next;   
        }

        nextPtr->next = nullptr;
    }
};

class Solution_92 {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (left == right) return head;
        ListNode* temp = new ListNode(0);
        ListNode* prev = temp;

        temp->next = head;
        for (int i = 0; i < left - 1; i++) {
            prev = prev->next; 
        }

        ListNode* curr = prev->next;
        for (int j = 0; j < right - left; j++) {
            ListNode* temp2 = curr->next;
            curr->next = temp2->next;
            temp2->next = prev->next;
            prev->next = temp2;
        } 

        return temp->next;
    }
};

int main(){
	//Problem 19:  Delete nth node from the end of a Linked List 
	//Problem 24:  Swap Nodes in Linked List (without modifying values)
    //Problem 876: Find the middle node of a linked list
    //Problem 141: Determine if a linked list has a cycle
    //Problem 143: Reorder a linked list by putting the last element as the second
    //Problem 92:  Reverse a linked list in order from position left <= position right
}