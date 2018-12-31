#include "sort.h"

int INPUT_SIZE = 10;

template <class T>
int getArrayLen(T &array)
{
    return sizeof(array) / sizeof(array[0]);
}

void Sort::printInput(int input[])
{
    for (int i = 0; i < INPUT_SIZE; i++)
    {
        cout << input[i] << " ";
    }
    cout << endl;
}

void Sort::mergeSort(int input[], int size)
{
    if (size == 1)
        return;
    mergeSort(input, size / 2);
    mergeSort(input + size / 2, size - size / 2);
    combine(input, size / 2, size);
}

void Sort::combine(int input[], int split, int size)
{
    //    cout<<"split: "<< split <<" size "<<size<<endl;
    for (int i = split; i < size; i++)
    {
        int key = input[i];
        int j = i - 1;
        for (; j >= 0 && key < input[j]; j--)
        {
            input[j + 1] = input[j];
        }
        input[j + 1] = key;
    }
}

void Sort::quickSort(int input[], int start, int end)
{
    if (start >= end)
        return;
    // cout << "start: " << start << " end: " << end << endl;
    int p = partition(input, start, end);
    // cout << " p: " << p << endl;
    quickSort(input, start, p - 1);
    quickSort(input, p + 1, end);
}

int Sort::partition(int input[], int start, int end)
{
    int i = start;
    int j = start;
    int pivot = input[end];
    int tmp;
    for (; j < end; j++)
    {
        if (input[j] <= pivot)
        {
            exchange(input, i, j);
            i++;
        }
    }
    exchange(input, i, end);
    printInput(input);
    return i;
}

void Sort::exchange(int input[], int i, int j)
{
    int tmp = input[i];
    input[i] = input[j];
    input[j] = tmp;
}

void InsertSort::doSort(int input[])
{
    cout << "original array: ";
    printInput(input);
    for (int i = 1; i < INPUT_SIZE; i++)
    {
        int key = input[i];
        int j = i - 1;
        for (; j >= 0 && key < input[j]; j--)
        {
            input[j + 1] = input[j];
        }
        input[j + 1] = key;
    }
    cout << "sorted array: ";
    printInput(input);
}

int main(int arc, const char *argv[])
{
    int input[INPUT_SIZE];
    for (int i = 0; i < INPUT_SIZE; i++)
    {
        input[i] = rand() % 11;
    }
    Sort sort;
    sort.printInput(input);

    // InsertSort is;
    // is.doSort(input);
    // sort.mergeSort(input, INPUT_SIZE);
    sort.quickSort(input, 0, INPUT_SIZE - 1);
    sort.printInput(input);
}