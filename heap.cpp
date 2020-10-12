#include "common.h"
using namespace std;

// 703. Kth Largest Element in a Stream
// Runtime: 48 ms, faster than 99.74% of C++ online submissions for Kth Largest Element in a Stream.
// Memory Usage: 20.1 MB, less than 8.70% of C++ online submissions for Kth Largest Element in a Stream.
class KthLargest
{
public:
    KthLargest(int k, vector<int> &nums)
    {
        kth = k;
        for (int val : nums)
        {
            add(val);
        }
    }

    void pop()
    {
        int last = heap.size() - 1;
        int i = 0;
        swap(last, i);
        while (i < last)
        {
            int left = 2 * i + 1;
            if (left >= last)
                break;
            int right = 2 * i + 2;
            right = (right < last) ? right : left;
            int mini = (heap[left] > heap[right]) ? right : left;
            if (heap[i] > heap[mini])
            {
                swap(i, mini);
                i = mini;
            }
            else
            {
                break;
            }
        }
        heap.pop_back();
    }

    void swap(int i, int j)
    {
        int tmp = heap[i];
        heap[i] = heap[j];
        heap[j] = tmp;
    }

    int add(int val)
    {
        cout << "add: " << val << endl;
        if (heap.size() == kth && val <= heap[0])
        {
            cout << "ignore minimum on heap full " << val << endl;
            return heap[0];
        }
        heap.push_back(val);
        int last = heap.size() - 1;
        while (last > 0)
        {
            int parent = (last - 1) / 2;
            if (heap[last] < heap[parent])
            {
                swap(last, parent);
                last = parent;
            }
            else
            {
                break;
            }
        }
        if (heap.size() > kth)
            pop();
        if (heap.size() == kth)
        {
            cout << "heap: " << endl;
            cout << *this;
        }
        return heap[0];
    }

    friend ostream &operator<<(ostream &os, const KthLargest &obj)
    {
        vector<int> tmp = obj.heap;
        int height = floor(log2(tmp.size() + 1));
        for (int i = 1; i <= height; i++)
        {
            int nodes = pow(2, i - 1);
            int start = nodes - 1;
            for (int j = start; j < start + nodes; j++)
            {
                os << tmp[j] << " ";
            }
            os << endl;
        }
        return os;
    }

private:
    vector<int> heap;
    int kth;
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */

void testKthLargest()
{
    vector<int> nums = {4, 5, 8, 2};
    KthLargest *kthLargest = new KthLargest(3, nums);
    kthLargest->add(3);  // return 4
    kthLargest->add(5);  // return 5
    kthLargest->add(10); // return 5
    kthLargest->add(9);  // return 8
    kthLargest->add(4);  // return 8

    cout << "+++++++++++++++++++++++++++++++++++++++" << endl;
    // heap:
    // 5
    // 6 9
    // 7 7 10 5
    // add: 8
    vector<int> nums0 = {5, 6, 9, 7, 7, 10, 5};
    kthLargest = new KthLargest(7, nums0);
    vector<int> elements = {8};
    for (int val : elements)
    {
        kthLargest->add(val);
    }

    cout << "+++++++++++++++++++++++++++++++++++++++" << endl;
    vector<int> nums1 = {-10, 1, 3, 1, 4, 10, 3, 9, 4, 5, 1};
    kthLargest = new KthLargest(7, nums1);
    vector<int> elements0 = {3, 2, 3, 1, 2, 4, 5, 5, 6, 7, 7, 8, 2, 3, 1, 1, 1, 10, 11, 5, 6, 2, 4, 7, 8, 5, 6};
    for (int val : elements0)
    {
        kthLargest->add(val);
    }
}

#include <queue>
// 215. Kth Largest Element in an Array
// Runtime: 28 ms, faster than 47.97% of C++ online submissions for Kth Largest Element in an Array.
// Memory Usage: 10.4 MB, less than 12.36% of C++ online submissions for Kth Largest Element in an Array.
int findKthLargest(vector<int> &nums, int k)
{
    priority_queue<int, vector<int>, std::greater<int>> heap(nums.begin(), nums.end());
    while (heap.size() > k)
    {
        heap.pop();
    }
    return heap.top();
}

void testfindKthLargest()
{
    vector<int> arr = {3, 2, 1, 5, 6, 4};
    int k = 2;
    printVector(arr);
    cout << k << " largest: " << findKthLargest(arr, k) << endl;

    arr = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    k = 4;
    printVector(arr);
    cout << k << " largest: " << findKthLargest(arr, k) << endl;
}

// 1046. Last Stone Weight
// Runtime: 4 ms, faster than 65.17% of C++ online submissions for Last Stone Weight.
// Memory Usage: 7.8 MB, less than 99.26% of C++ online submissions for Last Stone Weight.
int lastStoneWeight(vector<int> &stones)
{
    priority_queue<int> heap(stones.begin(), stones.end());
    while (heap.size() > 1)
    {
        int largest = heap.top();
        heap.pop();
        int second = heap.top();
        heap.pop();
        if (largest - second > 0)
        {
            heap.push(largest - second);
        }
    }
    if (heap.empty())
        return 0;
    return heap.top();
}

int main(int argc, char const *argv[])
{
    // testKthLargest();
    // testArray(lastStoneWeight, "lastStoneWeight", generateArrayInput, printInt);
    testfindKthLargest();
    return 0;
}
