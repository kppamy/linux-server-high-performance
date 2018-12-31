#include <iostream>
using namespace std;

class Sort
{
public:
  Sort(){};
  virtual ~Sort() { cout << "i am In Sort" << endl; };
  virtual void doSort(int input[]){};
  void mergeSort(int input[], int size);
  void combine(int input[], int split, int size);
  void quickSort(int input[], int start, int end);
  int partition(int input[],  int start, int end);
  void exchange(int input[],  int i, int j);

public:
  void printInput(int input[]);
};


class InsertSort : Sort
{
public:
  ~InsertSort() { cout << "i am InsertSort" << endl; };
  void doSort(int input[]);
};
