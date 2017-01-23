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
char a[25][25];
int dp[40][1<<20],n;
bool vis[40][1<<20];
int f(int xx,int st)
{
    if(vis[xx][st]) return dp[xx][st];
    int &res=dp[xx][st];
    vis[xx][st]=true;
    if(xx==n*2-2)
    {
        res=0;
    }
    else
    {
        if(xx&1) res=-inf;
        else res=inf;
        int mask[30];
        memset(mask,0,sizeof(mask));
        int cnt=0;
        for(int j=0;j<=xx+1;++j)
        {
            int x=xx+1-j;
            int y=j;
            if(x>=n||y>=n) continue;
            mask[a[x][y]-'a']|=(1<<cnt);
            cnt++;
        }
        for(int i=0;i<26;++i)
        {
            if(mask[i])
            {
                int xt;
                if(xx+1<n) xt=(st|(st<<1))&mask[i];
                else xt=(st|(st>>1))&mask[i];
                if(xt==0) continue;
                int tmp=0;
                if(i==0) tmp=1;
                else if(i==1) tmp=-1;
                if(xx&1) res=max(res,tmp+f(xx+1,xt));
                else res=min(res,tmp+f(xx+1,xt));
            }
        }
    }
    if(xx==0)
    {
        if(a[0][0]=='a') res+=1;
        else if(a[0][0]=='b') res-=1;
    }
    return res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d",&n))
    {
        for(int i=0;i<n;++i)
          scanf("%s",a[i]);
        memset(vis,0,sizeof(vis));
        int res=f(0,1);
        if(res==0) printf("DRAW\n");
        else if(res>0) printf("FIRST\n");
        else printf("SECOND\n");
    }
    return 0;
}
