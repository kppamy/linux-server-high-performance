#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <stddef.h>
#include <vector>
/**
 * Definition for singly-linked list. */

struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
     ListNode(int x, ListNode* ne) : val(x), next(ne){}
 };


class LinkedList
{
private:
    ListNode *data;
    int size = 0;
public:
    LinkedList(ListNode* head, int len){
    data = head;
    size = len;
};
    LinkedList(){};
    ~LinkedList(){
        data = NULL;
        delete data;
    };
    void deleteNode(ListNode *node);
    ListNode* removeEndNthNode(ListNode *head, int n);
    ListNode* buildCircleList(std::vector<int> &input, int pos);
    bool hasCycle(ListNode *head);
};

#endif   