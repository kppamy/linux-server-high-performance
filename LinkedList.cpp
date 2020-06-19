#include <vector>
#include <stdio.h>
#include <iostream>
#include <string>
#include "LinkedList.h"

using namespace std;

ListNode *vectorToListNode(const vector<int> &list)
{
  // Now convert that list into linked list
  ListNode *dummyRoot = new ListNode(0);
  ListNode *ptr = dummyRoot;
  for (int item : list)
  {
    ptr->next = new ListNode(item);
    ptr = ptr->next;
  }
  ptr = dummyRoot->next;
  delete dummyRoot;
  return ptr;
}

ListNode *vectorToCircleListNode(const vector<int> &list, int pos)
{
  if (pos == -1)
  {
    return vectorToListNode(list);
  }
  // Now convert that list into linked list
  ListNode *dummyRoot = new ListNode(0);
  ListNode *ptr = dummyRoot;
  int counter = -1;
  ListNode *circle;
  for (int item : list)
  {
    ptr->next = new ListNode(item);
    ptr = ptr->next;
    counter++;
    if (counter == pos)
    {
      circle = ptr;
    }
  }
  ptr->next = circle;
  ptr = dummyRoot->next;
  delete dummyRoot;
  return ptr;
}

void prettyPrintLinkedList(ListNode *node, int pos)
{
  int counter = -1;
  ListNode *head = node;
  while (node)
  {
    cout << node->val << "->";
    counter++;
    if (counter == pos)
    {
      head = node;
    }
    node = node->next;
    if (node == head)
    {
      cout << endl;
      cout << string(3 * pos, ' ') + "!  " + string(3 * (counter - pos), ' ') + "!  " << endl;
      cout << string(3 * pos, ' ');
      for (int i = 0; i < counter + 1 - pos; i++)
        cout << " <-";
      cout << endl;
      break;
    }
  }
  cout << endl;
}

void LinkedList::deleteNode(ListNode *node)
{
  ListNode *nn = node->next;
  node->val = nn->val;
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

bool LinkedList::hasCycle(ListNode *head)
{
  ListNode *slow = head;
  ListNode *fast = head;
  while (slow && fast && fast->next)
  {
    fast = fast->next->next;
    if (slow == fast)
    {
      return true;
    }
    slow = slow->next;
  }
  return false;
}

int main()
{
  vector<int> input{1, 2, 3, 4, 5, 6, 7};
  // ListNode* list = vectorToListNode(input);
  int pos = -1;
  while (pos != -2)
  {
    ListNode *list = vectorToCircleListNode(input, pos);
    prettyPrintLinkedList(list, pos);
    LinkedList ll;
    cout << " has cycle: " << (ll.hasCycle(list) == 0 ? "no" : "yes") << " " << endl;
    cin >> pos;
  }
  // ll.deleteNode(list->next->next);
  // prettyPrintLinkedList(ll.removeEndNthNode(list,7));
  return 0;
}