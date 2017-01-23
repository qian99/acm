
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
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=200+10;
const int dirx[4]={0,1,0,-1};
const int diry[4]={1,0,-1,0};
int mat[maxn][maxn],d[20][maxn][maxn];
int dis[55][55],pos[20][2],dp[15][1<<13],n,m,N;
bool inq[maxn][maxn];
void spfa(int x,int y,int id)
{
    memset(d[id],0x3f,sizeof(d[id]));
    memset(inq,0,sizeof(inq));
    queue<pair<int,int> >q;
    q.push(make_pair(x,y));
    d[id][x][y]=0;
    int dx,dy;
    while(!q.empty())
    {
        x=q.front().first;
        y=q.front().second;
        inq[x][y]=false;
        q.pop();
        for(int i=0;i<4;++i)
        {
            dx=x+dirx[i];
            dy=y+diry[i];
            if(dx<=0||dy<=0||dx>n||dy>m)
            {
                if(d[id][0][0]>d[id][x][y])
                    d[id][0][0]=d[id][x][y];
            }
            else if(mat[dx][dy]!=-1)
            {
                if(d[id][dx][dy]>d[id][x][y]+mat[dx][dy])
                {
                    d[id][dx][dy]=d[id][x][y]+mat[dx][dy];
                    if(!inq[dx][dy]) {inq[dx][dy]=true;q.push(make_pair(dx,dy));}
                }
            }
        }
    }
}
int f(int u,int st)
{
    if(st==(1<<N)-1) return d[u][0][0];
    if(dp[u][st]!=-1) return dp[u][st];
    dp[u][st]=inf;
    for(int v=0;v<N;++v)
    {
        if(st&(1<<v)) continue;
        dp[u][st]=min(dp[u][st],f(v,st|(1<<v))+dis[u][v]);
    }
    return dp[u][st];
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
        for(int i=1;i<=n;++i)
            for(int j=1;j<=m;++j)
                scanf("%d",&mat[i][j]);
        int K,x,y;
        N=0;
        scanf("%d",&K);
        for(int i=0;i<K;++i)
        {
            scanf("%d%d",&x,&y);
            x++;y++;
            spfa(x,y,N);
            if(d[N][0][0]!=inf)
                pos[N][0]=x,pos[N++][1]=y;
        }
        for(int i=0;i<N;++i)
            for(int j=0;j<N;++j)
                if(i!=j) dis[i][j]=d[i][pos[j][0]][pos[j][1]];
                else dis[i][j]=0;
        int ans=inf;
        memset(dp,0xff,sizeof(dp));
        for(int i=0;i<N;++i)
        {
            ans=min(ans,f(i,1<<i)+d[i][0][0]+mat[pos[i][0]][pos[i][1]]);
        }
        if(N==0) ans=0;
        printf("%d\n",ans);
    }
    return 0;
}
