#include <stddef.h>
#include <vector>
using namespace std;
/**
 * Definition for singly-linked list. */

struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
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
    ListNode* buildCircleList(vector<int> &input, int pos);
    bool hasCycle(ListNode *head);
};
