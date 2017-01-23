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
const int maxn=7;
double dp[7][7][7][7][7][7];
bool vis[7][7][7][7][7][7];
inline double& getx(int a[maxn])
{
    return dp[a[0]][a[1]][a[2]][a[3]][a[4]][a[5]];
}
inline bool& gety(int a[maxn])
{
    return vis[a[0]][a[1]][a[2]][a[3]][a[4]][a[5]];
}
double f(int a[maxn])
{
    int sum=0;
    for(int i=0;i<maxn;++i) sum+=a[i];
    if(sum==0) return 0;
    if(gety(a)) return getx(a);
    gety(a)=true;
    double ans=0,tmp=0;
    int b[maxn];
    for(int k=1;k<=6;++k)
    {
        sum=0;
        for(int i=0;i<6;++i) sum+=(a[i]>=k);
        if(sum==0) break;
        tmp=0;
        for(int i=1;i<=3;++i)
        {
            int z=i;
            for(int j=0;j<6;++j)
            {
                if(a[j]>=k&&z)
                {
                    b[j]=a[j]-1;
                    z--;
                }
                else b[j]=a[j];
            }
            tmp+=1.0/3*(1-f(b));
        }
        ans=max(ans,tmp);
    }
    for(int k=1;k<=6;++k)
    {
        sum=0;
        for(int i=0;i<6;++i) sum+=(a[i]>=k);
        if(sum==0) break;
        tmp=0;
        for(int i=1;i<=3;++i)
        {
            int z=i;
            for(int j=5;j>=0;--j)
            {
                if(a[j]>=k&&z)
                {
                    b[j]=a[j]-1;
                    z--;
                }
                else b[j]=a[j];
            }
            tmp+=1.0/3*(1-f(b));
        }
        ans=max(ans,tmp);
    }
    getx(a)=ans;
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int a[maxn];
    int n;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        memset(a,0,sizeof(a));
        memset(vis,0,sizeof(vis));
        for(int i=0;i<n;++i)
            scanf("%d",&a[i]);
        double ans=f(a);
        printf("%.6lf\n",ans);
    }
    return 0;
}
