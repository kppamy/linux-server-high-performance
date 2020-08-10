#include <vector>
#include <stack>
#include <iostream>
#include <type_traits>

using namespace std;

static const int DEAFAULT = -1;
static const int DISCOVERED = 0;
static const int FINISHED = 1;
//Runtime: 76 ms, faster than 27.12% of C++ online submissions for Course Schedule.
// Memory Usage: 82.4 MB, less than 5.01% of C++ online submissions for Course Schedule.
bool dfs(int vertice, int numCourses, vector<int>& color, vector<vector<int>> &graph, stack<int> &que) {
    if (color[vertice] == DEAFAULT)
        que.push(vertice);

    if (que.empty()||color[vertice]==FINISHED) {
        return true;
    }
    color[vertice] = DISCOVERED;
    for (int j=0;j<numCourses;j++) {
        if (vertice!=j && graph[vertice][j]==1) {
            if (color[j]==DISCOVERED) {
                return false;
            }
            if(!dfs(j, numCourses, color, graph, que))
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
bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    // represent the coures adj matrix
    vector<vector<int>> graph(numCourses, vector<int>(numCourses, 0));
    for (int i=0;i<prerequisites.size();i++) {
        graph[prerequisites[i][1]][prerequisites[i][0]] = 1;
    }

    // DFS each vertex
    vector<int> color(numCourses, DEAFAULT);
    stack<int> que;
    for (int i=0;i<numCourses;i++) {
        if (!dfs(i,numCourses,color,graph,que))
            return false;
    }
    return true;
}

void test(const vector<int> &arr){
  cout<<"size: "<<arr.size()<<endl;
}

void testcanFinish() {
    vector<vector<int>> arr={ { 0, 1 } };
    vector<vector<int>> arr2={ { 0, 1 }, { 1, 0 } };
    vector<vector<int>> arr3={ { 1, 0 } };
    vector<vector<int>> arr4={{1,0},{2,0},{0,2}};
    cout<<"{1,0},{2,0},{0,2} can "<<(canFinish(3, arr4)?"":" not ")<<"finish"<<endl;
    cout<<"[0,1],[1,0] can "<<(canFinish(2, arr2)?"":" not ")<<"finish"<<endl;
    cout<<"[1,0] can "<<(canFinish(2, arr3)?"":" not ")<<"finish"<<endl;
    cout<<"[0,1] can "<<(canFinish(2, arr)?"":" not ")<<"finish"<<endl;
    vector<int> arr1={ 0 };
    test(arr1);
}

int main(int argc, char const *argv[])
{
    /* code */
    testcanFinish();
    return 0;
}
