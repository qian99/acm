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
int a[15],b[5][5],c[5][5];
int n;
void change(int p,int v)
{
    int x,y,z;
    x=p/n-1;
    y=p%n;
    z=x*n+y;
    if(x>=0)
    {
        c[x][y]+=(a[p]>a[z]?v:0);
        c[p/n][p%n]+=(a[z]>a[p]?v:0);
    }
    x=p/n;
    y=p%n-1;
    z=x*n+y;
    if(y>=0)
    {
        c[x][y]+=(a[p]>a[z]?v:0);
        c[p/n][p%n]+=(a[z]>a[p]?v:0);
    }
}
bool canset(int p)
{
    int x,y;
    x=p/n-1;
    y=p%n-1;
    if(x>=0&&y>=0)
    {
        if(c[x][y]!=b[x][y]) return false;
    }
    if(p%n==n-1)
    {
        x=p/n-1;
        y=p%n;
        if(x>=0&&y>=0)
        {
            if(c[x][y]!=b[x][y]) return false;
        }
    }
    if(p/n==n-1)
    {
        x=p/n;
        y=p%n-1;
        if(x>=0&&y>=0)
        {
            if(c[x][y]!=b[x][y]) return false;
        }
    }
    if(p==n*n-1)
    {
        if(c[p/3][p%3]!=b[p/3][p%3]) return false;
    }
    return true;
}
bool dfs(int p)
{
    if(p==n*n)
    {
        return true;
    }
    for(int i=0;i<=9;++i)
    {
        a[p]=i;
        change(p,1);
        if(canset(p))
        {
            if(dfs(p+1)) return true;
        }
        change(p,-1);
    }
    return false;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d",&n);
    for(int i=0;i<n;++i)
      for(int j=0;j<n;++j)
        scanf("%d",&b[i][j]);
    memset(c,0,sizeof(c));
    bool flag=dfs(0);
    if(n==1&&b[0][0]!=0) flag=false;
    if(flag)
    {
        for(int i=0;i<n;++i)
        {
            printf("%d",a[i*n]);
            for(int j=1;j<n;++j)
              printf(" %d",a[i*n+j]);
            printf("\n");
        }
    }
    else printf("NO SOLUTION\n");
    return 0;
}
