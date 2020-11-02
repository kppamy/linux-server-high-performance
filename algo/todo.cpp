#include <iostream>
#include <string>
#include <vector>
#include "common.h"
using namespace std;

void getNextArr(string& str2, vector<int>& next) {
	next.at(0) = -1;
	if (str2.length() == 1) {
		return;
	}
	next.at(1) = 0;
	for (int cn = 0, i = 2; i < str2.length(); i++) {
		if (str2.at(i - 1) == str2.at(cn)) {
			next.at(i++) = ++cn;
		}
		else if (cn == 0) {
			next.at(i++) = 0;
		}
		else {
			cn = next.at(cn);
		}
	}
}

int KMP(string& str1, string& str2) {
	if (str1.empty() || str2.empty() || str1.length() < str2.length()) {
		return -1;
	}
	vector<int> next(str2.length(), 0);
	getNextArr(str2, next);
	size_t len1 = 0;
	size_t len2 = 0;
	while (len1 < str1.length() && len2 < str2.length()) {
		if (str1.at(len1) == str2.at(len2)) {
			len1++;
			len2++;
		}
		else if (next.at(len2) == -1) {
			len1++;
		}
		else {
			len2 = next.at(len2);
		}
	}
	return len2 == str2.length() ? (len1 - len2) : -1;
}

string longestPalindrome(string s)
{
if(s.size()==0)
    return "";
string s1;
for(auto a:s)
{
    s1=s1+'#';
    s1=s1+a;
}
s1=s1+'#';
int l=s1.size();
vector<int>temp(l,0);
int max_right=0,pos=0,res=0,res_pos=0;
for(int i=0;i<l;++i)
{
    if(i<max_right)temp[i]=min(temp[2*pos-i],max_right-i);
    else temp[i]=1;
    while(i-temp[i]>=0&&i+temp[i]<l&&s1[i-temp[i]]==s1[i+temp[i]])
        temp[i]++;
    if(i+temp[i]-1>max_right)
        {max_right=i+temp[i]-1;
        pos=i;}
    if(res<temp[i])
    {
        res=temp[i];
        res_pos=i;
    }
}
return s.substr((res_pos-res+1)/2,res-1);
}


 int longestCommonSubsequence(string text1, string text2) {
        int n=text1.size(),m=text2.size();
        if(n==0 || m==0)//边界情况
            return 0;
        
        int dp[n+1][m+1];//dp[n][m]表示text1[0..n-1],text2[0...m-1]的最长公共子序列
        for(int i=0;i<=n;i++)//初始化为0
            dp[i][0]=0;
        for(int j=0;j<=m;j++)
            dp[0][j]=0;

        for(int i=0;i<n;i++)//动态规划部分
            for(int j=0;j<m;j++)
            {
                if(text1[i]==text2[j])
                    dp[i+1][j+1]=dp[i][j]+1;
                else
                    dp[i+1][j+1]=max(dp[i][j+1],dp[i+1][j]);
            }
        return dp[n][m];
    }


int main() {
	
    
    vector<int> v {4, 1, 3, 5, 2, 3, 1, 7};

    printVector(v);

    string str1("abkabkacbck");
	string str2("cb");
	int res = KMP(str1, str2);
    	cout << res << endl;

    string str("abkabkacbckabkabkacbckabkabkacbck");
    char a='a';
    cout<< "size of "<<a<<" : "<<sizeof(a)<<endl;
    cout<<"\n size of "<<str<< " : "<< sizeof(str)<<endl;
        cout<<"\n capacity of "<<str<< " : "<< str.capacity()<<endl;
        cout<<"\n length of "<<str<< " : "<< str.length()<<endl;

    cout<<" longest echo "<< longestPalindrome(str)<<endl;
    cout<<" longest common string "<< longestCommonSubsequence(str1,str2)<<endl;



	return 0;
}