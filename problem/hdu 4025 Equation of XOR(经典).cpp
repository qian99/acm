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
int a[50][50];
int S[50][50];
ll x[50][50];
map<ll,ll>mp;
ll ans=0;
void dfs1(int s,int t,ll val)
{
    if(s>t)
    {
        mp[val]++;
        return;
    }
    for(int i=1;i<=x[s][0];++i)
    {
        dfs1(s+1,t,val^x[s][i]);
    }
}
void dfs2(int s,int t,int val)
{
    if(s>t)
    {
        if(mp[val]) ans+=mp[val];
        return;
    }
    for(int i=1;i<=x[s][0];++i)
    {
        dfs2(s+1,t,val^x[s][i]);
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n,m;
        scanf("%d%d",&n,&m);
        mp.clear();
        for(int i=1;i<=n;++i)
          for(int j=1;j<=m;++j)
            scanf("%d",&a[i][j]);
        for(int i=1;i<=m;++i)
        {
            scanf("%d",&S[i][0]);
            for(int j=1;j<=S[i][0];++j)
              scanf("%d",&S[i][j]);
        }
        for(int i=1;i<=m;++i)
        {
            x[i][0]=0;
            for(int j=1;j<=S[i][0];++j)
            {
                ll tmp=0;
                for(int k=1;k<=n;++k)
                {
                    tmp<<=2;
                    tmp+=S[i][j]*a[k][i];
                }
                x[i][++x[i][0]]=tmp;
            }
        }
        ans=0;
        dfs1(1,m/2,0);
        dfs2(m/2+1,m,0);
        printf("%I64d\n",ans);
    }
    return 0;
}
