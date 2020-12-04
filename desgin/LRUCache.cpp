#include <unordered_map>
#include <list>
#include <utility>
using namespace std;
// 146. LRU Cache
// 140 ms, faster than 73.25%
class LRUCache
{
public:
    LRUCache(int capacity) : capa(capacity)
    {
    }

    int get(int key)
    {

        auto itr = data.find(key);
        if (itr != data.end())
        {
            auto &old = (itr->second).second;
            history.erase(old);
            history.push_front(key);
            old = history.begin();
            return itr->second.first;
        }
        else
        {
            return -1;
        }
    }

    void put(int key, int value)
    {

        auto itr = data.find(key);
        if (itr != data.end())
        {
            auto &old = (itr->second).second;
            history.erase(old);
        }
        else
        {
            if (data.size() == capa)
            {
                data.erase(history.back());
                history.pop_back();
            }
        }
        history.push_front(key);
        data[key] = make_pair(value, history.begin());
    }

private:
    using liter = list<int>::iterator;
    list<int> history;
    unordered_map<int, pair<int, liter>> data;
    size_t capa{0};
};

#include <assert.h>
#include <vector>
#include <iostream>
void testLRU()
{

    {
        vector<string> cmds{"LRUCache", "put", "put", "get", "put", "get", "get"};
        vector<vector<int>> parameters{{{2}, {2, 1}, {1, 1}, {2}, {4, 1}, {1}, {2}}};
        vector<int> results{-1, -1, -1, 1, -1, 1, -1};
        LRUCache *hashMap = new LRUCache(2);
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
        }
    }

    {
        LRUCache *lRUCache = new LRUCache(2);
        lRUCache->put(1, 1);            // cache is {1=1}
        lRUCache->put(2, 2);            // cache is {1=1, 2=2}
        assert(lRUCache->get(1) == 1);  // return 1
        lRUCache->put(3, 3);            // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
        assert(lRUCache->get(2) == -1); // returns -1 (not found)
        lRUCache->put(4, 4);            // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
        assert(lRUCache->get(1) == -1); // return -1 (not found)
        assert(lRUCache->get(3) == 3);  // return 3
        assert(lRUCache->get(4) == 4);  // return 4
    }
}

#include "../common.h"
int main(int argc, char const *argv[])
{
    timeit(testLRU);
    return 0;
}
