#include <array>
#include <list>
#include <assert.h>
using namespace std;
// 705. Design HashSet
class MyHashSet
{
public:
    /** Initialize your data structure here. */
    MyHashSet()
    {
    }

    void add(int key)
    {
        auto &vals = data[key % size];
        if (vals.empty())
        {
            vals.push_back(key);
        }
        else
        {
            for (auto &&i : vals)
            {
                if (i == key)
                    return;
            }
            vals.push_back(key);
        }
    }

    void remove(int key)
    {
        auto &vals = data[key % size];
        vals.remove_if([key, this](auto &&val) {
            if (val == key)
                return true;
            return false;
        });
    }

    /** Returns true if this set contains the specified element */
    bool contains(int key)
    {
        auto &vals = data[key % size];
        if (!vals.empty())
        {
            for (auto &&i : vals)
            {
                if (i == key)
                    return true;
            }
        }
        return false;
    }

private:
    constexpr static size_t size{10000};
    array<list<int>, size> data; //Runtime: 144 ms, faster than 39.38%
};

void testHashSet()
{

    // Your MyHashSet object will be instantiated and called as such:

    MyHashSet *hashSet = new MyHashSet();
    hashSet->add(1);
    hashSet->add(2);
    assert(hashSet->contains(1));  // returns true
    assert(!hashSet->contains(3)); // returns false (not found)
    hashSet->add(2);
    assert(hashSet->contains(2)); // returns true
    hashSet->remove(2);
    assert(!hashSet->contains(2)); // returns false (already removed)
}

#include "../common.h"
int main(int argc, char const *argv[])
{
    timeit(testHashSet);
    return 0;
}
