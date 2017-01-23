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
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
int need[15],C[15][15],tot,cnt;
int color[7];
void Init()
{
    memset(C,0,sizeof(C));
    C[0][0]=1;
    for(int i=1;i<=12;++i)
    {
        C[i][0]=1;
        for(int j=1;j<=i;++j)
            C[i][j]=C[i-1][j-1]+C[i-1][j];
    }
}
void dfs(int x)
{
    if(x==tot)
    {
        cnt++;
        return ;
    }
    for(int i=1;i<=6;++i)
    {
        if(color[i]>=need[x])
        {
            color[i]-=need[x];
            dfs(x+1);
            color[i]+=need[x];
        }
    }
}
ll solve()
{
    ll ans=1,tmp=12;
    for(int i=1;i<=6;++i)
    {
        if(!color[i]) continue;
        ans*=C[tmp][color[i]];
        tmp-=color[i];
    }
    tot=cnt=0;
    for(int i=0;i<6;++i) need[tot++]=2;
    dfs(0);
    ans+=cnt*3;
    need[0]=need[1]=need[2]=4;
    tot=3;cnt=0;
    dfs(0);
    ans+=cnt*6;
    need[0]=need[1]=1;tot=2;
    for(int i=0;i<5;++i) need[tot++]=2;
    cnt=0;
    dfs(0);
    ans+=cnt*6;
    need[0]=need[1]=need[2]=need[3]=3;
    tot=4;cnt=0;
    dfs(0);
    ans+=cnt*8;
    return ans/24;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    Init();
    int t;
    scanf("%d",&t);
    while(t--)
    {
        memset(color,0,sizeof(color));
        int tmp;
        for(int i=0;i<12;++i)
        {
            scanf("%d",&tmp);
            color[tmp]++;
        }
        printf("%lld\n",solve());
    }
    return 0;
}
