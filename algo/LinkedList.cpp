#include <vector>
#include <stdio.h>
#include <iostream>
#include <string>
#include "LinkedList.h"
#include "../common.h"
using namespace std;

// 21. Merge Two Sorted Lists
// 8 ms, faster than 85.20%
// 14.8 MB, less than 95.62%

ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
{
  ListNode *first = l1;
  ListNode *second = l2;
  ListNode *head = new ListNode(0);
  ListNode *dummy = head;
  while (first && second)
  {
    if (first->val < second->val)
    {
      dummy->next = first;
      first = first->next;
    }
    else
    {
      dummy->next = second;
      second = second->next;
    }
    dummy = dummy->next;
  }
  if (first)
    dummy->next = first;
  else if (second)
    dummy->next = second;
  dummy = head->next;
  delete head;
  head = nullptr;
  return dummy;
}

vector<my2arr> testmergeTwoLists()
{
  vector<my2arr> cases = {
      {{1, 2, 3}, {4, 5, 6}},
      {{1, 2, 4}, {1, 3, 4}},
      {{}, {}},
      {{}, {1}},

  };

  return move(cases);
}

// 206. Reverse Linked List
// 8 ms, faster than 77.19%
//  8.5 MB, less than 85.01%
ListNode *reverseList(ListNode *head)
{
  if (!head || !head->next)
    return head;
  ListNode *nhead = reverseList(head->next);
  head->next->next = head;
  head->next = nullptr;
  return nhead;
}

// 206. Reverse Linked List
//  0 ms, faster than 100.00%
// 8.1 MB, less than 98.97%
ListNode *reverseListI(ListNode *head)
{
  ListNode *dummy = head;
  ListNode *last = nullptr;
  ListNode *next = nullptr;
  while (dummy)
  {
    next = dummy->next;
    dummy->next = last;
    last = dummy;
    dummy = next;
  }
  return last;
}

my2arr testreverseList()
{
  my2arr cases = {
      {},
      {1},
      {1, 2},
      {1, 2, 3},
      {1, 2, 3, 4},
      {4, 2, 2, 3},
      {3, 2, 2, 3},
  };
  return move(cases);
}

// 234. Palindrome Linked List
// 12 ms, faster than 99.51%
// 13.8 MB, less than 97.36%
bool isPalindrome(ListNode *head)
{
  ListNode *slow = head;
  ListNode *fast = head;

  while (fast && fast->next)
  {
    fast = fast->next->next;
    slow = slow->next;
  }

  if (fast)
    slow = slow->next;

  ListNode *dummy = slow;
  ListNode *next = nullptr;
  ListNode *last = nullptr;

  while (dummy)
  {
    next = dummy->next;
    dummy->next = last;
    last = dummy;
    dummy = next;
  }

  while (last)
  {
    if (head->val != last->val)
      return false;
    head = head->next;
    last = last->next;
  }
  return true;
}

my2arr testisPalindrome()
{
  return {
      {1},
      {1, 2},
      {1, 2, 1},
      {4, 2, 2, 3},
      {3, 2, 2, 3},
  };
}

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

pair<ListNode *, int> splitListH(ListNode *pivot, int len)
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

ListNode *qSortListH(ListNode *head, int len)
{
  pair<ListNode *, int> pa = splitListH(head, len);
  int spos = pa.second;
  ListNode *snode = pa.first;
  if (spos > 1)
    qSortListH(head, spos);
  if (len - spos - 1 > 1 && snode->next)
    qSortListH(snode->next, len - spos - 1);
  return head;
}

// 148. Sort List
// Runtime: 460 ms, faster than 7.65% of C++ online submissions for Sort List.
// Memory Usage: 16.2 MB, less than 39.73% of C++ online submissions for Sort Lis
ListNode *sortListH(ListNode *head)
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
  return qSortListH(head, sz);
}

ListNode *splitList(ListNode *head, ListNode *pivot)
{
  // len > 1
  ListNode *lower = new ListNode(100001, head); // record the actual ones smaller than pivot
  ListNode *higher = head;
  // split
  while (higher != pivot)
  {
    if (higher->val < pivot->val)
    {
      dumySwap(lower->next, higher);
      lower = lower->next;
    }
    higher = higher->next;
  }
  dumySwap(lower->next, pivot);
  return lower;
}

ListNode *qSortList(ListNode *head, ListNode *tail)
{
  if (head == tail)
    return head;
  ListNode *pre_split = splitList(head, tail);
  if (pre_split->next != head)
    qSortList(head, pre_split);
  if (pre_split->next != tail)
    qSortList(pre_split->next->next, tail);
  return head;
}

ListNode *sortList(ListNode *head)
{
  if (!head)
    return nullptr;
  ListNode *tmp = head;
  ListNode *tail = head;
  while (tmp)
  {
    if (!tmp->next)
    {
      tail = tmp;
      break;
    }
    tmp = tmp->next;
  }
  if (tail == head)
    return head;
  return qSortList(head, tail);
}

void testsortList()
{
  my2arr cases = {
      {4, 2, 1, 3},
      {1, 2},
      {1, 3, 2},
      {2, 1},
      {4, 3, 2, 1},
      {-1, 5, 3, 4, 0},
      {1, 2, 6, 4, 5},
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

void insert(ListNode *head, ListNode *node)
{
  ListNode *tmp = head;
  while (tmp != node)
  {
    if (node->val > tmp->val)
    {
      tmp = tmp->next;
    }
    else
      break;
  }
  if (tmp == node)
    return;
  // [tmp...node-1], shift 1
  int nextv = tmp->val;
  tmp->val = node->val;
  int tv;
  while (tmp != node)
  {
    tv = tmp->next->val;
    tmp->next->val = nextv;
    nextv = tv;
    tmp = tmp->next;
  }
}

// 147. Insertion Sort List
// Runtime: 96 ms, faster than 10.01% of C++ online submissions for Insertion Sort List.
// Memory Usage: 10 MB, less than 18.80% of C++ online submissions for Insertion Sort List.
ListNode *insertionSortList(ListNode *head)
{
  ListNode *end = head;
  while (end && end->next)
  {
    insert(head, end->next);
    end = end->next;
  }
  return head;
}

void testinsertionSortList()
{
  my2arr cases = {
      {1, 2},
      {2, 1},
      {4, 2, 1, 3},
      {1, 3, 2},
      {4, 3, 2, 1},
      {-1, 5, 3, 4, 0},
      {1, 2, 6, 4, 5},
      {},
  };

  for (auto &&item : cases)
  {
    ListNode *head = vectorToListNode(item);
    prettyPrintLinkedList(head);
    insertionSortList(head);
    cout << "sorted list: " << endl;
    prettyPrintLinkedList(head);
    cout << endl;
  }
}

template <typename F>
void testLinkedList(F func, my2arr &&cas)
{
  my2arr &&cases = std::move(cas);
  for (auto &&item : cases)
  {
    ListNode *head = vectorToListNode(item);
    prettyPrintLinkedList(head);
    ListNode *res = func(head);
    cout << "result: " << endl;
    prettyPrintLinkedList(res);
    cout << endl;
  }
}

template <typename F, typename P>
void testLinkedList(F func, my2arr cases, P print)
{
  for (auto &&item : cases)
  {
    ListNode *head = vectorToListNode(item);
    prettyPrintLinkedList(head);
    auto res = func(head);
    cout << "result: " << endl;
    print(res);
    cout << endl;
  }
}

template <typename F>
void test2LinkedList(F func, vector<my2arr> &&cas)
{
  vector<my2arr> &&cases = std::move(cas);
  for (auto &&item : cases)
  {
    ListNode *l1 = vectorToListNode(item[0]);
    prettyPrintLinkedList(l1);

    ListNode *l2 = vectorToListNode(item[1]);
    prettyPrintLinkedList(l2);
    ListNode *res = func(l1, l2);
    cout << "result: " << endl;
    prettyPrintLinkedList(res);
    cout << endl;
  }
}

int main()
{

  // testsortList();
  // testinsertionSortList();
  // testLinkedList(isPalindrome, testisPalindrome(), [](bool result){cout<<"isPalindrome: "<<result<<endl;});
  // testLinkedList(reverseList, testreverseList());
  test2LinkedList(mergeTwoLists, testmergeTwoLists());
  return 0;
}