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
const int maxn=5000+10;
const int dir[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
const int dir2[3][2]={{0,1},{0,-1},{-1,0}};
int a[maxn][maxn],n,m;
bool flag;
void bfs(int sx,int sy)
{
    queue<pair<int,int> >q;
    pair<int,int>pa;
    a[sx][sy]=2;
    if(sx==n) flag=true;
    q.push(make_pair(sx,sy));
    int x,y,dx,dy;
    while(!q.empty())
    {
        pa=q.front();q.pop();
        x=pa.first;y=pa.second;
        for(int i=0;i<4;++i)
        {
            dx=x+dir[i][0];
            dy=y+dir[i][1];
            if(dx>=1&&dx<=n&&dy>=1&&dy<=n&&a[dx][dy]==1)
            {
                a[dx][dy]=2;
                q.push(make_pair(dx,dy));
                if(dx==n) flag=true;
            }
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    char str[5];
    while(~scanf("%d%d",&n,&m))
    {
        for(int i=0;i<=n;++i)
            for(int j=0;j<=n;++j)
                a[i][j]=0;
        for(int i=0;i<=n;++i)
            a[0][i]=2;
        int x,y,dx,dy;
        flag=false;
        while(m--)
        {
            scanf("%s",str);
            if(str[0]=='O')
            {
                scanf("%d%d",&x,&y);
                if(a[x][y]==2) continue;
                a[x][y]=1;
                for(int i=0;i<4;++i)
                {
                    dx=x+dir[i][0];
                    dy=y+dir[i][1];
                    if(dx>=0&&dx<=n&&dy>=0&&dy<=n&&a[dx][dy]==2)
                    {
                        bfs(x,y);
                        break;
                    }
                }
            }
            else if(str[0]=='F')
            {
                scanf("%d%d",&x,&y);
                printf("%d\n",(a[x][y]==2?1:0));
            }
            else
            {
                if(flag) printf("1\n");
                else printf("0\n");
            }
        }
    }
    return 0;
}
