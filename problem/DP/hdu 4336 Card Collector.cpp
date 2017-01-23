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
const int maxn=20+1;
double dp[1<<maxn],p[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        double ng=0;
        for(int i=0;i<n;++i)
        {
            scanf("%lf",&p[i]);
            ng+=p[i];
        }
        ng=1-ng;
        int N=1<<n;
        dp[N-1]=0;
        for(int s=N-2;s>=0;s--)
        {
            double sum=0;
            dp[s]=1;
            for(int i=0;i<n;++i)
            {
                if(s&(1<<i)) continue;
                dp[s]+=dp[s|(1<<i)]*p[i];
                sum+=p[i];
            }
            dp[s]/=sum;
        }
        printf("%.4lf\n",dp[0]);
    }
    return 0;
}