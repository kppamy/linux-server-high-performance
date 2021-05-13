#include<vector>
#include<list>

template<class T>
class Mallocator{
};

template<class T>
using mlist = std::list<T,Mallocator<T>>;

template<class T>
struct mlistOld
{
    typedef std::list<T,Mallocator<T>> type;
};


// item 9, modern
void usingOrTypedef(){
    mlist<int> ml;
    // mlistOld<int> old;
  
}

int main(int argc, char const *argv[])
{
    
    return 0;
}
