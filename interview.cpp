
#include <string>
#include "common.h"
using namespace std;

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

vector<int> buildHeap(vector<int> &arr)
{
    int len = arr.size();
    if (len <= 1)
        return arr;
    for (int i = 1; i < len; i++)
    {
        int parent = i / 2;
        int j = i;
        while (j > 0 && arr[j] > arr[parent])
        {
            swap(arr[j], arr[parent]);
            j = parent;
            parent = parent / 2;
        }
    }
    return arr;
}

string nextInDc(string &input)
{
    int len = input.size();
    if (len == 0)
        return "";
    int i = len - 1;
    //find the target position right->left
    for (; i > 0; i--)
    {
        if (input[i] > input[i - 1])
            break;
    }
    int pos = i - 1;
    i = len - 1;
    // find the next greater val in the past right part
    for (; i > 0; i--)
    {
        if (input[i] > input[pos])
            break;
    }
    // swap(input, pos, i);
    // sort(input, pos + 1, len - 1);
    return input;
}

int main(int argc, char const *argv[])
{
    vector<int> heap = {1, 3, 4, 5, 2};
    vector<int> res = buildHeap(heap);
    printVector(res);
    return 0;
}
