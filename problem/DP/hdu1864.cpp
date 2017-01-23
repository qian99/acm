#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
double dp[50],v[50];
struct Data
{
    double price;
    char type;
};
Data Fapiao[2050];
double Check(int m)
{
    double sum=0,ans=0;
    double a=0,b=0,c=0;
    for(int i=0;i<m;++i)
    {
        if(600.0-Fapiao[i].price<0||600.0-a<0||600.0-b<0||600.0-c<0) return -1;
        sum+=Fapiao[i].price;
        if(Fapiao[i].type=='A')
        {
            a+=Fapiao[i].price;
            ans+=Fapiao[i].price;
        }
        else if(Fapiao[i].type=='B')
        {
            b+=Fapiao[i].price;
            ans+=Fapiao[i].price;
        }
        else if(Fapiao[i].type=='C')
        {
            c+=Fapiao[i].price;
            ans+=Fapiao[i].price;
        }
        else
        {
            return -1;
        }
    }
    if(1000.0-sum<0) return -1;
    return ans;
}
int main()
{
    double q;
    int n;
    while(~scanf("%lf%d",&q,&n))
    {
        if(n==0) break;
        int m,t=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&m);
            for(int i=0;i<m;++i)
            {
                scanf(" %c:%lf",&Fapiao[i].type,&Fapiao[i].price);
            }
            double ptemp=Check(m);
            if(ptemp>0)
            {
                v[++t]=ptemp;
            }
        }
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=t;++i)
        {
            for(int j=t;j>=1;--j)
               dp[j]=max(dp[j],dp[j-1]+v[i]);
        }
        double ans=0;
        for(int i=t;i>0;--i)
        {
            if(q-dp[i]>=0)
            {
                ans=dp[i];
                break;
            }
        }
        printf("%.2lf\n",ans);
    }
    return 0;
}
