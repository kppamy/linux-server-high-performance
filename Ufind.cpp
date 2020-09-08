#include <vector>
#include <iostream>
#include "common.h"

class Ufind
{
private:
    vector<int> uf;
    int len;

public:
    int findp(int a)
    {
        if (a == uf[a])
            return a;
        else
            return findp(uf[a]);
    }

    void union_set(int a, int b)
    {
        a = findp(a);
        b = findp(b);
        if (a != b)
        {
            uf[b] = a;
        }
    }

    int findCircleNum(vector<vector<int>> &M)
    {

        len = M.size();

        if (len == 1)
            return 1;
        uf.resize(len, 0);
        for (int i = 0; i < len; i++)
        {
            uf[i] = i;
        }

        for (int i = 0; i < len; i++)
        {
            for (int j = i + 1; j < len; j++)
            {
                if (M[i][j] == 1)
                {
                    union_set(i, j);
                }
            }
        }
        int sum = 0;
        for (int i = 0; i < len; i++)
        {
            if (uf[i] == i)
            {
                sum++;
            }
        }

        return sum;
    }

    void testfindCircleNum()
    {
        vector<vector<int>> fc = {{1, 1, 0},
                                  {1, 1, 0},
                                  {0, 0, 1}};

        vector<vector<int>> fc2 = {{1, 1, 0},
                                   {1, 1, 1},
                                   {0, 1, 1}};

        vector<vector<int>> fc3 = {{1, 0, 0, 1}, {0, 1, 1, 0}, {0, 1, 1, 1}, {1, 0, 1, 1}};
        vector<vector<int>> fc4 = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};

        for (int i = 0; i < fc4.size(); i++)
            printVector(fc4[i]);
        cout << "findCircleNum:  " << findCircleNum(fc4) << endl;

        for (int i = 0; i < fc3.size(); i++)
            printVector(fc3[i]);
        cout << "findCircleNum:  " << findCircleNum(fc3) << endl;

        for (int i = 0; i < 3; i++)
            printVector(fc[i]);
        cout << "findCircleNum:  " << findCircleNum(fc) << endl;

        for (int i = 0; i < 3; i++)
            printVector(fc2[i]);
        cout << "findCircleNum:  " << findCircleNum(fc2) << endl;
    }

    // 128. Longest Consecutive Sequence
    int longestConsecutive(vector<int> &nums)
    {
    }

    void testlongestConsecutive()
    {
    }
};

int main(int argc, char **argv)
{
    Ufind uf;
    uf.testfindCircleNum();
    return 0;
}
