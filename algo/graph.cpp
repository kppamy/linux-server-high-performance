#include <vector>
#include <stack>
#include <queue>
#include <iostream>
#include <type_traits>
#include "../common.h"

using namespace std;

vector<int> directions = {-1, 0, 1, 0, -1}; //up,right,down,left

void findIslandDfs(vector<vector<int>> &A, queue<pair<int, int>> &found, int i, int j)
{
    found.push(make_pair(i, j));
    A[i][j] = 2;
    for (int d = 0; d < 4; d++)
    {
        int x = i + directions[d], y = j + directions[d + 1];
        if (x < 0 || y < 0 || x >= A.size() || y >= A[0].size())
            continue;
        if (A[x][y] == 1)
        {
            findIslandDfs(A, found, x, y);
        }
    }
}

// 934. Shortest Bridge
// 84 ms, faster than 84.43%
int shortestBridge(vector<vector<int>> &A)
{
    int rows = A.size(), cols = A[0].size();
    queue<pair<int, int>> islandA;
    bool found = false;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            if (A[i][j] == 1)
            {
                findIslandDfs(A, islandA, i, j);
                found = true;
            }
            if (found)
                break;
        }
        if (found)
            break;
    }

    int depth = 0;

    while (!islandA.empty())
    {

        depth++;
        int sz = islandA.size();
        while (sz-- > 0)
        {
            auto [r, c] = islandA.front();
            islandA.pop();
            for (int d = 0; d < 4; ++d)
            {
                int x = r + directions[d], y = c + directions[d + 1];
                if (x < 0 || y < 0 || x >= A.size() || y >= A[0].size())
                    continue;
                if (A[x][y] == 2)
                    continue;
                if (A[x][y] == 1)
                    return depth - 1;
                A[x][y] = 2;
                islandA.push(make_pair(x, y));
            }
        }
    }
    return 0;
}

vector<my2arr> testshortestBridge()
{
    return {
        {{0, 0, 1, 0, 1}, {0, 1, 1, 0, 1}, {0, 1, 0, 0, 1}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}},
        {{0, 1}, {1, 0}},
        {{0, 1, 0}, {0, 0, 0}, {0, 0, 1}},
        {{1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 0, 1, 0, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1}}};
}

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
        states = vector<int>(numCourses, STATE::DEAFAULT);
        sorted = {};
        for (auto &&pre : prerequisites)
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

// 695. Max Area of Island
// 44 ms, faster than 24.08%
int maxAreaOfIsland(vector<vector<int>> &grid)
{
    int rows = grid.size(), cols = grid[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    stack<pair<int, int>> sta;
    vector<int> rdirection{1, -1, 0, 0};
    vector<int> cdirection{0, 0, 1, -1};
    int res = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (grid[i][j] == 1 && !visited[i][j])
            {
                int cnt = 0;
                sta.push(make_pair(i, j));
                visited[i][j] = true;
                while (!sta.empty())
                {
                    auto [r, c] = sta.top();
                    sta.pop();
                    cnt++;
                    for (int d = 0; d < 4; d++)
                    {
                        int ni = r + rdirection[d], nj = c + cdirection[d];
                        if (ni >= rows || ni < 0 || nj >= cols || nj < 0)
                            continue;
                        if (grid[ni][nj] == 1 && !visited[ni][nj])
                        {
                            sta.push(make_pair(ni, nj));
                            visited[ni][nj] = true;
                        }
                    }
                }
                res = res >= cnt ? res : cnt;
            }
        }
    }
    return res;
}

vector<my2arr> testmaxAreaOfIsland()
{
    return {
        {{1, 1, 0, 1, 1},
         {1, 0, 0, 0, 0},
         {0, 0, 0, 0, 1},
         {1, 1, 0, 1, 1}},
        {{0, 0, 0, 0, 0, 0, 0, 0}},
        {{0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
         {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0},
         {0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}},
    };
}

void canFlowdfs(vector<vector<int>> &matrix, vector<vector<bool>> &flowup, int r, int c)
{
    if (flowup[r][c])
        return;
    flowup[r][c] = true;
    for (int i = 0; i < 4; i++)
    {
        int x = r + directions[i], y = c + directions[i + 1];
        if (x < 0 || y < 0 || x >= matrix.size() || y >= matrix[0].size())
            continue;
        if (matrix[r][c] <= matrix[x][y])
        {
            canFlowdfs(matrix, flowup, x, y);
        }
    }
}

// 417. Pacific Atlantic Water Flow
// 84 ms, faster than 61.89%
vector<vector<int>> pacificAtlantic(vector<vector<int>> &matrix)
{
    int rows = matrix.size();
    if (rows == 0)
        return {};
    int cols = matrix[0].size();
    vector<vector<bool>> pac(rows, vector<bool>(cols, false));
    vector<vector<bool>> atl(rows, vector<bool>(cols, false));
    vector<vector<int>> ans;
    for (int i = 0; i < rows; i++)
    {
        canFlowdfs(matrix, pac, i, 0);
        canFlowdfs(matrix, atl, i, cols - 1);
    }
    for (int j = 0; j < cols; j++)
    {
        canFlowdfs(matrix, pac, 0, j);
        canFlowdfs(matrix, atl, rows - 1, j);
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; ++j)
        {
            if (pac[i][j] && atl[i][j])
            {
                ans.push_back(vector<int>{i, j});
            }
        }
    }
    return ans;
}

vector<my2arr> testpacificAtlantic()
{
    return {
        {{12, 7, 7, 14, 6, 17, 12, 17, 8, 18, 9, 5},
         {6, 8, 12, 5, 3, 6, 2, 14, 19, 6, 18, 13},
         {0, 6, 3, 8, 8, 10, 8, 17, 13, 13, 13, 12},
         {5, 6, 8, 8, 15, 16, 19, 14, 7, 11, 2, 3},
         {7, 18, 2, 7, 10, 10, 3, 14, 13, 15, 15, 7},
         {18, 6, 19, 4, 12, 3, 3, 2, 6, 6, 19, 6},
         {3, 18, 5, 16, 19, 6, 3, 12, 6, 0, 14, 11},
         {9, 10, 17, 12, 10, 11, 11, 9, 0, 0, 12, 0},
         {4, 13, 3, 0, 4, 12, 9, 5, 6, 17, 10, 11},
         {18, 3, 5, 0, 8, 19, 18, 4, 8, 19, 1, 3},
         {16, 2, 14, 6, 4, 14, 7, 2, 9, 7, 13, 18},
         {0, 16, 19, 16, 16, 4, 15, 19, 7, 0, 3, 16},
         {13, 8, 12, 8, 2, 3, 5, 18, 6, 15, 18, 6},
         {4, 10, 8, 1, 16, 0, 6, 0, 14, 10, 11, 8},
         {7, 1, 3, 4, 11, 12, 9, 0, 6, 2, 17, 5},
         {1, 16, 6, 1, 0, 19, 11, 1, 5, 7, 8, 2},
         {4, 1, 14, 13, 14, 7, 3, 7, 1, 9, 15, 18},
         {14, 11, 6, 14, 14, 14, 4, 0, 11, 17, 1, 9},
         {3, 14, 2, 10, 3, 1, 9, 16, 1, 13, 0, 15},
         {8, 9, 13, 5, 5, 7, 10, 1, 4, 5, 0, 9},
         {13, 16, 15, 5, 17, 6, 16, 13, 5, 7, 3, 15},
         {5, 1, 12, 19, 3, 13, 0, 0, 3, 10, 6, 13},
         {12, 17, 9, 16, 16, 6, 2, 6, 12, 15, 14, 16},
         {7, 7, 0, 6, 4, 15, 1, 7, 17, 5, 2, 12},
         {3, 17, 0, 2, 4, 5, 11, 7, 16, 16, 16, 13},
         {3, 7, 16, 11, 2, 16, 14, 9, 16, 17, 10, 3},
         {12, 18, 17, 17, 5, 15, 1, 2, 12, 12, 5, 7},
         {11, 10, 10, 0, 11, 7, 17, 14, 5, 15, 2, 16},
         {7, 19, 14, 7, 6, 2, 4, 16, 11, 19, 14, 14},
         {6, 17, 6, 6, 6, 15, 9, 12, 8, 13, 1, 7},
         {16, 3, 15, 0, 18, 17, 0, 11, 3, 16, 11, 12},
         {15, 12, 4, 6, 19, 15, 17, 7, 3, 9, 2, 11}},
        {},
        {{1, 2, 2, 3, 5},
         {3, 2, 3, 4, 4},
         {2, 4, 5, 3, 1},
         {6, 7, 1, 4, 5},
         {5, 1, 1, 2, 4}}};
}

vector<vector<int>> dfsPermute(vector<int> &nums, int i)
{
    if (i == 0)
        return {{nums[0]}};
    vector<vector<int>> ans;
    vector<vector<int>> sub = dfsPermute(nums, i - 1);
    for (auto &&val : sub)
    {
        for (int j = 0; j <= i; ++j)
        {
            vector<int> onep(i + 1, 11);
            onep[j] = nums[i];
            if (j >= 1)
                copy(val.begin(), val.begin() + j, onep.begin());
            copy(val.begin() + j, val.end(), onep.begin() + j + 1);
            ans.push_back(onep);
        }
    }
    return ans;
}

// 46. Permutations
// 4 ms, faster than 79.80%
vector<vector<int>> permute(vector<int> &nums)
{
    int len = nums.size();
    return dfsPermute(nums, len - 1);
}

my2arr testpermute()
{
    return {
        {1, 2, 3},
        {1},
        {0, 1},
        {1, 2, 3, 4},
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5, 6}};
}

int main(int argc, char const *argv[])
{
    /* code */
    // testcanFinish();
    // Graph ts;
    // ts.testfindOrder();
    // format_test(maxAreaOfIsland, testmaxAreaOfIsland, printInt);
    // format_test(pacificAtlantic, testpacificAtlantic);
    // format_test(permute, testpermute);
    format_test(shortestBridge, testshortestBridge);
    return 0;
}
