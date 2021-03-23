
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

#include <string>
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

// 2th interview 20210315  Yang Guang
// can pick m*n choices
// 373. Find K Pairs with Smallest Sums
vector<vector<int>> kSmallestPairs(vector<int> &nums1, vector<int> &nums2, int k)
{
    int m = nums1.size(), n = nums2.size();
    if (m == 0 || n == 0 || k == 0)
        return {};
    auto comp = [&nums1, &nums2](pair<int, int> &s1, pair<int, int> &s2) { return nums1[s1.first] + nums2[s1.second] > nums1[s2.first] + nums2[s2.second]; };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> heap(comp);
    heap.push(make_pair(0, 0));
    int i = 0, j = 0;
    int cnt = 0;
    vector<vector<int>> ans;
    k = (k < m * n) ? k : (m * n);
    while (cnt < k)
    {
        // can not use & here, because you release the value after
        //   auto& [i1,i2]=heap.top();
        auto [i1, i2] = heap.top();
        heap.pop();
        ans.push_back({nums1[i1], nums2[i2]});
        heap.push(make_pair(i1 + 1, i2));
        if (i1 == 0)
        {
            heap.push(make_pair(i1, i2 + 1));
        }
        cnt++;
    }
    return ans;
}

// 3th interview 20210315  Xu Fei
// "ace", "ae"  false
// "abc", "ba"-->true
// O(m+n) ,  m > n
// 567. Permutation in String
// 304 ms, faster than 7.45%
// 18.4 MB, less than 10.15%
bool checkInclusion(string s1, string s2)
{
    int m = s2.size(), n = s1.size();
    vector<int> dc(26, 0);
    for (auto &&c : s1)
    {
        dc[c - 'a']++;
    }
    for (int i = 0; i <= m - n; i++)
    {
        int j = i;
        auto curdc = dc;
        int c;
        for (; j < n + i; j++)
        {
            c = s2[j] - 'a';
            if (curdc[c] == 0)
                break;
            curdc[c]--;
            if (curdc[c] < 0)
                break;
        }
        if (j == n + i && curdc[c] == 0)
            return true;
    }
    return false;
}

// 3th interview 20210315 Xu Fei
const int NOT_FOUND = -1;
class MyHashMap
{
private:
    vector<list<pair<int, int>>> data;
    int capacity = 20;

public:
    MyHashMap()
    {
        data.resize(capacity);
    };
    ~MyHashMap() = default;

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
            for (auto &&kv : items)
            {
                if (kv.first > capacity)
                {
                    items.remove(kv);
                    add(kv.first, kv.second);
                }
            }
        }
        capacity *= 2;
    }
    void put(int key, int val)
    {
        rehash();
        add(key,val);
    }

    void add(int key, int val){
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

    void remove(int key){
        auto & list = data[hash(key)];
        remove_if(list.begin(),list.end(),[key,this](auto kv){return kv.first==key;});
        // for (auto &&kv : list)
        // {
        //     if (kv.first == key){
        //         list.remove(kv);
        //         return;
        //     }   
        // }
    }
    int get(int key)
    {
        auto &list = data[hash(key)];
        auto itr=find_if(list.begin(),list.end(),[key](auto& kv){return kv.first==key;});
        return itr==list.end()?-1:itr->second;
    }
};

#include <cassert>
#include <iostream>
void testMymap()
{
    MyHashMap *hashMap = new MyHashMap();
    hashMap->put(1, 1);
    hashMap->put(2, 2);
    hashMap->put(3, 2);
    assert(hashMap->get(1) == 1); // returns 1
    assert(hashMap->get(3) == 2);
    hashMap->put(2, 1);           // update the existing value
    hashMap->remove(2);           // update the existing value
    assert(hashMap->get(2) == NOT_FOUND); // returns 1
    assert(hashMap->get(1) == 1); // returns 1
    assert(hashMap->get(3) == 2); // returns 1

}

// 4th interview  20210315  Fan Yu
// 1706. Where Will the Ball Fall
//  24 ms, faster than 94.77%
// 13.2 MB, less than 90.05%
vector<int> findBall(vector<vector<int>> &grid)
{
    int m = grid.size();
    if (m == 0)
        return {};
    int n = grid[0].size();
    vector<int> succeed(n, -1);
    for (int ball = 0; ball < n; ball++)
    {
        int j = ball;
        int i = 0;
        for (; i < m; i++)
        {
            int wall = grid[i][j];
            if (wall == 1)
            {
                if (j == n - 1 || grid[i][j + 1] == -1)
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
                if (j == 0 || grid[i][j - 1] == 1)
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
            succeed[ball] = j;
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

// 5th interview  20210315 Ma Zhao Jia
// 236. Lowest Common Ancestor of s1 Binary Tree
Node *findCommonAncester(Node *root, Node *s1, Node *s2)
{
    deque<Node *> aqueue;
    deque<Node *> bqueue;
    deque<Node *> sta;
    sta.push_back(root);
    while (!sta.empty())
    {
        Node *tp = sta.back();
        if (tp == s1)
        {
            aqueue = sta;
        }
        else if (tp == s2)
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
    // checkInclusion("hello", "ooolleoooleh");
    testMymap();
    return 0;
}
