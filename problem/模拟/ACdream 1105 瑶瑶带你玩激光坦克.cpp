/*
* this code is made by qian99
* Problem: 1105
* Verdict: Accepted
* Submission Date: 2014-06-14 20:32:38
* Time: 124 MS
* Memory: 6656 KB
*/
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
#include<set>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=1000+10;
const int dirx[4]={-1,1,0,0};
const int diry[4]={0,0,-1,1};
int conv(int dir,char c)
{
    if(c=='/')
    {
        if(dir==0) return 3;
        if(dir==1) return 2;
        if(dir==2) return 1;
        return 0;
    }
    else
    {
        if(dir==0) return 2;
        if(dir==1) return 3;
        if(dir==2) return 0;
        return 1;
    }
}
char mat[maxn][maxn];
bool vis[maxn][maxn][4];
int n,m,sx,sy;
bool check(int x,int y)
{
    return x>=0&&x<n&&y>=0&&y<m&&mat[x][y]!='*';
}
int cal(int dir)
{
    int x=sx,y=sy;
    int cnt=0;
    while(!vis[x][y][dir])
    {
        vis[x][y][dir]=true;
        x=x+dirx[dir];
        y=y+diry[dir];
        if(check(x,y))
        {
            if(mat[x][y]=='/'||mat[x][y]=='\\')
            {
                dir=conv(dir,mat[x][y]);
            }
            else if(mat[x][y]=='E')
            {
                if(!vis[x][y][0]&&!vis[x][y][1]&&!vis[x][y][2]&&!vis[x][y][3])
                    cnt++;
            }
        }
        else break;
    }
    return cnt;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&n,&m))
    {
        for(int i=0;i<n;++i)
        {
            scanf("%s",mat[i]);
            for(int j=0;j<m;++j)
                if(mat[i][j]=='T') {sx=i,sy=j;}
        }
        int ans=0;
        for(int i=0;i<4;++i)
        {
            memset(vis,0,sizeof(vis));
            ans=max(ans,cal(i));
        }
        printf("%d\n",ans);
    }
    return 0;
}