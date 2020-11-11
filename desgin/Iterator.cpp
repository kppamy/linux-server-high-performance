#include <vector>
#include <mm_malloc.h>
#include <cassert>
using namespace std;

// 284. Peeking Iterator

/*
 * Below is the interface for Iterator, which is already defined for you.
 * **DO NOT** modify the interface for Iterator.
 */
class Iterator
{
private:
    int cursor{-1};
    int end{0};
    vector<int> dup;

public:
    struct Data
    {
    };
    Data *data;

    Iterator(const vector<int> &nums) : dup(nums)
    {
        end = nums.size() - 1;
    };
    virtual ~Iterator(){};
    Iterator(const Iterator &iter) = default;
    // Returns the next element in the iteration.
    int next()
    {
        cursor++;
        if (cursor > end)
            cursor = end;
        return dup[cursor];
    };
    // Returns true if the iteration has more elements.
    bool hasNext() const
    {
        return cursor < end;
    };
};

class PeekingIterator : public Iterator
{
public:
    PeekingIterator(const vector<int> &nums) : Iterator(nums)
    {
        // Initialize any member here.
        // **DO NOT** save a copy of nums and manipulate it directly.
        // You should only use the Iterator interface methods.
    }

    // Returns the next element in the iteration without advancing the iterator.
    int peek()
    {
        return Iterator(*this).next();
    }

    // hasNext() and next() should behave the same as in the Iterator interface.
    // Override them if needed.
    int next()
    {
        return Iterator::next();
    }

    bool hasNext() const
    {
        return Iterator::hasNext();
    }
};

// 100%
void testPeekingIterator()
{
    vector<int> arr{1, 2, 3};
    PeekingIterator iter(arr);
    assert(iter.next() == 1);
    assert(iter.peek() == 2);
    assert(iter.next() == 2);
    assert(iter.peek() == 3);
    assert(iter.next() == 3);
    assert(!iter.hasNext());
}

int main(int argc, char const *argv[])
{

    return 0;
}
