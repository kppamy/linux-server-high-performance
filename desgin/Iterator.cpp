#include <vector>
#include <mm_malloc.h>
#include <cassert>
#include <iostream>
using namespace std;
// design pattern

template <class T>
class AbstractAggregate;

template <class T>
class AbstractIterator
{
public:
    AbstractIterator() = default;
    AbstractIterator(const AbstractIterator &) = default;
    AbstractIterator(AbstractAggregate<T> agg){

    };
    virtual ~AbstractIterator() = default;
    virtual T next(){};
    virtual bool hasnext(){};
};

template <class T>
class AbstractAggregate
{
public:
    virtual AbstractIterator<T> *createIterator(){};
    virtual ~AbstractAggregate(){};
};

template <class T>
class ConcreteIterator;

template <class T>
class ConcreteAggre : public AbstractAggregate<T>
{
public:
    ConcreteAggre(T *val) : data(val) {}
    AbstractIterator<T> *createIterator()
    {
        return new ConcreteIterator<T>(*this);
    }
    T *getData()
    {
        return data;
    }

private:
    T *data{nullptr};
};

template <class T>
class ConcreteIterator : public AbstractIterator<T>
{
public:
    ConcreteIterator() = delete;
    ConcreteIterator(const ConcreteIterator &) = default;
    ConcreteIterator(ConcreteAggre<T> agg)
    {
        // copy base::data --> cpdata
        cpdata = agg.getData();
    }

    T next()
    {
        std::cout << "ConcreteIterator next" << std::endl;
        return *cpdata;
    }

private:
    T *cpdata{nullptr};
};

void testIteratorPattern()
{
    vector<int> da{1, 2};
    int a = 1;
    ConcreteAggre<int> ca(&a);
    AbstractIterator<int> *itr(ca.createIterator());
    cout << itr->next() << endl;
}

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

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 */
class NestedInteger
{
public:
    NestedInteger() = default;
    NestedInteger(int val) : pod(val) {}
    NestedInteger(vector<int> &arr)
    {
        flag = false;
        std::copy(arr.begin(), arr.end(), nestedList.begin());
    }

    NestedInteger(vector<NestedInteger> &nlist)
    {
        flag = false;
        nestedList = nlist;
    }

    NestedInteger(std::initializer_list<int> da)
    {
        flag = false;
        for (auto &&item : da)
        {
            nestedList.push_back(NestedInteger(item));
        }
    }

    // Return true if this NestedInteger holds a single integer, rather than a nested list.
    bool isInteger() const
    {
        return flag;
    };

    // Return the single integer that this NestedInteger holds, if it holds a single integer
    // The result is undefined if this NestedInteger holds a nested list
    int getInteger() const
    {
        return pod;
    };

    // Return the nested list that this NestedInteger holds, if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer
    const vector<NestedInteger> &getList() const
    {
        return nestedList;
    };

private:
    bool flag{true};
    int pod{0};
    vector<NestedInteger> nestedList;
};

// 341. Flatten Nested List Iterator
#include <utility>
class NestedIterator
{
public:
    // faster ?
    NestedIterator(vector<NestedInteger> &&nestedList)
    {
        vector<NestedInteger> da(std::move(nestedList));
        flatten(da);
        end = flattenedList.size() - 1;
    }

    NestedIterator(vector<NestedInteger> &nestedList)
    {
        vector<NestedInteger> da(std::move(nestedList));
        flatten(nestedList);
        end = flattenedList.size() - 1;
    }

    void flatten(const vector<NestedInteger> &da)
    {
        for (auto &&i : da)
        {
            if (i.isInteger())
            {
                flattenedList.push_back(i);
            }
            else
            {
                flatten(i.getList());
            }
        }
    }

    int next() noexcept
    {
        cursor++;
        return flattenedList[cursor].getInteger();
    }

    bool hasNext() noexcept
    {
        return cursor < end;
    }

private:
    int cursor{-1};
    int end{-1};
    vector<NestedInteger> flattenedList;
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * 
 * while (i.hasNext()) cout << i.next();
 */

#include <set>
void flattenNestedListIterator()
{
    // [[1,1],2,[1,1]]
    NestedInteger i1({1, 1});
    NestedInteger i2(2);
    NestedInteger i3{1, 1};
    vector<NestedInteger> nestedList{i1, i2, i3};

    // [1,[4,[6]]]
    NestedInteger s1(1);
    NestedInteger s2(4);
    NestedInteger s3{6};
    vector<NestedInteger> s4{s2, s3};
    vector<NestedInteger> nestedList2{s1, s4};

    // [1,[4,[6,[1]]]]
    NestedInteger t1(1);
    NestedInteger t2(4);
    NestedInteger t31(6);
    NestedInteger t32{1};
    vector<NestedInteger> t3{t31, t32};
    vector<NestedInteger> t4{t2, t3};
    vector<NestedInteger> nestedList3{t1, t4};

    vector<vector<NestedInteger>> cases{nestedList, nestedList2, nestedList3};
    for (auto &&cs : cases)
    {
        //NestedIterator i(std::move(cs));
        NestedIterator i(cs); //Runtime: 20 ms, faster than 79.65%.
        while (i.hasNext())
            cout << i.next() << " ";
        cout << endl;
    }
}

#include "../common.h"
int main(int argc, char const *argv[])
{
    // testIteratorPattern();
    timeit(flattenNestedListIterator);
    return 0;
}