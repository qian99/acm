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
const int maxn=20;
int a[maxn][maxn],val[maxn],n,m;
int res[maxn],sel[maxn],d[maxn];
bool vis[maxn];
double minrat;
double prime()
{
    double nodew=0;
    for(int i=0;i<m;++i)
    {
        nodew+=val[sel[i]];
        d[i]=a[sel[0]][sel[i]];
    }
    memset(vis,0,sizeof(vis));
    vis[0]=true;
    int sum=0;
    for(int i=1;i<m;++i)
    {
        int minval=inf;
        int pos;
        for(int j=0;j<m;++j)
        {
            if(!vis[j]&&d[j]<minval)
            {
                minval=d[j];
                pos=j;

            }
        }
        sum+=minval;
        vis[pos]=true;
        for(int j=0;j<m;++j)
            d[j]=min(d[j],a[sel[pos]][sel[j]]);
    }
    return sum/nodew;
}
void dfs(int x,int y)
{
    if(y==m)
    {
        double tmp=prime();
        if(minrat>tmp)
        {
            minrat=tmp;
            for(int i=0;i<m;++i)
                res[i]=sel[i];
        }
        return ;
    }
    if(x==n+1) return ;
    sel[y]=x;
    dfs(x+1,y+1);
    dfs(x+1,y);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&n,&m))
    {
        if(n+m==0) break;
        for(int i=1;i<=n;++i)
            scanf("%d",&val[i]);
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                scanf("%d",&a[i][j]);
        minrat=1e10;
        dfs(1,0);
        for(int i=0;i<m;++i)
        {
            if(i) printf(" ");
            printf("%d",res[i]);
        }
        printf("\n");
    }
    return 0;
}

