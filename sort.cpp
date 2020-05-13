#include "sort.h"
#include "common.h"
int INPUT_SIZE = 10;

template <class T>
int getArrayLen(T &array)
{
    return sizeof(array) / sizeof(array[0]);
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
    printInput(input, INPUT_SIZE);
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
    printInput(input, INPUT_SIZE);
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
    printInput(input, INPUT_SIZE);
}

// vec1 size enough to take both vector members
void Sort::mergeSortedArray(vector<int> &vec1, int m, vector<int> &vec2, int n)
{
    int size1 = vec1.size();
    int size2 = vec2.size();
    vector<int>::reverse_iterator out{vec1.rbegin()};
    vector<int>::reverse_iterator ri1{vec1.begin() + m};
    vector<int>::reverse_iterator ri2{vec2.rbegin()};
    int current;
    while (ri1 != vec1.rend() && ri2 != vec2.rend())
    {
        *out++ = (*ri1 >= *ri2) ? *ri1++ : *ri2++;
    }
    while (ri1 != vec1.rend())
    {
        *out++ = *(ri1++);
    }
    while (ri2 != vec2.rend())
    {
        *out++ = *(ri2++);
    }
    for (int i = 0; i < m + n; i++)
    {
        cout << vec1[i] << " ";
    }
    cout << endl;
    // printVector;(vec1);
}

void bunbleSort(vector<int> &arr, int size)
{
    int tmp;
    while (size >= 1)
    {
        for (int i = 0; i < size; ++i)
        {
            if (arr[i] > arr[i + 1])
            {
                tmp = arr[i + 1];
                arr[i + 1] = arr[i];
                arr[i] = tmp;
            }
        }
        // printVector(arr);
        size--;
    }
}

void cocktailSort(vector<int> &arr, int size)
{
    int max = INT_MIN, min = INT_MAX;
    int index_max, index_min = -1;
    int j = 0;
    while (j < size / 2)
    {
        cout<<j<<endl;
        int i = j;
        for (; i < size - j; ++i)
        {
            if (arr[i] > max)
            {
                max = arr[i];
                index_max = i;
            }
            else if (arr[i] < min)
            {
                min = arr[i];
                index_min = i;
            }
        }
        swap(arr[i], arr[index_min]);
        swap(arr[size - i - 1], arr[index_max]);
        max = INT_MIN, min = INT_MAX;
        index_max = -1;
        index_min = -1;
        ++j;
        printVector(arr);
    }
}

int main(int arc, const char *argv[])
{

    Sort sort;
    // int input[INPUT_SIZE];
    // for (int i = 0; i < INPUT_SIZE; i++)
    // {
    //     input[i] = rand() % 11;
    // }
    // sort.printInput(input);

    // InsertSort is;
    // is.doSort(input);
    // sort.mergeSort(input, INPUT_SIZE);
    // sort.quickSort(input, 0, INPUT_SIZE - 1);
    // sort.printInput(input);

    // vector<int> vec1{1, 4, 0, 0, 0,0};
    // vector<int> vec2{2, 3, 6};
    // sort.mergeSortedArray(vec1, 2, vec2, 3);

    vector<int> arr = generateArray(10, 10);
    printVector(arr);

    int start = clock();
    // bunbleSort(arr, 10);
    cocktailSort(arr, 10);
    int end = clock();
    double elaps = (static_cast<float>(end - start)) / CLOCKS_PER_SEC;
    cout << "elaps: " << elaps * 1000 << " ms" << endl;
}