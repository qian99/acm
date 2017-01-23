#include <iostream>
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
int dp[40][40][40][40],lf[44][44],ups[44][44];
char a[45][45];
int n,m,q;
int f(int x1,int y1,int x2,int y2)
{
    if(x2<x1||y2<y1) return 0;
    if(x1==x2&&y1==y2) return a[x1][y1]=='0';
    if(dp[x1][y1][x2][y2]!=-1) return dp[x1][y1][x2][y2];
    int& ans=dp[x1][y1][x2][y2];
    ans=0;
    if(a[x2][y2]!='0')
    {
        ans=f(x1,y1,x2-1,y2)+f(x1,y1,x2,y2-1)-f(x1,y1,x2-1,y2-1);
    }
    else
    {
        ans=min(y2-y1+1,lf[x2][y2])+min(x2-x1+1,ups[x2][y2])-1;
        ans+=f(x1,y1,x2-1,y2)+f(x1,y1,x2,y2-1)-f(x1,y1,x2-1,y2-1);
        int xx=max(x1,x2-ups[x2][y2]+1);
        int yy=max(y1,y2-lf[x2][y2]+1);
        for(int j=y2-1;j>=yy;--j)
        {
            for(int i=x2-1;i>=xx;--i)
            {
                if(a[i][j]=='1') {xx=i+1;break;}
                ans++;
            }
            if(xx==x2) break;
        }
    }
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d%d%d",&n,&m,&q);
    for(int i=0;i<n;++i)
        scanf("%s",a[i]);
    for(int i=0;i<n;++i)
    {
        lf[i][0]=(a[i][0]=='0');
        for(int j=0;j<m;++j)
        {
            if(i==0) ups[i][j]=(a[i][j]=='0');
            else ups[i][j]=(a[i][j]=='0')?ups[i-1][j]+1:0;
            if(j) lf[i][j]=(a[i][j]=='0')?lf[i][j-1]+1:0;
        }
    }
    memset(dp,0xff,sizeof(dp));
    int x1,x2,y1,y2;
    while(q--)
    {
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        printf("%d\n",f(x1-1,y1-1,x2-1,y2-1));
    }
    return 0;
}