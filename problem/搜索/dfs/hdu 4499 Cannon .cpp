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
int a[7][7],n,m,maxv;
void getxy(int x,int y,int &dx,int &dy)
{
    dx=x;dy=y;
    dy++;
    if(dy==m) dx++,dy=0;
}
bool check(int x,int y)
{
    a[x][y]=2;
    bool flag=true;
    int i=0;
    for(int j=0;j<n;++j)
    {
        if(a[j][y]==2)
        {
            i=j+1;
            while(i<n&&a[i][y]==0) i++;
            if(i!=n)
            {
                i++;
                while(i<n&&a[i][y]==0) i++;
                if(i<n&&a[i][y]==2) flag=false;
            }
        }
    }
    for(int j=0;j<m;++j)
    {
        if(a[x][j]==2)
        {
            i=j+1;
            while(i<m&&a[x][i]==0) i++;
            if(i!=m)
            {
                i++;
                while(i<m&&a[x][i]==0) i++;
                if(i<m&&a[x][i]==2) flag=false;
            }
        }
    }
    a[x][y]=0;
    return flag;
}
void dfs(int x,int y,int cnt)
{
    if(x==n)
    {
        maxv=max(maxv,cnt);
        return ;
    }
    int dx,dy;
    getxy(x,y,dx,dy);
    dfs(dx,dy,cnt);
    if(a[x][y]!=1&&check(x,y))
    {
        a[x][y]=2;
        dfs(dx,dy,cnt+1);
        a[x][y]=0;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int q;
    while(~scanf("%d%d%d",&n,&m,&q))
    {
        memset(a,0,sizeof(a));
        int x,y;
        while(q--)
        {
            scanf("%d%d",&x,&y);
            a[x][y]=1;
        }
        maxv=0;
        dfs(0,0,0);
        printf("%d\n",maxv);
    }
    return 0;
}
