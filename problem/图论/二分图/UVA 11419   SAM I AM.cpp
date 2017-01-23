#include <iostream>
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
const int maxn=1000+10;
vector<int>G[maxn];
int link[maxn],linkr[maxn];
bool S[maxn],T[maxn];
bool dfs(int u)
{
    S[u]=true;
    for(int i=0;i<G[u].size();++i)
    {
        int v=G[u][i];
        if(!T[v])
        {
            T[v]=true;
            if(link[v]==-1||dfs(link[v]))
            {
                link[v]=u;
                linkr[u]=v;
                return true;
            }
        }
    }
    return false;
}
int hungary(int m)
{
    int res=0;
    memset(link,0xff,sizeof(link));
    memset(linkr,0xff,sizeof(linkr));
    for(int i=1;i<=m;++i)
    {
        memset(S,0,sizeof(S));
        memset(T,0,sizeof(T));
        if(dfs(i)) res++;
    }
    return res;
}
void slove(int m,int n)
{
    memset(S,0,sizeof(S));
    memset(T,0,sizeof(T));
    for(int i=1;i<=m;++i)
       if(linkr[i]==-1) dfs(i);
    for(int i=1;i<=m;++i)
       if(!S[i]) printf(" r%d",i);
    for(int i=1;i<=n;++i)
       if(T[i]) printf(" c%d",i);
    printf("\n");
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int m,n,q;
    while(~scanf("%d%d%d",&m,&n,&q))
    {
        if(m==0&&n==0&&q==0) break;
        int a,b;
        for(int i=0;i<=m;++i) G[i].clear();
        for(int i=0;i<q;++i)
        {
            scanf("%d%d",&a,&b);
            G[a].push_back(b);
        }
        int ans=hungary(m);
        printf("%d",ans);
        slove(m,n);
    }
    return 0;
}
