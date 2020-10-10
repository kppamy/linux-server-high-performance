#include "common.h"
using namespace std;

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
        int sz = heap.size();
        int i = 0;
        while (i < sz - 1)
        {
            int left = 2 * i + 1;
            left = (left < sz - 1) ? left : sz - 1;
            int right = 2 * i + 2;
            right = (right < sz - 1) ? right : sz - 1;
            int mini = (heap[left] > heap[right]) ? right : left;
            swap(i, mini);
            i = mini;
        }
        heap.resize(sz - 1);
    }

    void swap(int i, int j)
    {
        int tmp = heap[i];
        heap[i] = heap[j];
        heap[j] = tmp;
    }

    int add(int val)
    {
        cout<<"add: "<<val<<endl;
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
    vector<int> nums1 = {-10, 1, 3, 1, 4, 10, 3, 9, 4, 5, 1};
    kthLargest = new KthLargest(7, nums1);
    vector<int> elements = {3, 2, 3, 1, 2, 4, 5, 5, 6, 7, 7, 8, 2, 3, 1, 1, 1, 10, 11, 5, 6, 2, 4, 7, 8, 5, 6};
    for (int val : elements)
    {
        kthLargest->add(val);
    }
}

int main(int argc, char const *argv[])
{
    testKthLargest();
    return 0;
}
