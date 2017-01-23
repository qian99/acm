#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<map>
#include<queue>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=50000+10;
ll num[maxn],dpa[maxn],dpo[maxn],dpx[maxn];
void opw(int n)
{
    dpa[0]=dpo[0]=dpx[0]=0;
    int u=0,v=0,b=0;
    for(int i=1;i<=n;++i)
    {
        if(num[i]&1)
        {
            u++;
            dpa[i]=dpa[i-1]+u;
            dpo[i]=dpo[i-1]+i;
            dpx[i]=dpx[i-1]+i-v;
            v=i-v;
            b=i;
        }
        else
        {
            u=0;
            dpa[i]=dpa[i-1];
            dpo[i]=dpo[i-1]+b;
            dpx[i]=dpx[i-1]+v;
        }
        num[i]=num[i]>>1;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        scanf("%d",&n);
        ll maxnum=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%I64d",&num[i]);
            maxnum=max(maxnum,num[i]);
        }
        ll p=1,ans1=0,ans2=0,ans3=0;
        while(true)
        {
            opw(n);
            ans1+=dpa[n]*p;
            ans2+=dpo[n]*p;
            ans3+=dpx[n]*p;
            p=p<<1;
            maxnum=maxnum>>1;
            if(maxnum==0) break;
        }
        double res1=(double)ans1/(((ll)n*(n+1))/2);
        double res2=(double)ans2/(((ll)n*(n+1))/2);
        double res3=(double)ans3/(((ll)n*(n+1))/2);
        printf("Case #%d: %.6lf %.6lf %.6lf\n",tcase,res1,res2,res3);
    }
    return 0;
}
