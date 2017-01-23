#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;

const int maxn=3000;
bool a[255][4];      //0:ÉÏ  1£º×ó 2£ºÏÂ  3£ºÓÒ
const int move[4][2]={{-1,0},{0,-1},{1,0},{0,1}};
//int parent[maxn];
char pipe[55][55];
bool vis[55][55];
//int Find(int x);
//void Uion(int x,int y);
void dfs(int x,int y);
bool check(int sx,int sy,int px,int py,int dir);
int sum,m,n;

int main()
{
    memset(a,0,sizeof(a));
    a['A'][1]=a['A'][0]=a['B'][0]=a['B'][3]=a['C'][1]=a['C'][2]=true;
    a['D'][2]=a['D'][3]=a['E'][0]=a['E'][2]=a['F'][1]=a['F'][3]=true;
    a['G'][1]=a['G'][0]=a['G'][3]=a['H'][0]=a['H'][1]=a['H'][2]=true;
    a['I'][1]=a['I'][2]=a['I'][3]=a['J'][0]=a['J'][2]=a['J'][3]=true;
    a['K'][0]=a['K'][1]=a['K'][2]=a['K'][3]=true;
    while(~scanf("%d%d",&m,&n))
    {
        if(m<0||n<0) break;
        for(int i=0;i<m;++i)
        {
            scanf("%s",pipe[i]);
        }
        sum=0;
        memset(vis,0,sizeof(vis));
        for(int i=0;i<m;++i)
        {
            for(int j=0;j<n;++j)
            {
                if(!vis[i][j])
                {
                    dfs(i,j);
                    sum++;
                }
            }
        }
        printf("%d\n",sum);
    }
    return 0;
}
/*int Find(int x)
{
    if(x!=parent[x])
    {
        parent[x]=Find(parent[x]);
    }
    return parent[x];
}
void Uion(int x,int y)
{
    if(Find(x)!=Find(y))
    {
        sum++;
        parent[y]=x;
        //Find(x);
    }
}*/
void dfs(int x,int y)
{
    if(vis[x][y]) return;
    vis[x][y]=true;
    for(int k=0;k<4;++k)
    {
        int px=x+move[k][0];
        int py=y+move[k][1];
        if(!vis[px][py]&&check(x,y,px,py,k))
        {
            dfs(px,py);
        }
    }
}
bool check(int sx,int sy,int px,int py,int dir)
{
    if(px<0||px>=m||py<0||py>n)
       return false;
    if(dir==0)
    {
        if(a[pipe[sx][sy]][0]&&a[pipe[px][py]][2])
           return true;
    }
    if(dir==1)
    {
        if(a[pipe[sx][sy]][1]&&a[pipe[px][py]][3])
           return true;
    }
    if(dir==2)
    {
        if(a[pipe[sx][sy]][2]&&a[pipe[px][py]][0])
           return true;
    }
    if(dir==3)
    {
        if(a[pipe[sx][sy]][3]&&a[pipe[px][py]][1])
           return true;
    }
    return false;
}
