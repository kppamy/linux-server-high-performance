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
    vector<int>::reverse_iterator out{vec1.rbegin()};
    vector<int>::reverse_iterator ri1{vec1.begin() + m};
    vector<int>::reverse_iterator ri2{vec2.rbegin()};
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
        swap(arr[j], arr[index_min]);
        if (j == index_max)
        {
            int new_max = index_min;
            swap(arr[size - j - 1], arr[new_max]);
        }
        else
        {
            swap(arr[size - j - 1], arr[index_max]);
        }

        max = INT_MIN, min = INT_MAX;
        index_max = -1;
        index_min = -1;
        ++j;
        printVector(arr);
    }
}

void split(vector<int> &arr, int start, int end)
{
    int j = start;
    int i = j + 1;
    int key = arr[start];
    for (; i <= end; ++i)
    {
        if (arr[i] < key)
        {
            swap(arr[i], arr[j]);
            j++;
        }
    }
    if (end - start <= 1)
    {
        return;
    }
    split(arr, 0, j);
    split(arr, j + 1, end);
}

void quickSort(vector<int> &arr, int size)
{
    split(arr, 0, size - 1);
}

#include <map>
#include <algorithm>

// 1356. Sort Integers by The Number of 1 Bits
// Runtime: 32 ms, faster than 21.36% of C++ online submissions for Sort Integers by The Number of 1 Bits.
// Memory Usage: 13.8 MB, less than 5.05% of C++ online submissions for Sort Integers by The Number of 1 Bits
vector<int> sortByBits(vector<int> &arr)
{
    int len = arr.size();
    if (len <= 1)
    {
        return arr;
    }
    map<int, vector<int>> counter;
    vector<int> items;
    for (int val : arr)
    {
        int left = val;
        int bit = -1;
        int cnt = 0;
        while (left > 0)
        {
            bit = left % 2;
            if (bit)
                cnt++;
            left = left / 2;
        }
        items = counter[cnt];
        items.push_back(val);
        counter[cnt] = items;
    }
    // cout<<"after counter bits"<<endl;
    // for(auto &&itr:counter){
    //     cout<<itr.first<<": ";
    //     printVector(itr.second);
    // }
    // cout<<"after counter bits"<<endl;

    vector<int> out(len, -1);
    int pos = 0;
    for (int i = 0; i < counter.size(); ++i)
    {
        items = counter[i];
        sort(items.begin(), items.end());
        for (int val : items)
        {
            out[pos++] = val;
        }
    }
    return out;
}

vector<vector<int>> generater1DCases()
{
    return {
        {0, 1, 2, 3, 4, 5, 6, 7, 8},
        {1024, 512, 256, 128, 64, 32, 16, 8, 4, 2, 1},
        {10000, 10000},
        {2, 3, 5, 7, 11, 13, 17, 19},
        {10, 100, 1000, 10000}};
}

void testSortBit()
{
    vector<vector<int>> cases = generater1DCases();
    for (auto &&item : cases)
    {
        printVector(item);
        vector<int> res = sortByBits(item);
        printVector(res);
    }
}

void oldTests()
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
    // cocktailSort(arr, 10);
    quickSort(arr, 10);

    printVector(arr);

    int end = clock();
    double elaps = (static_cast<float>(end - start)) / CLOCKS_PER_SEC;
    cout << "elaps: " << elaps * 1000 << " ms" << endl;
}

#include <map>
#include <algorithm>
// 350. Intersection of Two Arrays II
// Runtime: 12 ms, faster than 66.25% of C++ online submissions for Intersection of Two Arrays II.
// Memory Usage: 10.4 MB, less than 64.37% of C++ online submissions for Intersection of Two Arrays II.
vector<int> intersect(vector<int> &nums1, vector<int> &nums2)
{
    int len1 = nums1.size();
    int len2 = nums2.size();
    if (len1 * len2 == 0)
    {
        return {};
    }
    sort(nums1.begin(), nums1.end());
    sort(nums2.begin(), nums2.end());
    int i = 0, j = 0;
    vector<int> out;
    while (i < len1 && j < len2)
    {
        if (nums1[i] == nums2[j])
        {
            out.push_back(nums1[i]);
            i++;
            j++;
        }
        else if (nums1[i] < nums2[j])
        {
            i++;
        }
        else
        {
            j++;
        }
    }
    return out;
}

// 350. Intersection of Two Arrays II
// Runtime: 16 ms, faster than 30.45% of C++ online submissions for Intersection of Two Arrays II.
// Memory Usage: 10.8 MB, less than 43.01% of C++ online submissions for Intersection of Two Arrays II.
vector<int> intersectHash(vector<int> &nums1, vector<int> &nums2)
{
    map<int, int> counter;
    for (int item : nums1)
    {
        counter[item]++;
    }
    sort(nums2.begin(), nums2.end());
    vector<int> out = {};
    for (int item : nums2)
    {
        if (counter.find(item) != counter.end() && counter[item] > 0)
        {
            counter[item]--;
            out.push_back(item);
        }
    }
    return out;
}

void testintersectII()
{
    my2DCases cases = {
        {{1, 2, 2, 1}, {2, 2}},
        {{}, {}},
        {{4, 9, 5}, {9, 4, 9, 8, 4}},

    };
    for (auto &&item : cases)
    {
        printVector(item[0]);
        printVector(item[1]);
        auto out = intersect(item[0], item[1]);
        cout << "result: " << endl;
        printVector(out);
    }
}

// 922. Sort Array By Parity II
// Runtime: 44 ms, faster than 71.38% of C++ online submissions for Sort Array By Parity II.
// Memory Usage: 21.5 MB, less than 70.37% of C++ online submissions for Sort Array By Parity II.
vector<int> sortArrayByParityII(vector<int> &A)
{
    int len = A.size();
    if (len == 0)
    {
        return {};
    }
    vector<int> out(len, 0);
    int odd = 1, even = 0;
    for (int i = 0; i < A.size(); i++)
    {
        if (A[i] % 2)
        {
            out[odd] = A[i];
            odd += 2;
        }
        else
        {
            out[even] = A[i];
            even += 2;
        }
    }
    return out;
}

void testsortArrayByParityII(){
    my2arr cases={
        {0,1},
        {1,0},
        {4,2,5,7},
        {3,2,5,4},
        };
    for(auto&& item:cases){
        printVector(item);
        auto res=sortArrayByParityII(item);
        printf("sorted:\n");
        printVector(res);
    }
}

int main(int arc, const char *argv[])
{
    // testSortBit();
    // testintersectII();
    testsortArrayByParityII();
}