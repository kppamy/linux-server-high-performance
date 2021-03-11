
#ifndef COMMON_H
#define COMMON_H
#include <iostream>
#include <vector>
#include <time.h>
#include <limits.h>
#include <random>
#include "Timer.h"
#include "algo/LinkedList.h"

typedef std::vector<std::vector<int>> my2arr;
typedef std::vector<my2arr> my2DCases;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int val, TreeNode *l, TreeNode *r) : val(0), left(l), right(r) {}
};

#include<chrono>
template<typename F, typename ... Args>
double timeit(F func, Args&& ... arg)
{
    Timer t;
    t.start();
    func(arg...);
    t.stop();
    std::cout << "time cost: " << t.miniSeconds() << " ms" << std::endl;
    return t.miniSeconds();
}


void print(int n){
    std::cout<<" "<<n<<" "<<std::endl;
}

void print(bool n){
    std::cout<<" "<<n<<" "<<std::endl;
}

template<typename T>
void print(std::vector<T> &input)
{
    for(auto&& val:input){
        std::cout<<val<<" ";
    }
    std::cout << std::endl;
}

template<typename T>
void print(std::vector<std::vector<T>> &input)
{
    for(auto&& val:input){
        print(val);
    }
    std::cout << std::endl;
}



void printInt(int n){
    std::cout<<" "<<n<<" "<<std::endl;
}

template<typename T>
void printVector(std::vector<T> &input)
{
    for(auto&& val:input){
        std::cout<<val<<" ";
    }
    std::cout << std::endl;
}

template<typename T>
void printVector(std::vector<std::vector<T>> &input)
{
    for(auto&& val:input){
        printVector(val);
    }
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
            std::cout << input[i] << " ";
        }
        std::cout << std::endl;
    }
}


std::vector<int> generateArray(int num, int max)
{
    std::vector<int> arr(num);

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

template<typename F, typename I, typename P>
void format_test(F func, I inputf, P print){
 auto&& cases=inputf();
 for(auto&& item :cases){
     printVector(item);
     auto&& res=func(item);
     print(res);
 }
}


template<typename F, typename I>
void format_test(F func, I inputf){
 auto&& cases=inputf();
 for(auto&& item :cases){
     std::cout<<std::endl;
     std::cout<<"=====case===== "<<std::endl;
     printVector(item);
     auto&& res=func(item);
     std::cout<<"==result== "<<std::endl;
     print(res);
 }
}

my2arr generateArrayInput()
{
    return {
        {2,2},
        {2, 7, 4, 1, 8, 1 },
        {4, 3, 10, 9, 8},
        {4, 4, 7, 6, 7},
        {6}
        };
}

template<typename f, typename u, typename p>
void testArray(f fun, std::string name, u input=generateArrayInput, p print=printVector){
    my2arr&& cases=input();
    for(auto&& cs:cases){
        printVector(cs);
        std::cout<<name<<" :"<<std::endl;
        auto res=fun(cs);
        print(res);
        std::cout<<std::endl;
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
        Test(){std::cout << "Test constructor" << std::endl;}
        ~Test(){std::cout << "Test destructor" << std::endl;}
};

#include <regex>
std::vector<std::string> split(const std::string &input, const std::string &regex)
{
    // passing -1 as the submatch index parameter performs splitting
    std::regex re(regex);
    std::sregex_token_iterator
        first{input.begin(), input.end(), re, -1},
        last;
    return {first, last};
}

#endif