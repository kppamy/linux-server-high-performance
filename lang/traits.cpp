 #include<vector>
 #include<iostream>
// using namespace std;


// // when there is no need to return the inner type
// // use function template's parameters to deduct the value type of iterator
//  template<class I,class T>
//  void func2(I itr,T value){     
//  }

//  template<class I>
//  void func2_wrap(I itr){
//      func2(itr,*itr);
//  }


// // what if the return type is the value type of the iterator?
//  template <class I>
//  struct iterator_traits {
//      typedef typename I::value_type value_type;
//  };
 
//  template <class T>
//  struct iterator_traits<T*>{
//      typedef T value_type;
//  };
 
//  template <class I> 
// typename iterator_traits<I>::value_type
//  func(I ite) {
//      return *ite;
//  }
// int main(int argc, char const *argv[])
// {
//     /* code */
//     int i=4;
//     int* p=&i;
//     std::cout<<func(p)<<std::endl;

//     std::vector<int> arr{1,2};
//     std::cout<<func(arr.begin())<<std::endl;
//     return 0;
// }


#include <iostream>
using namespace std;

/*先定义一些tag*/
struct A {};
struct B : A{}; // 继承的好处就是，当函数需要参数为A，
                // 而你传入的参数为B的时候，可以往上一直找到适合的对象

/*假设有一个未知类*/
template <class AorB>
struct container {
    typedef AorB value_type;
};

/*特性萃取器*/
template <class container>
struct container_traits {
    typedef typename container::value_type value_type;
};

/*特性萃取器 —— 针对原生指针*/
template <class T>
struct container_traits<T*> {
    typedef T value_type;
};

/*特性萃取其 —— 针对指向常数*/
template <class T>
struct container_traits<const T*> {
    typedef const T value_type;
};


/*决定使用哪一个类型*/
// template <class container>
// inline typename container_traits<container>::value_type
// return_func(container) {
//     typedef typename container_traits<container>::value_type RT;
//         cout << "value_type func" << endl;
//     return RT();
// }

template <class container>
inline typename container_traits<container>::value_type
__func(container, A) {
    cout << "use A flag" << endl;
    return A();
}

template <class container>
inline typename container_traits<container>::value_type
__func(container, B) {
    cout << "use B flag" << endl;
    return B();
}

template <class container, class T>
T
__func(container, T) {
    cout << "use origin ptr" << endl;
    return T();
}

template <class container>
inline typename container_traits<container>::value_type
func(container u) {
    typedef typename container_traits<container>::value_type value_type;
    return __func(u, value_type());
}


int main() {
    container<B> b;
    container<A> a;
    //container<int> i;
    int value = 1;
    int *p = &value;

    A v1 = func(a);
    B v2 = func(b);
    int v3 = func(p);

    char ch = getchar();
}




template<typename T>
class RawIterator
{
public:

    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

public:

    RawIterator(T* ptr = nullptr){m_ptr = ptr;}
    RawIterator(const RawIterator<T>& rawIterator) = default;
    ~RawIterator(){}

    RawIterator<T>&                  operator=(const RawIterator<T>& rawIterator) = default;
    RawIterator<T>&                  operator=(T* ptr){m_ptr = ptr;return (*this);}

    operator                                    bool()const
    {
        if(m_ptr)
            return true;
        else
            return false;
    }

    bool                                        operator==(const RawIterator<T>& rawIterator)const{return (m_ptr == rawIterator.getConstPtr());}
    bool                                        operator!=(const RawIterator<T>& rawIterator)const{return (m_ptr != rawIterator.getConstPtr());}

    RawIterator<T>&                  operator+=(const difference_type& movement){m_ptr += movement;return (*this);}
    RawIterator<T>&                  operator-=(const difference_type& movement){m_ptr -= movement;return (*this);}
    RawIterator<T>&                  operator++(){++m_ptr;return (*this);}
    RawIterator<T>&                  operator--(){--m_ptr;return (*this);}
    RawIterator<T>                   operator++(int){auto temp(*this);++m_ptr;return temp;}
    RawIterator<T>                   operator--(int){auto temp(*this);--m_ptr;return temp;}
    RawIterator<T>                   operator+(const difference_type& movement){auto oldPtr = m_ptr;m_ptr+=movement;auto temp(*this);m_ptr = oldPtr;return temp;}
    RawIterator<T>                   operator-(const difference_type& movement){auto oldPtr = m_ptr;m_ptr-=movement;auto temp(*this);m_ptr = oldPtr;return temp;}

    difference_type                             operator-(const RawIterator<T>& rawIterator){return std::distance(rawIterator.getPtr(),this->getPtr());}

    T&                                 operator*(){return *m_ptr;}
    const T&                           operator*()const{return *m_ptr;}
    T*                                 operator->(){return m_ptr;}

    T*                                 getPtr()const{return m_ptr;}
    const T*                           getConstPtr()const{return m_ptr;}

protected:

    T*                                 m_ptr;
};


template<typename T>
class RawReverseIterator : public RawIterator<T>
{
public:

    RawReverseIterator(T* ptr = nullptr):RawIterator<T>(ptr){}
    RawReverseIterator(const RawIterator<T>& rawIterator){this->m_ptr = rawIterator.getPtr();}
    RawReverseIterator(const RawReverseIterator<T>& rawReverseIterator) = default;
    ~RawReverseIterator(){}

    RawReverseIterator<T>&           operator=(const RawReverseIterator<T>& rawReverseIterator) = default;
    RawReverseIterator<T>&           operator=(const RawIterator<T>& rawIterator){this->m_ptr = rawIterator.getPtr();return (*this);}
    RawReverseIterator<T>&           operator=(T* ptr){this->setPtr(ptr);return (*this);}

    RawReverseIterator<T>&           operator++(){--this->m_ptr;return (*this);}
    RawReverseIterator<T>&           operator--(){++this->m_ptr;return (*this);}
    RawReverseIterator<T>            operator++(int){auto temp(*this);--this->m_ptr;return temp;}
    RawReverseIterator<T>            operator--(int){auto temp(*this);++this->m_ptr;return temp;}
    RawReverseIterator<T>            operator+(const int& movement){auto oldPtr = this->m_ptr;this->m_ptr-=movement;auto temp(*this);this->m_ptr = oldPtr;return temp;}
    RawReverseIterator<T>            operator-(const int& movement){auto oldPtr = this->m_ptr;this->m_ptr+=movement;auto temp(*this);this->m_ptr = oldPtr;return temp;}


    RawIterator<T>                   base(){RawIterator<T> forwardIterator(this->m_ptr); ++forwardIterator; return forwardIterator;}
};

template<typename T>
class blCustomContainer
{
public: // The typedefs

    typedef RawIterator<T>              iterator;
    typedef RawIterator<const T>        const_iterator;

    typedef RawReverseIterator<T>       reverse_iterator;
    typedef RawReverseIterator<const T> const_reverse_iterator;            

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

    T*                                    m_data;
    size_t                                   m_size;
};




