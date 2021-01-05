#include<string>
#include<iostream>
using namespace std;

void test(string&& rv){
	string lc=move(rv);
    cout<<"address of local rvalue: "<<&lc<<" "<<lc<<endl;
	
}

string gs="cococco";
const string gcs="cococcocc";


class Rvtest
{
public:
    int i = 0;
    Rvtest operator+(const Rvtest &second)
    {
        Rvtest tmp;
        tmp.i = second.i + this->i;
        return std::move(tmp);
    }
};

Rvtest &&testRv(Rvtest &&rv)
{
    std::cout << "before return " << rv.i << " " << &rv.i << std::endl;
    Rvtest &&r = std::move(rv);
    std::cout << "return " << rv.i << " " << &rv.i << std::endl;
    std::cout << "return " << r.i << " " << &r.i << std::endl;
    return std::move(rv);
}

void testRvalue()
{
    Rvtest r1;
    r1.i = 1;
    Rvtest r2;
    r2.i = 2;
    Rvtest &&r3 = testRv(r1 + r2);
    std::cout << "after return " << r3.i << " " << &r3.i << std::endl;
}

int main() {
    cout<<"address of global string: "<<&gs<<" "<<gs<<endl;
    cout<<"address of global const string: "<<&gcs<<" "<<gcs<<endl;

    int* arr=new int[2];
    cout<<"new array address:     "<<arr<<endl;

    std::string lv="sdjfdk";
    test(lv+lv);

    const string cs="caycay";  
    cout<<"address of local const string: "<<&cs<<" "<<cs<<endl;

    cout<<"address of lvalue: "<<&lv<<" "<<lv<<endl;
    std::string lv2=lv+lv;
    cout<<"address of lvalue2: "<<&lv2<<" "<<lv2<<endl;
    std::string&& rv="sdjfdk";
    string&& rv2=lv+lv;
    cout<<"address of rvalue: "<<&rv<<" "<<rv<<endl;
    cout<<"address of rvalue2: "<<&rv2<<" "<<rv2<<endl;
    cout<<"address of function :%p "<<test<<endl;

    testRvalue();

    getchar();
    return 0;
}
