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

void prettyPrintLinkedList(ListNode *node, int pos = 0)
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

void testCycle()
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
}

void dumySwap(ListNode *n1, ListNode *n2)
{
  if (n1 == n2)
    return;
  int tmp = n1->val;
  n1->val = n2->val;
  n2->val = tmp;
}

pair<ListNode *, int> splitList(ListNode *pivot, int len)
{
  // len > 1
  ListNode *lower = pivot; // for "next" lower node
  ListNode *higher = pivot->next;
  int pos = 0;
  // split
  while (higher && len > 1)
  {
    if (higher->val < pivot->val)
    {
      dumySwap(higher, lower->next);
      lower = lower->next;
      pos++;
    }
    higher = higher->next;
    len--;
  }
  if (pos > 0)
    dumySwap(lower, pivot);
  return pair<ListNode *, int>{lower, pos};
}

ListNode *qSortList(ListNode *head, int len)
{
  pair<ListNode *, int> pa = splitList(head, len);
  int spos = pa.second;
  ListNode *snode = pa.first;
  if (spos > 1)
    qSortList(head, spos);
  if (len - spos - 1 > 1 && snode->next)
    qSortList(snode->next, len - spos - 1);
  return head;
}

// 148. Sort List
// Runtime: 460 ms, faster than 7.65% of C++ online submissions for Sort List.
// Memory Usage: 16.2 MB, less than 39.73% of C++ online submissions for Sort Lis
ListNode *sortList(ListNode *head)
{
  if (!head)
    return nullptr;
  int sz = 0;
  ListNode *tmp = head;
  while (tmp)
  {
    sz++;
    tmp = tmp->next;
  }
  //compute sz
  if (sz == 1)
    return head;
  return qSortList(head, sz);
}

#include "common.h"
void testsortList()
{
  my2arr cases = {
      {1, 3, 2},
      {1, 2},
      {2, 1},
      {4, 2, 1, 3},
      {-1, 5, 3, 4, 0},
      {},
  };

  for (auto &&item : cases)
  {
    ListNode *head = vectorToListNode(item);
    prettyPrintLinkedList(head);
    sortList(head);
    cout << "sorted list: " << endl;
    prettyPrintLinkedList(head);
    cout << endl;
  }
}

int main()
{

  testsortList();
  return 0;
}