#include <string>
#include "common.h"
using namespace std;

// 1th interview 20210310
void mergeSortedArray(vector<int> &arr1, vector<int> &arr2)
{
    int s1 = arr1.size(), s2 = arr2.size(), n=s2-s1;
    if (s1 == 0)
        return;
    int p1 = s1 - 1, p2 = n - 1, pos = s2 - 1;
    while (pos >= 0)
    {
        int target;
        if (p1 < 0)
            break;
        if (arr1[p1] > arr2[p2])
        {
            target = arr1[p1];
            p1--;
        }
        else
        {
            target = arr2[p2];
            p2--;
        }
        arr2[pos] = target;
        pos--;
    }
}

// 1th interview 20210310
const ListNode *commonNode(const ListNode *l1, const ListNode *l2, int len1, int len2)
{
    if (l1 == nullptr || l2 == nullptr)
        return nullptr;
    int dis = abs(len1 - len2);
    const ListNode *who = (len1 > len2) ? l1 : l2;
    const ListNode *another = (len1 > len2) ? l2 : l1;
    for (int i = 0; i < dis; i++)
    {
        who = who->next;
    }

    while (who != another)
    {
        who = who->next;
        another = another->next;
    }
    return who;
}

enum class BULLET
{
    READ,
    BLUE
};

// enum BULLET2
// {
//     READ,
//     BLUE
// } ;

// 1th interview 20210310
void sortBullets(vector<BULLET> &arr)
{
    int sz = arr.size();
    if (sz <= 1)
        return;
    int r = 0, b = sz - 1;
    while (r <= b)
    {
        BULLET rb = arr[r], bb = arr[b];
        if (rb == BULLET::BLUE && bb == BULLET::READ)
        {
            swap(rb, bb);
            r++;
            b--;
        }
        else if (rb == BULLET::BLUE)
        {
            b--;
        }
        else if (bb == BULLET::READ)
        {
            r++;
        }
        else
        {
            r++;
            b--;
        }
    }
}



// 2th interview 20210314
// 9,  1001,
// 1000, 0
// 1000101,
int binaryDis(int n)
{
    int ans = 0;
    int beg = 0;
    int cnt = 0;
    while (n != 0)
    {
       cnt++;
       if(n& 1==1){
            if (beg == 0)
                beg = cnt;
            else
            {
                int dis = cnt - beg -1;
                if (dis > ans)
                {
                    ans = dis;
                }
            }
       }else if(ans!=0){
           beg=cnt-1;
       }
       n=n>>1;    
    }
    return ans;
}

// 9,  1001,
// 1000, 0
// 1000101,
int binaryDis2(int n)
{
    int ans = 0;
    int cnt = 0;
    bool flag=false;
    while (n != 0)
    {
       if(n& 1==1){
           if(!flag){
               flag=true;
           }else{
              ans=ans>cnt?ans:cnt;
              cnt=0;
           }
       }else if(flag){
           cnt++;
       }
       n=n>>1;    
    }
    return ans;
}


// fifo
// queue
// array,

// list: data,ptr*  o(1)

// time comple:

#include <vector>
using namespace std;



const int MAX_SZ = 100;
int data[MAX_SZ];
const int ERROR = INT_MIN;
const int SUCCESS = INT_MAX;

int front = 0;
int end = 0;
int sz = 0;

bool isEmpty()
{
    return sz == 0;
}
bool isFull()
{
    return sz >= MAX_SZ;
}
int push(int val)
{
    if (isFull())
    {
        return ERROR;
    }
    data[end] = val;
    end++;
    if (end == MAX_SZ)
        end = 0;
    sz++;
    return SUCCESS;
}

// push to end of queue,   max 4, push 4 , pop 1

int pop()
{
    if (isEmpty())
    {
        return ERROR;
    }
    int val = data[front];
    front++;
    sz--;
    if (front == MAX_SZ)
        front = 0;
    return val;
}
