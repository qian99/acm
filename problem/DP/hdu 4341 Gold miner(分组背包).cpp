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
const int maxn=200+10;
const int maxt=40000+10;
int dp[maxn][maxt];
struct Point
{
    int x,y,t,v;
    bool operator <(const Point & a) const
    {
        if(a.x*y==a.y*x) return y<a.y;
        return a.x*y<a.y*x;
    }
    void read()
    {
        scanf("%d%d%d%d",&x,&y,&t,&v);
    }
};
Point pt[maxn];
vector<int>groups[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,T,tcase=0;
    while(~scanf("%d%d",&n,&T))
    {
        tcase++;
        for(int i=0;i<=n;++i) groups[i].clear();
        int kg=1;
        for(int i=0;i<n;++i)
          pt[i].read();
        sort(pt,pt+n);
        groups[kg].push_back(0);
        for(int i=1;i<n;++i)
        {
            if(pt[i].x*pt[i-1].y==pt[i].y*pt[i-1].x)
            {
                pt[i].t+=pt[i-1].t;
                pt[i].v+=pt[i-1].v;
                groups[kg].push_back(i);
            }
            else groups[++kg].push_back(i);
        }
        memset(dp[0],0,sizeof(dp[0]));
        Point tmp;
        for(int i=1;i<=kg;++i)
        {
            for(int j=0;j<=T;++j)
              dp[i][j]=dp[i-1][j];
            int sz=groups[i].size();
            for(int j=0;j<sz;++j)
            {
                tmp=pt[groups[i][j]];
                for(int k=T;k>=tmp.t;--k)
                  dp[i][k]=max(dp[i][k],dp[i-1][k-tmp.t]+tmp.v);
            }
        }
        printf("Case %d: %d\n",tcase,dp[kg][T]);
    }
    return 0;
}
