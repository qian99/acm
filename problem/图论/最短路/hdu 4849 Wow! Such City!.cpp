#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<set>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=1000+10;
const int maxm=1000000+10;
const int mod1=5837501;
const int mod2=9860381;
const int mod3=8475871;
ll X[maxm],Y[maxm],Z[maxm];
ll g[maxn][maxn],d[maxn];
bool vis[maxn];
int dijkstra(int n,int m)
{
    memset(vis,0,sizeof(vis));
    for(int i=0;i<=n;++i) d[i]=g[0][i];
    d[0]=0;
    vis[0]=true;
    int res=m;
    for(int i=1;i<n;++i)
    {
        ll minv=Inf;
        int pos=0;
        for(int j=0;j<n;++j)
            if(!vis[j]&&d[j]<minv)
            {
                minv=d[j];
                pos=j;
            }
        vis[pos]=true;
        res=min(res,(int)(minv%m));
        for(int i=0;i<n;++i)
            if(!vis[i])
                d[i]=min(d[i],d[pos]+g[pos][i]);
    }
    return res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,X0,X1,Y0,Y1;
    while(~scanf("%d%d%d%d%d%d",&n,&m,&X0,&X1,&Y0,&Y1))
    {
        X[0]=X0;X[1]=X1;
        Y[0]=Y0;Y[1]=Y1;
        for(int i=2;i<=n*n;++i)
        {
            X[i]=(12345+X[i-1]*23456+X[i-2]*34567+X[i-1]*X[i-2]%mod1*45678)%mod1;
            Y[i]=(56789+Y[i-1]*67890+Y[i-2]*78901+Y[i-1]*Y[i-2]%mod2*89012)%mod2;
        }
        for(int i=0;i<=n*n;++i)
            Z[i]=(X[i]*90123+Y[i])%mod3+1;
        for(int i=0;i<n;++i)
            for(int j=0;j<n;++j)
                g[i][j]=(i==j)?0:Z[i*n+j];
        int ans=dijkstra(n,m);
        printf("%d\n",ans);
    }
    return 0;
}

