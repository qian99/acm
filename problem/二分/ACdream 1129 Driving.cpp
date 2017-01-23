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
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100000+10;
double s[maxn],b[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        double f,v;
        scanf("%lf%lf",&f,&v);
        for(int i=0;i<n;++i)
            scanf("%lf%lf",&s[i],&b[i]);
        double L=0,R=v,mid;
        double ans=1e30;
        bool flag=false;
        while(R-L>eps)
        {
            mid=(L+R)/2;
            double cost=0,t=0;
            for(int i=0;i<n;++i)
            {
                if(0.5*mid+b[i]>=eps)
                {
                    cost+=(0.5*mid+b[i])*s[i];
                    t+=s[i]/mid;
                }
                else
                {
                    t+=s[i]/min(v,-b[i]/0.5);
                }
            }
            if(cost<=f)
            {
                ans=min(t,ans);
                flag=true;
                L=mid;
            }
            else R=mid;
        }
        if(flag) printf("%.3lf\n",ans);
        else printf("Bad Luck!\n");
    }
    return 0;
}
