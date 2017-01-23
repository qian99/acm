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
const int maxn=200+10;
const int maxv=11000;
int w[maxn][maxn],g[maxn][maxn],n,m;
int lx[maxn],ly[maxn],links[maxn],slack;
bool S[maxn],T[maxn];
bool dfs(int u)
{
    S[u]=true;
    int tmp,v;
    for(int i=1;i<=g[u][0];++i)
    {
        v=g[u][i];
        if(!w[u][v]) continue;
        tmp=lx[u]+ly[v]-w[u][v];
        if(tmp==0)
        {
            if(!T[v])
            {
                T[v]=true;
                if(!links[v]||dfs(links[v]))
                {
                    links[v]=u;
                    return true;
                }
            }
        }
        else slack=min(slack,tmp);
    }
    return false;
}
void update()
{
    for(int i=1;i<=n;++i)
    {
        if(S[i]) lx[i]-=slack;
        if(T[i]) ly[i]+=slack;
    }
}
void KM()
{
    memset(lx,0,sizeof(lx));
    memset(ly,0,sizeof(ly));
    memset(links,0,sizeof(links));
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            lx[i]=max(lx[i],w[i][j]);
    for(int i=1;i<=n;++i)
    {
        slack=inf;
        while(true)
        {
            memset(S,0,sizeof(S));
            memset(T,0,sizeof(T));
            if(dfs(i)) break;
            else update();
        }
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
        scanf("%d%d",&n,&m);
        memset(w,0,sizeof(w));
        int a,b,c;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&a,&b,&c);
            w[a][b]=max(w[a][b],maxv-c);
        }
        for(int i=1;i<=n;++i)
        {
            g[i][0]=0;
            for(int j=1;j<=n;++j)
                if(w[i][j]) g[i][++g[i][0]]=j;
        }
        KM();
        int sum=0;
        for(int i=1;i<=n;++i)
        {
            b=links[i];
            sum+=(maxv-w[b][i]);
        }
        printf("%d\n",sum);
    }
    return 0;
}

