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
struct Circle
{
    double x,y,r;
    int color;
    void read()
    {
        scanf("%lf%lf%lf",&x,&y,&r);
        scanf("%d",&color);
    }
}c[25];
int over[25],ans,n;
char dp[1<<24];
double Len(double x1,double y1,double x2,double y2)
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
bool check(Circle a,Circle b)
{
    return a.r+b.r-Len(a.x,a.y,b.x,b.y)>0;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        for(int i=0;i<n;++i)
            c[i].read();
        memset(over,0,sizeof(over));
        for(int i=0;i<n;++i)
            for(int j=0;j<i;++j)
                if(check(c[i],c[j]))
                {
                    over[i]|=(1<<j);
                }
        for(int i=0;i<(1<<n);++i) dp[i]=-1;
        ans=dp[0]=0;
        for(int i=0;i<(1<<n);++i)
        {
            if(dp[i]==-1) continue;
            ans=max(ans,(int)dp[i]);
            for(int j=0;j<n;++j)
            {
                if(((i>>j)&1)||((i&over[j])!=over[j])) continue;
                for(int k=j+1;k<n;++k)
                {
                    if(((i>>k)&1)||((i&over[k])!=over[k])) continue;
                    if(c[j].color!=c[k].color) continue;
                    dp[i|(1<<j)|(1<<k)]=max((int)dp[i|(1<<j)|(1<<k)],dp[i]+2);
                }
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
