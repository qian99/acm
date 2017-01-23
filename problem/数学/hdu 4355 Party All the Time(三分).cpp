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
const int maxn=50000+10;
struct Node
{
    double x,w;
    void read()
    {
        scanf("%lf%lf",&x,&w);
    }
}node[maxn];
int n;
double cal(double pos)
{
    double ans=0,tmp;
    for(int i=0;i<n;++i)
    {
        tmp=fabs(pos-node[i].x);
        ans+=tmp*tmp*tmp*node[i].w;
    }
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        scanf("%d",&n);
        double L=1e6,R=-1e6,m1,m2;
        for(int i=0;i<n;++i)
        {
            node[i].read();
            L=min(L,node[i].x);
            R=max(R,node[i].x);
        }
        while(fabs(R-L)>1e-5)
        {
            m1=L+(R-L)/3;
            m2=R-(R-L)/3;
            if(cal(m1)+eps<cal(m2)) R=m2;
            else L=m1;
        }
        printf("Case #%d: %.0f\n",tcase,cal(L));
    }
    return 0;
}
