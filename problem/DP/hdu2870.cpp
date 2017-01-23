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
int lf[maxn][maxn],rn[maxn][maxn],up[maxn][maxn];
char ac[maxn][maxn];
const char cc[7]={'a','b','c','w','x','y','z'};
int m,n;
bool check(char a,char b)
{
    if(a==b) return true;
    if(a=='w'&&(b=='a'||b=='b')) return true;
    if(a=='x'&&(b=='b'||b=='c')) return true;
    if(a=='y'&&(b=='a'||b=='c')) return true;
    if(a=='z'&&(b=='a'||b=='b'||b=='c')) return true;
    return false;
}
int sovle(char a)
{
    int i,j,ans=0;
    for(i=1;i<=m;++i)
    {
        for(j=1;j<=n;++j)
        {
            if(check(ac[i][j],a))
              up[i][j]=up[i-1][j]+1;
            else
              up[i][j]=0;
        }
    }
    int lo=0,ro=0;
    for(i=1;i<=m;++i)
    {
        lo=0;
        for(j=1;j<=n;++j)
        {
            if(check(ac[i][j],a))
               lf[i][j]=(i==1)?lo+1:max(lf[i-1][j],lo+1);
            else
            {
                lf[i][j]=0;
                lo=j;
            }
        }
    }
    for(i=1;i<=m;++i)
    {
        ro=n+1;
        for(j=n;j>=1;--j)
        {
            if(check(ac[i][j],a))
              rn[i][j]=(i==1)?ro-1:min(rn[i-1][j],ro-1);
            else
            {
                ro=j;
                rn[i][j]=n;
            }
            ans=max(ans,up[i][j]*(rn[i][j]-lf[i][j]+1));
        }
    }
    return ans;
}
int main()
{
    memset(lf,0,sizeof(lf));
    while(~scanf("%d%d",&m,&n))
    {
        for(int i=1;i<=m;++i)
        {
            scanf("%s",ac[i]+1);
        }
        int ans=0;
        for(int i=0;i<7;++i)
           ans=max(ans,sovle(cc[i]));
        printf("%d\n",ans);
    }
    return 0;
}
