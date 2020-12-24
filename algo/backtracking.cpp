#include <vector>
#include "../common.h"

using namespace std;

void select(vector<vector<int>> &ans, vector<int> &one, int n, int k, int i)
{
    if (k == 0)
    {
        ans.push_back(one);
        return;
    }
    for (int j = i; j <= n; ++j)
    {
        one[k - 1] = j;
        select(ans, one, n, k - 1, j + 1);
    }
}

// 77. Combinations
// 12 ms, faster than 96.31%
// 9.3 MB, less than 86.38%
vector<vector<int>> combine(int n, int k)
{
    vector<vector<int>> ans;
    vector<int> one(k, 0);
    select(ans, one, n, k, 1);
    return ans;
}

vector<vector<int>> combinewrapper(vector<int> &arr)
{
    return combine(arr[0], arr[1]);
}

vector<vector<int>> testCombin()
{
    return {
        {1, 1},
        {4, 1},
        {4, 2},
    };
}
void backtracking(vector<int> &nums, vector<vector<int>> &ans, int i)
{
    if (i == nums.size() - 1)
    {
        ans.push_back(nums);
        return;
    }
    for (int j = i; j < nums.size(); ++j)
    {
        swap(nums[j], nums[i]);
        backtracking(nums, ans, i + 1);
        swap(nums[j], nums[i]);
    }
}

// 46. Permutations
// 4 ms, faster than 79.80%
vector<vector<int>> permute(vector<int> &nums)
{
    vector<vector<int>> ans;
    backtracking(nums, ans, 0);
    return ans;
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
    // format_test(permute, testpermute);
    format_test(combinewrapper, testCombin);
    return 0;
}