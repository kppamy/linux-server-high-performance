#include <vector>
#include<mm_malloc.h>
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

public:
    struct Data{
    };
    Data *data;
 
    // char *data;
    Iterator(const vector<int> &nums)
    {
        // data = (Data *)&nums;
        data=(Data*)malloc(nums.size()*sizeof(int));
        data=std::copy(nums.begin(),nums.end(),data);
        // data = (char *)&nums;
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
        // int res=(*(data + cursor)).val[0];
        return 0;
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



template<typename blDataType>
class blRawIterator
{
public:

    using iterator_category = std::random_access_iterator_tag;
    using value_type = blDataType;
    using difference_type = std::ptrdiff_t;
    using pointer = blDataType*;
    using reference = blDataType&;

public:

    blRawIterator(blDataType* ptr = nullptr){m_ptr = ptr;}
    blRawIterator(const blRawIterator<blDataType>& rawIterator) = default;
    ~blRawIterator(){}

    blRawIterator<blDataType>&                  operator=(const blRawIterator<blDataType>& rawIterator) = default;
    blRawIterator<blDataType>&                  operator=(blDataType* ptr){m_ptr = ptr;return (*this);}

    operator                                    bool()const
    {
        if(m_ptr)
            return true;
        else
            return false;
    }

    bool                                        operator==(const blRawIterator<blDataType>& rawIterator)const{return (m_ptr == rawIterator.getConstPtr());}
    bool                                        operator!=(const blRawIterator<blDataType>& rawIterator)const{return (m_ptr != rawIterator.getConstPtr());}

    blRawIterator<blDataType>&                  operator+=(const difference_type& movement){m_ptr += movement;return (*this);}
    blRawIterator<blDataType>&                  operator-=(const difference_type& movement){m_ptr -= movement;return (*this);}
    blRawIterator<blDataType>&                  operator++(){++m_ptr;return (*this);}
    blRawIterator<blDataType>&                  operator--(){--m_ptr;return (*this);}
    blRawIterator<blDataType>                   operator++(int){auto temp(*this);++m_ptr;return temp;}
    blRawIterator<blDataType>                   operator--(int){auto temp(*this);--m_ptr;return temp;}
    blRawIterator<blDataType>                   operator+(const difference_type& movement){auto oldPtr = m_ptr;m_ptr+=movement;auto temp(*this);m_ptr = oldPtr;return temp;}
    blRawIterator<blDataType>                   operator-(const difference_type& movement){auto oldPtr = m_ptr;m_ptr-=movement;auto temp(*this);m_ptr = oldPtr;return temp;}

    difference_type                             operator-(const blRawIterator<blDataType>& rawIterator){return std::distance(rawIterator.getPtr(),this->getPtr());}

    blDataType&                                 operator*(){return *m_ptr;}
    const blDataType&                           operator*()const{return *m_ptr;}
    blDataType*                                 operator->(){return m_ptr;}

    blDataType*                                 getPtr()const{return m_ptr;}
    const blDataType*                           getConstPtr()const{return m_ptr;}

protected:

    blDataType*                                 m_ptr;
};


template<typename blDataType>
class blRawReverseIterator : public blRawIterator<blDataType>
{
public:

    blRawReverseIterator(blDataType* ptr = nullptr):blRawIterator<blDataType>(ptr){}
    blRawReverseIterator(const blRawIterator<blDataType>& rawIterator){this->m_ptr = rawIterator.getPtr();}
    blRawReverseIterator(const blRawReverseIterator<blDataType>& rawReverseIterator) = default;
    ~blRawReverseIterator(){}

    blRawReverseIterator<blDataType>&           operator=(const blRawReverseIterator<blDataType>& rawReverseIterator) = default;
    blRawReverseIterator<blDataType>&           operator=(const blRawIterator<blDataType>& rawIterator){this->m_ptr = rawIterator.getPtr();return (*this);}
    blRawReverseIterator<blDataType>&           operator=(blDataType* ptr){this->setPtr(ptr);return (*this);}

    blRawReverseIterator<blDataType>&           operator+=(const difference_type& movement){this->m_ptr -= movement;return (*this);}
    blRawReverseIterator<blDataType>&           operator-=(const difference_type& movement){this->m_ptr += movement;return (*this);}
    blRawReverseIterator<blDataType>&           operator++(){--this->m_ptr;return (*this);}
    blRawReverseIterator<blDataType>&           operator--(){++this->m_ptr;return (*this);}
    blRawReverseIterator<blDataType>            operator++(int){auto temp(*this);--this->m_ptr;return temp;}
    blRawReverseIterator<blDataType>            operator--(int){auto temp(*this);++this->m_ptr;return temp;}
    blRawReverseIterator<blDataType>            operator+(const int& movement){auto oldPtr = this->m_ptr;this->m_ptr-=movement;auto temp(*this);this->m_ptr = oldPtr;return temp;}
    blRawReverseIterator<blDataType>            operator-(const int& movement){auto oldPtr = this->m_ptr;this->m_ptr+=movement;auto temp(*this);this->m_ptr = oldPtr;return temp;}

    difference_type                             operator-(const blRawReverseIterator<blDataType>& rawReverseIterator){return std::distance(this->getPtr(),rawReverseIterator.getPtr());}

    blRawIterator<blDataType>                   base(){blRawIterator<blDataType> forwardIterator(this->m_ptr); ++forwardIterator; return forwardIterator;}
};

template<typename blDataType>
class blCustomContainer
{
public: // The typedefs

    typedef blRawIterator<blDataType>              iterator;
    typedef blRawIterator<const blDataType>        const_iterator;

    typedef blRawReverseIterator<blDataType>       reverse_iterator;
    typedef blRawReverseIterator<const blDataType> const_reverse_iterator;            

public:  // The begin/end functions

    iterator                                       begin(){return iterator(&m_data[0]);}
    iterator                                       end(){return iterator(&m_data[m_size]);}

    const_iterator                                 cbegin(){return const_iterator(&m_data[0]);}
    const_iterator                                 cend(){return const_iterator(&m_data[m_size]);}

    reverse_iterator                               rbegin(){return reverse_iterator(&m_data[m_size - 1]);}
    reverse_iterator                               rend(){return reverse_iterator(&m_data[-1]);}

    const_reverse_iterator                         crbegin(){return const_reverse_iterator(&m_data[m_size - 1]);}
    const_reverse_iterator                         crend(){return const_reverse_iterator(&m_data[-1]);}
    // This is the pointer to the
    // beginning of the data
    // This allows the container
    // to either "view" data owned
    // by other containers or to
    // own its own data
    // You would implement a "create"
    // method for owning the data
    // and a "wrap" method for viewing
    // data owned by other containers

    blDataType*                                    m_data;
    size_t                                   m_size;
};

#include <cassert>
int main(int argc, char const *argv[])
{
    vector<int> arr{1, 2, 3};
    PeekingIterator iter(arr);
    assert(iter.next() == 1);
    assert(iter.peek() == 2);
    assert(iter.next() == 2);
    assert(iter.next() == 3);
    assert(!iter.hasNext());
    return 0;
}
