#include <stdio.h>

struct Student
{

    int num;

    char name[7];

    short age;

    char sex;

} student1;

struct Student2
{
    char name[7];
} student2;

int main(int argc, char const *argv[])
{
    // cout << "sizeof long: " << sizeof(long) << endl;
    // cout << "address of student 1  " << &student1 << " sizeof student1 " << sizeof(student1) << endl;
    // cout << "address of student 2  " << &student2 << " sizeof student2 " << sizeof(student2) << endl;
    // cout << "align value of student2  " << alignof(student2) << endl;

    // ofstream File1("text.txt");
    // string d("20160314");
    // string y = d.substr(0, 4);
    // int k = d.find("2");
    // int i = d.find("3");
    // string m = d.substr(k + 2, i - k);
    // string dd = d.substr(i + 1, 2);
    // string n = dd + m + y;
    // File1 << n << endl;
    // File1.close();

    char a1[14] = "Hello, world!";
     int i = 3;
      printf("%d %d", ++i, ++i);

    return 0;
}
