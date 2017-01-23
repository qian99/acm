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
double pt[15][2],dis[15][15],dp[15][1<<15];
bool vis[15][1<<15];
int n;
inline double Len(double x1,double y1,double x2,double y2)
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
double f(int x,int state)
{
    if(state==0) return 0;
    if(vis[x][state]) return dp[x][state];
    double &res=dp[x][state]=1e10;
    vis[x][state]=true;
    for(int i=0;i<n;++i)
    {
        if(!(state&(1<<i))) continue;
        res=min(res,f(i,state^(1<<i))+dis[x][i]);
    }
    return res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(int i=0;i<n;++i)
            scanf("%lf%lf",&pt[i][0],&pt[i][1]);
        for(int i=0;i<n;++i)
            for(int j=0;j<n;++j)
                dis[i][j]=Len(pt[i][0],pt[i][1],pt[j][0],pt[j][1]);
        memset(vis,0,sizeof(vis));
        double ans=1e10,tmp;
        for(int i=0;i<n;++i)
            for(int j=(1<<i);j<(1<<n);++j)
            {
                if(!(j&(1<<i))) continue;
                int k=(1<<n)-1-j;
                tmp=f(i,j^(1<<i))+f(i,k);
                ans=min(ans,tmp);
            }
        printf("%.2lf\n",ans);
    }
    return 0;
}