
#include <vector>
#include <list>
#include <queue>
using namespace std;

// 1th interview
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
// 1th interview
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

// 2th interview 20210315
// can pick m*n choices
// 373. Find K Pairs with Smallest Sums
vector<vector<int>> kSmallestPairs(vector<int> &nums1, vector<int> &nums2, int k)
{
    int m=nums1.size(),n=nums2.size();
    priority_queue<int, std::greater<int>> heap;
    heap.push(nums1[0]+nums2[0]);
    int i=0, j=0;
    int cnt=0;
    int kmin;
    while (cnt<k)
    {
      heap.push(nums1[i+1]+nums2[j]);
      kmin=heap.top();
      heap.pop();
      cnt++;
    }
    
}

// 3th interview 20210315
// "ace", "ae"  false
// "abc", "ba"-->true
// O(m+n)
bool findOutofOrderSubstring(string a, string b)
{
}

// 3th interview 20210315
const int NOT_FOUND = INT_MAX;
class Mymap
{
private:
    vector<list<pair<int, int>>> data;
    int capacity = 20;

public:
    Mymap()
    {
        data.resize(20);
    };
    ~Mymap() = default;

    int hash(int key)
    {
        return key % capacity;
    }

    void rehash()
    {
        if (data.size() < capacity / 2)
            return;
        data.resize(capacity * 2);
        for (auto &&items : data)
        {
            for (auto &&[key, val] : items)
            {
                if (key > capacity)
                {
                    // delete the old one
                    put(key, val);
                }
            }
        }
        capacity *= 2;
    }
    void put(int key, int val)
    {
        rehash();
        auto &items = data[hash(key)];
        for (auto &&[k, v] : items)
        {
            if (k == key)
            {
                v = val;
                return;
            }
        }
        items.push_back(make_pair(key, val));
    }

    int get(int key)
    {
        auto &list = data[hash(key)];
        for (auto &&kv : list)
        {
            if (kv.first == key)
                return kv.second;
        }
        return NOT_FOUND;
    }
};

#include <cassert>
#include <iostream>
void testMymap()
{
    Mymap *hashMap = new Mymap();
    hashMap->put(1, 1);
    hashMap->put(2, 2);
    assert(hashMap->get(1) == 1); // returns 1
    assert(hashMap->get(3) == NOT_FOUND);
    hashMap->put(2, 1);           // update the existing value
    assert(hashMap->get(2) == 1); // returns 1
}

// 4th interview  20210315
vector<int> canFall(vector<vector<int>> &walls)
{
    int m = walls.size();
    if (m == 0)
        return {};
    int n = walls[0].size();
    vector<int> succeed(n, -1);
    for (int ball = 0; ball < n; ball++)
    {
        int j = ball;
        int i = 0;
        for (; i < m; i++)
        {
            int wall = walls[i][j];
            if (wall == 1)
            {
                if (j == n - 1 || walls[i][j + 1] == -1)
                {
                    break;
                }
                else
                {
                    j++;
                }
            }
            else
            {
                if (j == 0 || walls[i][j - 1] == 1)
                {
                    break;
                }
                else
                {
                    j--;
                }
            }
        }
        if (i == m)
            succeed[ball] = 1;
    }
    return succeed;
}

#include <deque>
#include <stack>
class Node
{
public:
    int val;
    vector<Node *> children;

    Node() {}

    Node(int _val)
    {
        val = _val;
    }

    Node(int _val, vector<Node *> _children)
    {
        val = _val;
        children = _children;
    }
};

// 5th interview  20210315
Node *findCommonAncester(Node *root, Node *a, Node *b)
{
    deque<Node *> aqueue;
    deque<Node *> bqueue;
    deque<Node *> sta;
    sta.push_back(root);
    while (!sta.empty())
    {
        Node *tp = sta.back();
        if (tp == a)
        {
            aqueue = sta;
        }
        else if (tp == b)
        {
            bqueue = sta;
        }
        if (aqueue.size() > 0 && bqueue.size() > 0)
        {
            break;
        }
        if (tp->children.size() == 0)
        {
            sta.pop_back();
        }
        else
        {
            Node *ch = tp->children.back();
            tp->children.pop_back();
            sta.push_back(ch);
        }
    }

    Node *parent = root;
    while (!aqueue.empty() && !bqueue.empty())
    {
        if (aqueue.front() != bqueue.front())
            return parent;
        parent = aqueue.front();
        aqueue.pop_front();
        bqueue.pop_front();
    }
    return parent;
}

int main(int argc, char const *argv[])
{

    return 0;
}
