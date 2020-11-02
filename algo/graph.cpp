#include <vector>
#include <stack>
#include <iostream>
#include <type_traits>
#include "common.h"

using namespace std;

static const int DEAFAULT = -1;
static const int DISCOVERED = 0;
static const int FINISHED = 1;
//Runtime: 76 ms, faster than 27.12% of C++ online submissions for Course Schedule.
// Memory Usage: 82.4 MB, less than 5.01% of C++ online submissions for Course Schedule.
bool dfs(int vertice, int numCourses, vector<int> &color, vector<vector<int>> &graph, stack<int> &que)
{
    if (color[vertice] == DEAFAULT)
        que.push(vertice);

    if (que.empty() || color[vertice] == FINISHED)
    {
        return true;
    }
    color[vertice] = DISCOVERED;
    for (int j = 0; j < numCourses; j++)
    {
        if (vertice != j && graph[vertice][j] == 1)
        {
            if (color[j] == DISCOVERED)
            {
                return false;
            }
            if (!dfs(j, numCourses, color, graph, que))
                return false;
        }
    }
    que.pop();
    color[vertice] = FINISHED;
    return true;
}

// 207. Course Schedule
// why can not pass { { 0, 1 }, { 1, 0 } } directly?
// why the vector value changed if pass by reference to const?
bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
{
    // represent the coures adj matrix
    vector<vector<int>> graph(numCourses, vector<int>(numCourses, 0));
    for (int i = 0; i < prerequisites.size(); i++)
    {
        graph[prerequisites[i][1]][prerequisites[i][0]] = 1;
    }

    // DFS each vertex
    vector<int> color(numCourses, DEAFAULT);
    stack<int> que;
    for (int i = 0; i < numCourses; i++)
    {
        if (!dfs(i, numCourses, color, graph, que))
            return false;
    }
    return true;
}

#include <list>

class Graph
{

private:
    enum STATE
    {
        DEAFAULT,
        DISCOVERED,
        FINISHED
    };
    vector<int> states;
    vector<list<int>> al;
    vector<int> sorted;

    // tropological sort
    // for each vertex, white(v) ,root->pre
    // for each vertex, DFS(v, vertices,aj,sorted)
    //  v finished, push front v.
public:
    bool dfs(int v)
    {
        if (states[v] == STATE::DISCOVERED)
            return false;
        else if (states[v] == STATE::FINISHED)
            return true;
        states[v] = STATE::DISCOVERED;
        for (auto &&i : al[v])
        {
            if (!dfs(i))
                return false;
        }
        states[v] = STATE::FINISHED;
        sorted.push_back(v);
        return true;
    }

    // 210. Course Schedule II
    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
    {
        if (numCourses == 1)
            return {0};
        int len = prerequisites.size();
        if (len == 0)
        {
            sorted.resize(numCourses);
            for (int i = 0; i < numCourses; i++)
                sorted[i] = i;
            return sorted;
        }
        al.clear();
        al.resize(numCourses, {});
        states=vector<int>(numCourses,STATE::DEAFAULT);
        sorted={};
        for (auto&& pre : prerequisites)
        {
            al[pre[0]].push_back(pre[1]);
        }

        for (int i = 0; i < numCourses; i++)
        {
            if (!dfs(i))
                return {};
        }
        return sorted;
    }

    void testfindOrder()
    {
        // test case 1: {0,1}
        int numCourses = 2;
        vector<vector<int>> pre = {{1, 0}};
        for (auto i : pre)
        {
            printVector(i);
        }
        vector<int> out = findOrder(numCourses, pre);
        cout << " the order to finish " << numCourses << " is: ";
        printVector(out);


        // test case 2: {}
        numCourses = 2;
        pre = {{1, 0}, {0, 1}};
        for (auto i : pre)
        {
            printVector(i);
        }
        out = findOrder(numCourses, pre);
        cout << " the order to finish " << numCourses << " courses is: ";
        printVector(out);


        // test case 3: {0, 1,2,3}
        numCourses = 4;
        pre = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};
        for (auto i : pre)
        {
            printVector(i);
        }
        out = findOrder(numCourses, pre);
        cout << " the order to finish " << numCourses << " courses is: ";
        printVector(out);

        
        // test case 4: {0}
        numCourses = 1;
        pre = {};
        for (auto i : pre)
        {
            printVector(i);
        }
        out = findOrder(numCourses, pre);
        cout << " the order to finish " << numCourses << " courses is: ";
        printVector(out);
    }
};

void test(const vector<int> &arr)
{
    cout << "size: " << arr.size() << endl;
}

void testcanFinish()
{
    vector<vector<int>> arr = {{0, 1}};
    vector<vector<int>> arr2 = {{0, 1}, {1, 0}};
    vector<vector<int>> arr3 = {{1, 0}};
    vector<vector<int>> arr4 = {{1, 0}, {2, 0}, {0, 2}};
    cout << "{1,0},{2,0},{0,2} can " << (canFinish(3, arr4) ? "" : " not ") << "finish" << endl;
    cout << "[0,1],[1,0] can " << (canFinish(2, arr2) ? "" : " not ") << "finish" << endl;
    cout << "[1,0] can " << (canFinish(2, arr3) ? "" : " not ") << "finish" << endl;
    cout << "[0,1] can " << (canFinish(2, arr) ? "" : " not ") << "finish" << endl;
    vector<int> arr1 = {0};
    test(arr1);
}

int main(int argc, char const *argv[])
{
    /* code */
    // testcanFinish();
    Graph ts;
    ts.testfindOrder();
    return 0;
}
