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
int dp[15][4][13];
int num[15];
int f(int pos,int sa,int sb,bool limit)
{
    if(pos==-1) return (sb==0)&&((sa&2)!=0);
    if(!limit&&dp[pos][sa][sb]!=-1)
        return dp[pos][sa][sb];
    int ans=0,st;
    int last=limit?num[pos]:9;
    for(int i=0;i<=last;++i)
    {
        if(i==1) st=(1|(sa&2));
        else if(i==3) st=((sa&1)<<1)|(sa&2);
        else st=sa&2;
        ans+=f(pos-1,st,(sb*10+i)%13,limit&&(i==last));
    }
    if(!limit) dp[pos][sa][sb]=ans;
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
    return f(len-1,0,0,true);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    memset(dp,0xff,sizeof(dp));
    int n;
    while(~scanf("%d",&n))
    {
        printf("%d\n",cal(n));
    }
    return 0;
}
