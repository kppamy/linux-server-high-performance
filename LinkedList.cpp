#include <vector>
#include <stdio.h>
#include <iostream>
#include <string>
#include "LinkedList.h"

using namespace std;
 

ListNode* vectorToListNode(vector<int> &list) {
    // Now convert that list into linked list
    ListNode* dummyRoot = new ListNode(0);
    ListNode* ptr = dummyRoot;
    for(int item : list) {
        ptr->next = new ListNode(item);
        ptr = ptr->next;
    }
    ptr = dummyRoot->next;
    delete dummyRoot;
    return ptr;
}

void prettyPrintLinkedList(ListNode* node) {
  while (node && node->next) {
      cout << node->val << "->";
      node = node->next;
  }

  if (node) {
    cout << node->val << endl;
  } else {
    cout << "Empty LinkedList" << endl;
  }
}

void LinkedList::deleteNode(ListNode *node){
     ListNode *nn = node->next;
     node->val = nn->val ;
     node->next = nn->next;
     delete nn;
}

 

int main() {
    vector<int> input{1, 2, 3, 4, 5,6, 7};
    ListNode* list = vectorToListNode(input);
    prettyPrintLinkedList(list); 
    LinkedList ll;
    ll.deleteNode(list->next->next);
    prettyPrintLinkedList(list); 
    return 0;
}