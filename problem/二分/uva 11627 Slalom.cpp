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
const int maxn=100000+10;
const int maxm=1000000+10;
int x[maxn][2],y[maxn],vh,n;
int skis[maxm];
bool check(int speed)
{
    if(speed==0) return true;
    double now=y[0],l=x[0][0],r=x[0][1];
    double L,R;
    for(int i=1;i<n;++i)
    {
        double times=(double)(y[i]-now)/speed;
        L=l-(double)vh*times;
        R=r+(double)vh*times;
        if(L<x[i][0]) L=x[i][0];
        if(R>x[i][1]) R=x[i][1];
        if(L>R) return false;
        l=L;r=R;
        now=y[i];
    }
    return true;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,W;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d",&W,&vh,&n);
        for(int i=0;i<n;++i)
        {
            scanf("%d%d",&x[i][0],&y[i]);
            x[i][1]=x[i][0]+W;
        }
        int m;
        scanf("%d",&m);
        for(int i=0;i<m;++i)
            scanf("%d",&skis[i]);
        int L=0,R=1e6+1,mid;
        while(R-L>1)
        {
            mid=(L+R)>>1;
            if(check(mid)) L=mid;
            else R=mid;
        }
        int ans=-1;
        for(int i=0;i<m;++i)
            if(skis[i]<=L)
                ans=max(ans,skis[i]);
        if(ans==-1) printf("IMPOSSIBLE\n");
        else printf("%d\n",ans);
    }
    return 0;
}
