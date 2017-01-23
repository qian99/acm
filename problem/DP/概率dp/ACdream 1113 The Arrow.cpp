/*
* this code is made by qian99
* Problem: 1113
* Verdict: Accepted
* Submission Date: 2014-06-08 20:18:44
* Time: 148 MS
* Memory: 8604 KB
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<vector>
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100000+10;
double dp[maxn];
bool flag[maxn];
int n;
double f(int x)
{
    if(x==n) return 0;
    if(flag[x]) return dp[x];
    flag[x]=true;
    dp[x]=1;
    if(x+6<n)
    {
        for(int i=1;i<=6;++i)
            dp[x]+=1.0/6*f(x+i);
    }
    else
    {
        int y=n-x;
        for(int i=1;i<y;++i)
            dp[x]+=1.0/6*f(x+i);
        dp[x]*=6.0/y;
    }
    return dp[x];
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        memset(flag,0,sizeof(flag));
        double ans=f(0);
        printf("%.2lf\n",ans);
    }
    return 0;
}