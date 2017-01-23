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
const int maxn=1000+10;
struct Node
{
    int x,y,t;
    double p;
    Node(){}
    Node(int x,int y,int t,double p):x(x),y(y),t(t),p(p){}
    bool operator <(const Node &a) const
    {
        return t<a.t;
    }
}node[maxn];
double dp[maxn];
double Dis(double x1,double y1,double x2,double y2)
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n,v;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&v);
        for(int i=1;i<=n;++i)
            scanf("%d%d%d%lf",&node[i].x,&node[i].y,&node[i].t,&node[i].p);
        sort(node+1,node+n+1);
        for(int i=1;i<=n;++i)
        {
            dp[i]=node[i].p;
            for(int j=1;j<i;++j)
            {
                if(Dis(node[i].x,node[i].y,node[j].x,node[j].y)<=(double)v*(node[i].t-node[j].t))
                    dp[i]=max(dp[i],dp[j]+node[i].p);
            }
        }
        double ans=0;
        for(int i=1;i<=n;++i) ans=max(ans,dp[i]);
        printf("%.6lf\n",ans);
    }
    return 0;
}
