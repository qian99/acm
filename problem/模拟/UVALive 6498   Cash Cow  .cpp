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
const int N=12;
const int M=10;
const int dirx[4]={0,1,0,-1};
const int diry[4]={1,0,-1,0};
char mat[15][15];
bool vis[15][15];
int cntcol[15];
void ptmat()
{
    for(int i=1;i<=N;++i)
    {
        for(int j=1;j<=M;++j)
            printf("%c",mat[i][j]);
        printf("\n");
    }
    printf("\n");
}
void changes(int mx,int my)
{
    if(mat[mx][my]=='.') return;
    memset(vis,0,sizeof(vis));
    queue<pair<int,int> >q;
    q.push(make_pair(mx,my));
    vis[mx][my]=true;
    int x,y,dx,dy,tot=1;
    pair<int,int> pii;
    while(!q.empty())
    {
        pii=q.front();q.pop();
        x=pii.first;y=pii.second;
        for(int i=0;i<4;++i)
        {
            dx=x+dirx[i];
            dy=y+diry[i];
            if(dx>=1&&dx<=N&&dy>=1&&dy<=M&&!vis[dx][dy]&&mat[dx][dy]==mat[x][y])
            {
                vis[dx][dy]=true;
                tot++;
                q.push(make_pair(dx,dy));
            }
        }
    }
    if(tot<=2) return ;
    memset(cntcol,0,sizeof(cntcol));
    for(int i=1;i<=N;++i)
        for(int j=1;j<=M;++j)
        {
            if(vis[i][j]) mat[i][j]='.';
            if(mat[i][j]!='.') cntcol[j]++;
        }
    for(int j=1;j<=M;++j)
    {
        for(int i=N-1;i>=1;--i)
        {
            if(mat[i][j]=='.') continue;
            x=i;
            while(x+1<=N&&mat[x+1][j]=='.')
            {
                mat[x+1][j]=mat[x][j];
                mat[x][j]='.';
                x++;
            }
        }
    }
    //ptmat();
    for(int j=2;j<=M;++j)
    {
        if(cntcol[j]&&(!cntcol[j-1]))
        {
            int k=j-1;
            while(k-1>=1&&(!cntcol[k-1])) k--;
            swap(cntcol[k],cntcol[j]);
            for(int i=1;i<=N;++i)
                swap(mat[i][j],mat[i][k]);
        }
    }
   // ptmat();
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    while(~scanf("%d",&t))
    {
        if(t==0) break;
        for(int i=1;i<=N;++i)
            scanf("%s",mat[i]+1);
        //ptmat();
        int x,y;
        char str[5];
        while(t--)
        {
            scanf("%s%d",str,&x);
            x=13-x;
            y=str[0]-'a'+1;
            changes(x,y);
        }
        int ans=0;
        for(int i=1;i<=N;++i)
            for(int j=1;j<=M;++j)
                if(mat[i][j]!='.') ans++;
        printf("%d\n",ans);
    }
    return 0;
}
