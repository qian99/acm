#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
int dp[15][2];
int num[15];
int f(int pos,int st,bool limit)
{
    if(pos==-1) return 1;
    if(!limit&&dp[pos][st]!=-1)
        return dp[pos][st];
    int ans=0;
    int last=limit?num[pos]:9;
    for(int i=0;i<=last;++i)
    {
        if(i==4||(i==2&&st)) continue;
        ans+=f(pos-1,i==6,limit&&i==last);
    }
    if(!limit) dp[pos][st]=ans;
    return ans;
}
int cal(int x)
{
    int len=0;
    while(x)
    {
        num[len++]=x%10;
        x/=10;
    }
    return f(len-1,0,true);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    memset(dp,0xff,sizeof(dp));
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        if(n==0&&m==0) break;
        printf("%d\n",cal(m)-cal(n-1));
    }
    return 0;
}
