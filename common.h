#include <iostream>
#include <vector>
#include <time.h>
#include <limits.h>
#include <random>
#include "Timer.h"

typedef vector<vector<int>> my2arr;
typedef vector<my2arr> my2DCases;


void timeit(std::function<void()> func)
{
    Timer t;
    t.start();
    func();
    t.stop();
    std::cout << "time cost: " << t.miniSeconds() << " ms" << endl;
}

void printInt(int n){
    cout<<" "<<n<<" ";
}

void printVector(std::vector<int> &input)
{

    for_each(input.begin(), input.end(), [](int i) {
        cout << i << " ";
    });
    cout << endl;
}

void print2Vector(std::vector<std::vector<int>> &input)
{

   for(auto&& item:input){
       printVector(item);
   }
}

void printInput(int input[], int len)
{
    {
        for (int i = 0; i < len; i++)
        {
            cout << input[i] << " ";
        }
        cout << endl;
    }
}


vector<int> generateArray(int num, int max)
{
    vector<int> arr(num);

    // C random generators
    // for(int i=0;i<=num;i++){
    //     arr[i]=(rand()%max);
    // }

    // C++ 11 random generations
    //  http://channel9.msdn.com/Events/GoingNative/2013/rand-Considered-Harmful
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(1.0, 10.0);

    for (int i = 0; i < num; ++i)
    {
        arr[i] = dist(mt);
    }
    return arr;
}

template<typename f, typename u, typename t>
void format_test(f func, u inputf, t print){
 auto&& cases=u();
 for(auto&& item :cases){
     func(item);
     print(item);
 }
}

template<typename f, typename u, typename p>
void testArray(f fun, string name, u input, p print){
    my2arr&& cases=input();
    for(auto&& cs:cases){
        printVector(cs);
        cout<<name<<" :"<<endl;
        auto res=fun(cs);
        print(res);
        cout<<endl;
    }
}


#include <iostream>
#include <string>
#include <map>

 
#define DECLARE_CLASS() \
    protected: \
        static ClassInfo ms_classinfo; \
    public:  \
        static Object* CreateObject();  
 
#define IMPLEMENT_CLASS(interface_name, class_name)            \
	ClassInfo class_name::ms_classinfo(interface_name,(ObjectConstructorFn)class_name::CreateObject);\
    Object* class_name::CreateObject() \
        { return new class_name;} 
 
class ClassInfo;
class Object;
typedef Object* (*ObjectConstructorFn)();
 
class Object  
{ 
protected:
    Object(){}
public:  
    virtual ~Object(){}
    static void Register(ClassInfo* ci);         
    static Object* CreateObject(std::string name);     
    static std::map<std::string, ClassInfo *> *classInfoMap;
};  
 
class ClassInfo  
{  
public:  
	ClassInfo(const std::string className, ObjectConstructorFn ctor);
	ClassInfo();
	Object *CreateObject()const;
 
public:  
	std::string m_className;
	ObjectConstructorFn m_objectConstructor;
}; 
 
std::map<std::string, ClassInfo *> *Object::classInfoMap = new std::map<std::string, ClassInfo*>();
 
void Object::Register(ClassInfo* ci)  
{   
	if (NULL != ci && classInfoMap->find(ci->m_className) == classInfoMap->end())
	{  
		classInfoMap->insert(std::map<std::string, ClassInfo*>::value_type(ci->m_className, ci)); 
	}  
}
 
Object* Object::CreateObject(std::string name)  
{
	std::map<std::string, ClassInfo*>::const_iterator iter = classInfoMap->find(name);  
	if (iter != classInfoMap->end())
	{
		return iter->second->CreateObject();
	}
	return NULL;  
}  
 
ClassInfo::ClassInfo(const std::string className, ObjectConstructorFn ctor):m_className(className), m_objectConstructor(ctor)  
{  
	Object::Register(this);
}
 
ClassInfo::ClassInfo()
{
}
 
Object *ClassInfo::CreateObject()const 
{ 
	return m_objectConstructor ? (*m_objectConstructor)() : 0; 
}
 
class Test:public Object
{
        DECLARE_CLASS()
public:
        Test(){cout << "Test constructor" << endl;}
        ~Test(){cout << "Test destructor" << endl;}
};
