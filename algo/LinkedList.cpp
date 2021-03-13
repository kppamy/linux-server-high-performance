#include <vector>
#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include "LinkedList.h"
#include "../common.h"
using namespace std;

// 21. Merge Two Sorted Lists
// 4 ms, faster than 97.50%
// 14.8 MB, less than 87.01%
ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
{
  ListNode *dummy = new ListNode(INT_MAX);
  ListNode *head = dummy;
  while (l1 && l2)
  {
    if (l1->val <= l2->val)
    {
      dummy->next = l1;
      l1 = l1->next;
    }
    else
    {
      dummy->next = l2;
      l2 = l2->next;
    }
    dummy = dummy->next;
  }
  ListNode *left = l1 == nullptr ? l2 : l1;
  dummy->next = left;
  return head->next;
}

// 92. Reverse Linked List II
// 4 ms, faster than 59.80%
//  0 ms, faster than 100.00%
//  7.5 MB, less than 72.45%
ListNode *reverseBetween(ListNode *head, int left, int right)
{
  int cnt = 0;
  ListNode *before = new ListNode(501);
  before->next = head;
  ListNode *dummy = before; // mind before changes
  ListNode *after;
  ListNode *prev;
  ListNode *next;

  // 4  1 - 2  -- 3  5 ||  2, 4
  // 1 2 3 || 1 , 2
  // 1 2 3 || 2 , 3
  // 1 2  || 1 , 2
  // 1  || 1 , 1
  while (head)
  {
    cnt++;
    if (cnt > right)
      break;
    if (cnt < left)
    {
      before = head;
      head = head->next;
    }
    else
    {
      next = head->next;
      head->next = prev;
      if (cnt == left)
      {
        after = head;
      }
      prev = head;
      if (cnt == right)
      {
        after->next = next;
        before->next = head;
      }
      head = next;
    }
  }
  return dummy->next;
}

// 206. Reverse Linked List
// 8 ms, faster than 72.20% o
//  8.3 MB, less than 61.62%
ListNode *reverseList(ListNode *head)
{
  // 1->2->3
  // 1<-2  3
  ListNode *next;
  ListNode *prev = nullptr;
  while (head)
  {
    next = head->next;
    head->next = prev;
    prev = head;
    head = next;
  }
  return prev;
}

// 82. Remove Duplicates from Sorted List II
//  8 ms, faster than 84.54%
// 11.2 MB, less than 82.40%
ListNode *deleteDuplicates(ListNode *head)
{
  ListNode *dummy = new ListNode(101);
  dummy->next = head;
  ListNode *prev = dummy;
  ListNode *current = head;
  while (current)
  {
    // 1 2 3 3 4 4 5
    // 1,1,1,2,3
    // 1,1
    // [1,2,2]
    if (current->next != nullptr && current->val == current->next->val)
    {
      do
      {
        current = current->next;
      } while (current->next != nullptr && current->val == current->next->val);
      prev->next = current->next;
    }
    else
    {
      prev = prev->next;
    }
    current = current->next;
  }
  return dummy->next;
}

// 203. Remove Linked List Elements
// 20 ms, faster than 91.13%
// 15 MB, less than 60.00% o
ListNode *removeElements(ListNode *head, int val)
{
  ListNode *dummy = new ListNode(-1);
  dummy->next = head;
  ListNode *prev = dummy;
  ListNode *current = head;
  while (current)
  {
    if (current->val == val)
    {
      prev->next = current->next;
    }
    else
      prev = current;
    current = current->next;
  }
  return dummy->next;
}

// 237. Delete Node in a Linked List
// 12 ms, faster than 88.39%
// 7.6 MB, less than 60.20%
void deleteNode(ListNode *node)
{
  ListNode *mid = node;
  while (mid && mid->next && mid->next->next)
  {
    mid->val = mid->next->val;
    mid = mid->next;
  }
  if (mid->next)
  {
    mid->val = mid->next->val;
    mid->next = nullptr;
  }
}

// 1290. Convert Binary Number in a Linked List to Integer
// 0 ms, faster than 100.00%
// 8.2 MB, less than 94.17%
int getDecimalValue(ListNode *head)
{
  int ans = 0;
  while (head)
  {
    ans = (ans << 1) + head->val;
    head = head->next;
  }
  return ans;
}

// 876. Middle of the Linked List
// 0 ms, faster than 100.00%
//  6.6 MB, less than 57.70%
ListNode *middleNode(ListNode *head)
{
  ListNode *slow = head;
  ListNode *fast = head;
  while (fast && fast->next)
  {
    slow = slow->next;
    fast = fast->next->next;
  }
  return slow;
}

// 160. Intersection of Two Linked Lists
// 36 ms, faster than 95.71%
// 14.5 MB, less than 88.89%
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
{
  auto getlen = [](ListNode *head) {
    ListNode *slow = head;
    ListNode *fast = head;
    int sz = 0;
    while (fast && fast->next)
    {
      fast = fast->next->next;
      slow = slow->next;
      sz++;
    }
    if (!fast)
      sz *= 2;
    else
      sz = sz * 2 + 1;
    return sz;
  };
  int la = getlen(headA);
  int lb = getlen(headB);
  if (la > lb)
  {
    int skipa = la - lb;
    while (skipa > 0)
    {
      headA = headA->next;
      skipa--;
    }
  }
  else if (la < lb)
  {
    int skipb = lb - la;
    while (skipb > 0)
    {
      headB = headB->next;
      skipb--;
    }
  }
  while (headA && headB)
  {
    if (headA == headB)
      return headA;
    headA = headA->next;
    headB = headB->next;
  }
  return nullptr;
}

// 160. Intersection of Two Linked Lists
//  60 ms, faster than 26.00%
// 17.8 MB, less than 9.96%
ListNode *getIntersectionNodeHM(ListNode *headA, ListNode *headB)
{

  map<ListNode *, int> amap;
  while (headA)
  {
    amap[headA] = headA->val;
    headA = headA->next;
  }
  while (headB)
  {
    if (amap.find(headB) != amap.end())
      return headB;
    headB = headB->next;
  }
  return nullptr;
}

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
  ListNode *current = dummyRoot;
  for (int item : list)
  {
    current->next = new ListNode(item);
    current = current->next;
  }
  current = dummyRoot->next;
  delete dummyRoot;
  return current;
}

ListNode *vectorToCircleListNode(const vector<int> &list, int pos)
{
  if (pos == -1)
  {
    return vectorToListNode(list);
  }
  // Now convert that list into linked list
  ListNode *dummyRoot = new ListNode(0);
  ListNode *current = dummyRoot;
  int counter = -1;
  ListNode *circle;
  for (int item : list)
  {
    current->next = new ListNode(item);
    current = current->next;
    counter++;
    if (counter == pos)
    {
      circle = current;
    }
  }
  current->next = circle;
  current = dummyRoot->next;
  delete dummyRoot;
  return current;
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

ListNode *qSortList(ListNode *head, ListNode *current)
{
  if (head == current)
    return head;
  ListNode *pre_split = splitList(head, current);
  if (pre_split->next != head)
    qSortList(head, pre_split);
  if (pre_split->next != current)
    qSortList(pre_split->next->next, current);
  return head;
}

ListNode *sortList(ListNode *head)
{
  if (!head)
    return nullptr;
  ListNode *tmp = head;
  ListNode *current = head;
  while (tmp)
  {
    if (!tmp->next)
    {
      current = tmp;
      break;
    }
    tmp = tmp->next;
  }
  if (current == head)
    return head;
  return qSortList(head, current);
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