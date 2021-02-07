#include <array>
#include <vector>
#include <list>
using namespace std;

// 1512. Number of Good Pairs
//  0 ms, faster than 100.00% o
//  7.2 MB, less than 79.44%
int numIdenticalPairs(vector<int> &nums)
{
    vector<int> cnt(101, 0);
    int len = nums.size();
    int ans = 0;
    for (int i = 0; i < len; i++)
    {
        cnt[nums[i]]++;
        int num = cnt[nums[i]];
        if (num > 1)
        {
            ans += num - 1;
        }
    }
    return ans;
}

// 706. Design HashMap
// allocat heap memory dynamically: 192 ms, faster than 22.05%;  56.7 MB, less than 44.70%
// initialize enough memory at the begining: 164 ms, faster than 52.59% ;  54.9 MB, less than 52.43% ,
// using array: 144 ms, faster than 90.27%;  54.8 MB, less than 52.43%,
class MyHashMap
{
public:
    /** Initialize your data structure here. */
    MyHashMap()
    {
        // data.resize(capacity);
        // data.fill({});
    }

    /** value will always be non-negative. */
    void put(int key, int value)
    {
        // if (size >= capacity / 2)
        // {
        //     // copy all to newqas
        //     capacity *= 2;
        //     data.resize(capacity);
        //     for (int i = 0; i < capacity / 2; i++)
        //     {
        //         auto pairs = data[i];
        //         // auto& pairs = data[i]; // invalid iterator after data[i].remove(p)
        //         for (auto &&p : pairs)
        //         {
        //             int npos = mhash(p.first);
        //             if (npos != i)
        //             {
        //                 data[i].remove(p);
        //                 data[npos].emplace_back(move(p));
        //             }
        //         }
        //     }
        // }
        auto val = make_pair(key, value);
        auto &samekeys = data[mhash(key)]; // [] on vector return T&, samekeys is a reference to lvalue
        // auto tt = data[mhash(key)];// tt is a deduced to a lvalue, copy
        if (samekeys.empty())
            samekeys.emplace_back(move(val));
        else
        {
            for (auto &&[first, second] : samekeys)
            {
                if (first == key)
                {
                    second = value;
                    return;
                }
            }
            samekeys.emplace_back(move(val));
        }
        // size++;
    }

    //  don't consider hash collision
    int mhash(int key)
    {
        return (key % capacity);
    }
    /** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
    int get(int key)
    {

        auto &samekeys = data[mhash(key)];
        if (samekeys.empty())
            return -1;
        else
        {
            for (auto &&[first, second] : samekeys)
            {
                if (first == key)
                {
                    return second;
                }
            }
        }

        return -1;
    }

    /** Removes the mapping of the specified value key if this map contains a mapping for the key */
    void remove(int key)
    {
        auto &samekeys = data[mhash(key)];
        samekeys.remove_if([key, this](auto x) {
            if (x.first == key)
            {
                // size--;
                return true;
            }
            return false;
        });
    }

private:
    // int capacity{20};
    constexpr static int capacity{10000};
    // int size{0};
    // vector<list<pair<int, int>>> data;
    array<list<pair<int, int>>, capacity> data;
};

#include <assert.h>
#include <string>
#include <iostream>
void testHashMap()
{
    {
        MyHashMap *hashMap = new MyHashMap();
        hashMap->put(1, 1);
        hashMap->put(2, 2);
        assert(hashMap->get(1) == 1);  // returns 1
        assert(hashMap->get(3) == -1); // returns -1 (not found)
        hashMap->put(2, 1);            // update the existing value
        assert(hashMap->get(2) == 1);  // returns 1
        hashMap->remove(2);            // remove the mapping for 2
        assert(hashMap->get(2) == -1); // returns -1 (not found)
    }

    {
        vector<string> cmds{"MyHashMap", "remove", "put", "remove", "remove", "get", "remove", "put", "get", "remove", "put", "put", "put", "put", "put", "put", "put", "put", "put", "put", "put", "remove", "put", "put", "get", "put", "get", "put", "put", "get", "put", "remove", "remove", "put", "put", "get", "remove", "put", "put", "put", "get", "put", "put", "remove", "put", "remove", "remove", "remove", "put", "remove", "get", "put", "put", "put", "put", "remove", "put", "get", "put", "put", "get", "put", "remove", "get", "get", "remove", "put", "put", "put", "put", "put", "put", "get", "get", "remove", "put", "put", "put", "put", "get", "remove", "put", "put", "put", "put", "put", "put", "put", "put", "put", "put", "remove", "remove", "get", "remove", "put", "put", "remove", "get", "put", "put"};
        vector<vector<int>> parameters{{}, {27}, {65, 65}, {19}, {0}, {18}, {3}, {42, 0}, {19}, {42}, {17, 90}, {31, 76}, {48, 71}, {5, 50}, {7, 68}, {73, 74}, {85, 18}, {74, 95}, {84, 82}, {59, 29}, {71, 71}, {42}, {51, 40}, {33, 76}, {17}, {89, 95}, {95}, {30, 31}, {37, 99}, {51}, {95, 35}, {65}, {81}, {61, 46}, {50, 33}, {59}, {5}, {75, 89}, {80, 17}, {35, 94}, {80}, {19, 68}, {13, 17}, {70}, {28, 35}, {99}, {37}, {13}, {90, 83}, {41}, {50}, {29, 98}, {54, 72}, {6, 8}, {51, 88}, {13}, {8, 22}, {85}, {31, 22}, {60, 9}, {96}, {6, 35}, {54}, {15}, {28}, {51}, {80, 69}, {58, 92}, {13, 12}, {91, 56}, {83, 52}, {8, 48}, {62}, {54}, {25}, {36, 4}, {67, 68}, {83, 36}, {47, 58}, {82}, {36}, {30, 85}, {33, 87}, {42, 18}, {68, 83}, {50, 53}, {32, 78}, {48, 90}, {97, 95}, {13, 8}, {15, 7}, {5}, {42}, {20}, {65}, {57, 9}, {2, 41}, {6}, {33}, {16, 44}, {95, 30}};
        vector<int> results{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 90, -1, -1, -1, -1, 40, -1, -1, -1, -1, -1, 29, -1, -1, -1, -1, 17, -1, -1, -1, -1, -1, -1, -1, -1, -1, 33, -1, -1, -1, -1, -1, -1, 18, -1, -1, -1, -1, -1, -1, 35, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 87, -1, -1};
        MyHashMap *hashMap = new MyHashMap();
        for (int i = 1; i < cmds.size(); i++)
        {
            if (cmds[i] == "put")
            {
                hashMap->put(parameters[i][0], parameters[i][1]);
            }
            else if (cmds[i] == "get")
            {
                if (hashMap->get(parameters[i][0]) != results[i])
                {
                    cout << "failed............" << endl;
                }
            }
            else if (cmds[i] == "remove")
            {
                hashMap->remove(parameters[i][0]);
            }
        }
    }
}

#include "../common.h"
int main(int argc, char const *argv[])
{
    timeit(testHashMap);
    return 0;
}
