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
const int maxn=200+10;
const int maxm=50000+10;
bool vis[maxn][maxm];
int colors[10],n,m,q;
int parents[maxn][maxm];
struct Node
{
    int type,x,y,r,l,w,c;
}node[50010];
int Find(int x,int k)
{
    return parents[k][x]==x?x:parents[k][x]=Find(parents[k][x],k);
}
void covers(int k,int l,int r,int c)
{
    int fa;
    int tmp=Find(l,k);
    for(int i=r;i>=l;i=fa-1)
    {
        fa=Find(i,k);
        if(!vis[k][fa])
        {
            vis[k][fa]=true;
            colors[c]++;
        }
        if(tmp!=fa) parents[k][i]=tmp;
    }
}
void solve(Node nd)
{
    int add,l,r;
    if(nd.type==0||nd.type==1)
    {
        add=0;
        while(true)
        {
            int tmp;
            if(add>nd.r) break;
            if(!nd.type)
                tmp=(int)sqrt((double)nd.r*nd.r-(double)add*add+1e-8);
            else
                tmp=nd.r-add;
            if(nd.y-add<0&&nd.y+add>=n) break;
            l=nd.x-tmp;r=tmp+nd.x;
            if(l<0) l=0;
            if(r>=m) r=m-1;
            if(nd.y-add>=0)
              covers(nd.y-add,l,r,nd.c);
            if(tmp!=nd.r&&nd.y+add<n)
              covers(nd.y+add,l,r,nd.c);
            add++;
        }
    }
    else if(nd.type==2)
    {
        l=nd.x;r=nd.x+nd.w-1;
        if(r>=m) r=m-1;
        for(int i=nd.y;i<=nd.y+nd.l-1;++i)
        {
            if(i>=n) break;
            covers(i,l,r,nd.c);
        }
    }
    else
    {
        add=(nd.w+1)/2;
        for(int i=0;i<add;++i)
        {
            int y=nd.y+i;
            if(y>=n) break;
            l=nd.x-add+1+i;
            r=nd.x+add-1-i;
            if(l<0) l=0;
            if(r>=m) r=m-1;
            covers(y,l,r,nd.c);
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    char str[15];
    while(~scanf("%d%d%d",&n,&m,&q))
    {
        memset(vis,0,sizeof(vis));
        memset(colors,0,sizeof(colors));
        for(int i=0;i<=n;++i)
          for(int j=0;j<=m;++j)
            parents[i][j]=j;
        for(int i=0;i<q;++i)
        {
            scanf("%s",str);
            if(str[0]=='C')
            {
                scanf("%d%d%d%d",&node[i].y,&node[i].x,&node[i].r,&node[i].c);
                node[i].type=0;
            }
            else if(str[0]=='D')
            {
                scanf("%d%d%d%d",&node[i].y,&node[i].x,&node[i].r,&node[i].c);
                node[i].type=1;
            }
            else if(str[0]=='R')
            {
                scanf("%d%d%d%d%d",&node[i].y,&node[i].x,&node[i].l,&node[i].w,&node[i].c);
                node[i].type=2;
            }
            else
            {
                scanf("%d%d%d%d",&node[i].y,&node[i].x,&node[i].w,&node[i].c);
                node[i].type=3;
            }
        }
        for(int i=q-1;i>=0;--i)
          solve(node[i]);
        printf("%d",colors[1]);
        for(int i=2;i<=9;++i)
          printf(" %d",colors[i]);
        printf("\n");
    }
    return 0;
}
