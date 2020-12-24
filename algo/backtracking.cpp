#include <vector>
#include "../common.h"

using namespace std;
void backtracking(vector<int> &nums,vector<vector<int>>& ans,int i){
    if(i==nums.size()-1){
        ans.push_back(nums);
        return;
    }
    for(int j=i;j<nums.size();++j){
        swap(nums[j],nums[i]);
        backtracking(nums,ans,i+1);
        swap(nums[j],nums[i]);
    }
}

// 46. Permutations
// 4 ms, faster than 79.80%
vector<vector<int>> permute(vector<int> &nums){
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
    format_test(permute, testpermute);
    return 0;
}