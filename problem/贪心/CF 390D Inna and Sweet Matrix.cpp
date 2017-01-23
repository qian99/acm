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
const int maxn=55;
const int dir[2][2]={{0,1},{1,0}};
int q[10010][2],pa[maxn][maxn][2],n,m,k;
bool vis[maxn][maxn];
void ptpath(int x,int y)
{
    if(x==-1&&y==-1) return ;
    ptpath(pa[x][y][0],pa[x][y][1]);
    printf("(%d,%d) ",x,y);
}
void solve()
{
    memset(vis,0,sizeof(vis));
    int l=0,r=0;
    q[r][0]=1;q[r++][1]=1;
    vis[1][1]=true;
    pa[1][1][0]=pa[1][1][1]=-1;
    int x,y,dx,dy;
    while(l<r)
    {
        if(r>=k) break;
        x=q[l][0];y=q[l++][1];
        for(int i=0;i<2;++i)
        {
            dx=x+dir[i][0];
            dy=y+dir[i][1];
            if(dx<=n&&dy<=m&&!vis[dx][dy])
            {
                vis[dx][dy]=true;
                pa[dx][dy][0]=x;
                pa[dx][dy][1]=y;
                q[r][0]=dx;q[r++][1]=dy;
            }
        }
    }
    int sum=0;
    for(int i=0;i<k;++i)
        sum+=(q[i][0]+q[i][1]-1);
    printf("%d\n",sum);
    for(int i=k-1;i>=0;--i)
    {
        ptpath(q[i][0],q[i][1]);
        printf("\n");
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d%d%d",&n,&m,&k);
    solve();
    return 0;
}