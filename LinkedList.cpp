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

ListNode *LinkedList::removeEndNthNode(ListNode *head, int n)
{
    ListNode *sp = head;
    for (int i = 0; i < n; i++)
    {
      sp = sp->next;
    }
    if (sp == NULL)
      return head->next;
    ListNode *ep = sp;
    sp = head;
    while (ep != NULL && ep->next != NULL)
    {
      ep = ep->next;
      sp = sp->next;
    }
    sp->next = sp->next->next;
    return sp;
}

int main() {
    vector<int> input{1, 2, 3, 4, 5,6, 7};
    ListNode* list = vectorToListNode(input);
    prettyPrintLinkedList(list); 
    LinkedList ll;
    // ll.deleteNode(list->next->next);
    prettyPrintLinkedList(ll.removeEndNthNode(list,7)); 
    return 0;
}