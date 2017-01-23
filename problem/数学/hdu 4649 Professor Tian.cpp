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
#define inf 2139062143
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
double dp[30],val[300];
int num[300],op[300];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    int tcase=0;
    while(~scanf("%d",&n))
    {
        tcase++;
        char ss[2];
        for(int i=0;i<=n;++i)
            scanf("%d",&num[i]);
        for(int i=1;i<=n;++i)
        {
            scanf("%s",ss);
            if(ss[0]=='&') op[i]=0;
            else if(ss[0]=='|') op[i]=1;
            else op[i]=2;
        }
        memset(val,0,sizeof(val));
        for(int i=1;i<=n;++i)
        {
            scanf("%lf",&val[i]);
            val[i]=1.0-val[i];
        }
        memset(dp,0,sizeof(dp));
        int temp=num[0];
        int z=0;
        while(temp!=0)
        {
            if(temp&1) dp[z]=1;
            temp=temp>>1;
            z++;
        }
        for(int i=1;i<=n;++i)
        {
            temp=num[i];
            z=0;
            for(;z<=22;++z)
            {
                if(op[i]==0)
                {
                    if(temp&1) dp[z]=dp[z];
                    else dp[z]=dp[z]*(1.0-val[i]);
                }
                else if(op[i]==1)
                {
                    if(temp&1) dp[z]=1.0-(1.0-dp[z])*(1.0-val[i]);
                    else dp[z]=dp[z];
                }
                else
                {
                    if(temp&1) dp[z]=(1.0-dp[z])*val[i]+dp[z]*(1.0-val[i]);
                    else dp[z]=dp[z];
                }
                temp=temp>>1;
            }
        }
        double ans=0;
        int p=1;
        for(int i=0;i<=22;++i)
        {
            ans+=dp[i]*p;
            p*=2;
        }
        printf("Case %d:\n",tcase);
        printf("%.6lf\n",ans);
    }
    return 0;
}
