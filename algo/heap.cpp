#include "../common.h"
#include <iostream>
using namespace std;

// 295. Find Median from Data Stream
//  100 ms, faster than 90.62%
// 46.9 MB, less than 61.39%
class MedianFinder
{
public:
    /** initialize your data structure here. */
    MedianFinder()
    {
    }

    void reblance()
    {
        int sz1 = fmax.size();
        int sz2 = smin.size();
        if (sz1 - sz2 > 1)
        {
            smin.push(fmax.top());
            fmax.pop();
        }
        else if (sz2 - sz1 > 1)
        {
            fmax.push(smin.top());
            smin.pop();
        }
    }
    void addNum(int num)
    {

        if (fmax.size() == 0)
        {
            fmax.push(num);
            return;
        }
        if (num > fmax.top())
        {
            smin.push(num);
        }
        else
        {
            fmax.push(num);
        }
        reblance();
    }

    double findMedian()
    {

        int sz1 = fmax.size(), sz2 = smin.size();
        if (sz1 == 0)
        {
            return 0;
        }
        if (sz1 == sz2)
        {
            return (fmax.top() + smin.top()) / 2.0;
        }
        else
        {
            if (sz1 > sz2)
                return fmax.top();
            return smin.top();
        }
    }

private:
    priority_queue<int> fmax;                                 // max heap in the first half
    priority_queue<int, vector<int>, std::greater<int>> smin; // min heap in the second half
};

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

// bellman-ford shortest path
// 787. Cheapest Flights Within K Stops
// Runtime: 280 ms, faster than 5.92% of C++ online submissions for Cheapest Flights Within K Stops.
// Memory Usage: 11.7 MB, less than 9.08% of C++ online submissions for Cheapest Flights Within K Stops.

int findCheapestPriceMy(int n, vector<vector<int>> &flights, int src, int dst, int K)
{
    vector<vector<int>> map(n, vector<int>(n, 0));
    vector<int> indegree(n, 0);
    for (auto &&val : flights)
    {
        map[val[0]][val[1]] = val[2];
        indegree[val[1]]++;
    }
    vector<int> paths(K + 1, INT_MAX);
    vector<vector<int>> cheapest(n, paths);
    queue<int> bfs;
    auto relax = [&](int u) {
        for (int v = 0; v < n; v++)
        {
            if (map[u][v] == 0)
                continue;
            if (v != src && indegree[v] > 0)
            {
                bfs.push(v);
                indegree[v]--;
            }
            if (u == src)
            {
                cheapest[v][0] = map[u][v];
                continue;
            }
            for (int i = 0; i < K; i++)
            {
                if (cheapest[u][i] == INT_MAX)
                    continue;
                if (cheapest[u][i] + map[u][v] < cheapest[v][i + 1])
                {
                    cheapest[v][i + 1] = cheapest[u][i] + map[u][v];
                }
            }
        }
    };

    bfs.push(src);
    while (!bfs.empty())
    {
        int nd = bfs.front();
        bfs.pop();
        relax(nd);
    }
    int mini = INT_MAX;
    for (int val : cheapest[dst])
    {
        if (val < mini)
        {
            mini = val;
        }
    }
    return (mini == INT_MAX) ? -1 : mini;
}

int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int K)
{
    vector<pair<int, int>> adjList[n];

    for (auto &flight : flights)
        adjList[flight[0]].emplace_back(flight[1], flight[2]);

    int minCost[n];
    for (auto &cost : minCost)
        cost = INT_MAX;

    queue<pair<int, int>> que;
    que.emplace(src, 0);
    int steps = 0, res = INT_MAX;

    while (!que.empty() && steps <= K + 1)
    {
        int size = que.size();
        while (size--)
        {
            auto [at, cost] = que.front();
            cout << "pop: " << at << " cost: " << cost << endl;
            que.pop();

            if (at == dst)
                res = min(res, cost);

            if (steps == K + 1)
                continue;

            for (auto &edge : adjList[at])
            {
                cout << at << " " << edge.first << " " << edge.second << endl;
                if (cost + edge.second < minCost[edge.first])
                {
                    minCost[edge.first] = cost + edge.second;
                    que.emplace(edge.first, cost + edge.second);
                    cout << "emplace: " << edge.first << " cost: " << cost + edge.second << endl;
                }
            }
        }
        steps++;
    }

    return res == INT_MAX ? -1 : res;
}

void testfindCheapestPrice()
{
    int n = 3, src = 0, dst = 2, k = 1;
    vector<vector<int>> edges = {{0, 1, 100}, {1, 2, 100}, {0, 2, 500}};
    cout << "from " << src << " to " << dst << " within " << k << " stops, cheapest: " << findCheapestPrice(n, edges, src, dst, k) << endl;
    k = 0;
    cout << "from " << src << " to " << dst << " within " << k << " stops, cheapest: " << findCheapestPrice(n, edges, src, dst, k) << endl;

    edges = {{0, 12, 28}, {5, 6, 39}, {8, 6, 59}, {13, 15, 7}, {13, 12, 38}, {10, 12, 35}, {15, 3, 23}, {7, 11, 26}, {9, 4, 65}, {10, 2, 38}, {4, 7, 7}, {14, 15, 31}, {2, 12, 44}, {8, 10, 34}, {13, 6, 29}, {5, 14, 89}, {11, 16, 13}, {7, 3, 46}, {10, 15, 19}, {12, 4, 58}, {13, 16, 11}, {16, 4, 76}, {2, 0, 12}, {15, 0, 22}, {16, 12, 13}, {7, 1, 29}, {7, 14, 100}, {16, 1, 14}, {9, 6, 74}, {11, 1, 73}, {2, 11, 60}, {10, 11, 85}, {2, 5, 49}, {3, 4, 17}, {4, 9, 77}, {16, 3, 47}, {15, 6, 78}, {14, 1, 90}, {10, 5, 95}, {1, 11, 30}, {11, 0, 37}, {10, 4, 86}, {0, 8, 57}, {6, 14, 68}, {16, 8, 3}, {13, 0, 65}, {2, 13, 6}, {5, 13, 5}, {8, 11, 31}, {6, 10, 20}, {6, 2, 33}, {9, 1, 3}, {14, 9, 58}, {12, 3, 19}, {11, 2, 74}, {12, 14, 48}, {16, 11, 100}, {3, 12, 38}, {12, 13, 77}, {10, 9, 99}, {15, 13, 98}, {15, 12, 71}, {1, 4, 28}, {7, 0, 83}, {3, 5, 100}, {8, 9, 14}, {15, 11, 57}, {3, 6, 65}, {1, 3, 45}, {14, 7, 74}, {2, 10, 39}, {4, 8, 73}, {13, 5, 77}, {10, 0, 43}, {12, 9, 92}, {8, 2, 26}, {1, 7, 7}, {9, 12, 10}, {13, 11, 64}, {8, 13, 80}, {6, 12, 74}, {9, 7, 35}, {0, 15, 48}, {3, 7, 87}, {16, 9, 42}, {5, 16, 64}, {4, 5, 65}, {15, 14, 70}, {12, 0, 13}, {16, 14, 52}, {3, 10, 80}, {14, 11, 85}, {15, 2, 77}, {4, 11, 19}, {2, 7, 49}, {10, 7, 78}, {14, 6, 84}, {13, 7, 50}, {11, 6, 75}, {5, 10, 46}, {13, 8, 43}, {9, 10, 49}, {7, 12, 64}, {0, 10, 76}, {5, 9, 77}, {8, 3, 28}, {11, 9, 28}, {12, 16, 87}, {12, 6, 24}, {9, 15, 94}, {5, 7, 77}, {4, 10, 18}, {7, 2, 11}, {9, 5, 41}};
    n = 17, src = 13, dst = 4, k = 13;
    cout << "from " << src << " to " << dst << " within " << k << " stops, cheapest: " << findCheapestPrice(n, edges, src, dst, k) << endl;

    // Time Limit Exceeded
    n = 18, src = 7, dst = 2, k = 6;
    edges = {{16, 1, 81}, {15, 13, 47}, {1, 0, 24}, {5, 10, 21}, {7, 1, 72}, {0, 4, 88}, {16, 4, 39}, {9, 3, 25}, {10, 11, 28}, {13, 8, 93}, {10, 3, 62}, {14, 0, 38}, {3, 10, 58}, {3, 12, 46}, {3, 8, 2}, {10, 16, 27}, {6, 9, 90}, {14, 8, 6}, {0, 13, 31}, {6, 4, 65}, {14, 17, 29}, {13, 17, 64}, {12, 5, 26}, {12, 1, 9}, {12, 15, 79}, {16, 11, 79}, {16, 15, 17}, {4, 0, 21}, {15, 10, 75}, {3, 17, 23}, {8, 5, 55}, {9, 4, 19}, {0, 10, 83}, {3, 7, 17}, {0, 12, 31}, {11, 5, 34}, {17, 14, 98}, {11, 14, 85}, {16, 7, 48}, {12, 6, 86}, {5, 17, 72}, {4, 12, 5}, {12, 10, 23}, {3, 2, 31}, {12, 7, 5}, {6, 13, 30}, {6, 7, 88}, {2, 17, 88}, {6, 8, 98}, {0, 7, 69}, {10, 15, 13}, {16, 14, 24}, {1, 17, 24}, {13, 9, 82}, {13, 6, 67}, {15, 11, 72}, {12, 0, 83}, {1, 4, 37}, {12, 9, 36}, {9, 17, 81}, {9, 15, 62}, {8, 15, 71}, {10, 12, 25}, {7, 6, 23}, {16, 5, 76}, {7, 17, 4}, {3, 11, 82}, {2, 11, 71}, {8, 4, 11}, {14, 10, 51}, {8, 10, 51}, {4, 1, 57}, {6, 16, 68}, {3, 9, 100}, {1, 14, 26}, {10, 7, 14}, {8, 17, 24}, {1, 11, 10}, {2, 9, 85}, {9, 6, 49}, {11, 4, 95}};
    cout << "from " << src << " to " << dst << " within " << k << " stops, cheapest: " << findCheapestPrice(n, edges, src, dst, k) << endl;

    src = 0;
    edges = {{0, 1, 100}, {0, 2, 100}, {0, 3, 10}, {1, 2, 100}, {1, 4, 10}, {2, 1, 10}, {2, 3, 100}, {2, 4, 100}, {3, 2, 10}, {3, 4, 100}};
    n = 5, dst = 4, k = 3;
    cout << "from " << src << " to " << dst << " within " << k << " stops, cheapest: " << findCheapestPrice(n, edges, src, dst, k) << endl;

    edges = {{0, 1, 100}, {1, 2, 100}, {0, 2, 500}, {2, 3, 100}};
    n = 4, k = 1, dst = 3;
    cout << "from " << src << " to " << dst << " within " << k << " stops, cheapest: " << findCheapestPrice(4, edges, src, dst, k) << endl;
    k = 2;
    cout << "from " << src << " to " << dst << " within " << k << " stops, cheapest: " << findCheapestPrice(4, edges, src, dst, k) << endl;
    k = 0;
    cout << "from " << src << " to " << dst << " within " << k << " stops, cheapest: " << findCheapestPrice(4, edges, src, dst, k) << endl;
}

int main(int argc, char const *argv[])
{
    testKthLargest();
    // testArray(lastStoneWeight, "lastStoneWeight", generateArrayInput, printInt);
    // testfindKthLargest();
    // testfindCheapestPrice();
    return 0;
}
