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
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
const int maxn=1000+10;
int m,n;
int maze[30][maxn];
int dp[30][maxn];
bool check(int x,int y)
{
    return x>=1&&x<=m&&y>=1&&y<=n;
}
void dfs(int x,int y)
{
    if(x==m&&y==n)
    {
        dp[x][y]=maze[m][n];
        return ;
    }
    if(dp[x][y]!=-1000) return;
    int maxpoint=-1000;
    int px,py;
    px=x+1;
    py=y;
    if(check(px,py))
    {
        dfs(px,py);
        maxpoint=max(maxpoint,dp[px][py]);
    }
    int k=2;
    px=x;
    py=y+1;
    if(check(px,py))
    {
        dfs(px,py);
        maxpoint=max(maxpoint,dp[px][py]);
    }
    while(k*y<=n)
    {
        py=y*k;
        if(check(px,py))
        {
            dfs(px,py);
            maxpoint=max(maxpoint,dp[px][py]);
        }
        k++;
    }
    dp[x][y]=maxpoint+maze[x][y];
}
int main()
{
    int t;
    cin>>t;
    while(cin>>m>>n)
    {
        for(int i=1;i<=m;++i)
        {
            for(int j=1;j<=n;++j)
            {
                cin>>maze[i][j];
                dp[i][j]=-1000;
            }
        }
        dfs(1,1);
        cout<<dp[1][1]<<endl;
    }
    return 0;
}
