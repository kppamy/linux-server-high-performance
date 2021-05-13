#include <memory>
using namespace std;
class Rval
{
private:
    int val=1;
};



Rval testReturn()
{
   Rval val;
   return val;
}

int main()
{
    Rval val =testReturn();
    Rval val2 = move(val);
    return 0;
}