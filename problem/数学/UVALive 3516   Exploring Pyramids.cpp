#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
const int maxn=300+10;
const int mod=1000000000;
int dp[maxn][maxn];
char str[maxn];
int  f(int i,int j)
{
    if(i==j) return 1;
    if(str[i]!=str[j]) return 0;
    int& ans=dp[i][j];
    if(ans>=0) return ans;
    ans=0;
    for(int k=i+2;k<=j;++k)
    {
        if(str[i]==str[k])
        {
            ans=(ans+(long long)f(i+1,k-1)*(long long)f(k,j))%mod;
        }
    }
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%s",str))
    {
        memset(dp,0xff,sizeof(dp));
        printf("%d\n",f(0,strlen(str)-1));
    }
    return 0;
}

