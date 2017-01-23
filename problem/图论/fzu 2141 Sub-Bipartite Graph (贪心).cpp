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
const int maxn=100+10;
int g[maxn][maxn],color[maxn],B,W;
void cal(int p)
{
    int b=0,w=0;
    color[p]=1;
    for(int i=1;i<p;++i)
        if(g[i][p]&&color[i]!=color[p]) b++;
    color[p]=2;
    for(int i=1;i<p;++i)
        if(g[i][p]&&color[i]!=color[p]) w++;
    if(b>w) color[p]=1,B++;
    else color[p]=2,W++;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n,m;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        memset(color,0,sizeof(color));
        memset(g,0,sizeof(g));
        int u,v;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&u,&v);
            g[u][v]=g[v][u]=1;
        }
        B=W=0;
        for(int i=1;i<=n;++i)
            cal(i);
        printf("%d",B);
        for(int i=1;i<=n;++i)
            if(color[i]==1) printf(" %d",i);
        printf("\n");
        printf("%d",W);
        for(int i=1;i<=n;++i)
            if(color[i]==2) printf(" %d",i);
        printf("\n");
    }
    return 0;
}
