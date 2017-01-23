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
int v[110];
double dp[10010],w[110];
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        double ps,pt;
        int n,m,va,u=0;
        cin>>ps;
        cin>>n;
        m=0;
        for(int i=1;i<=n;++i)
        {
            cin>>va;
            cin>>pt;
            m+=va;
            w[i]=pt;
            v[i]=va;
        }
        memset(dp,0,sizeof(dp));
        dp[0]=1;
        for(int i=1;i<=n;++i)
        {
            for(int j=m;j>=v[i];--j)
            {
                dp[j]=max(dp[j],dp[j-v[i]]*(1-w[i]));
            }
        }
        int ans=0;
        for(int i=m;i>0;--i)
        {
            if(1-dp[i]-ps<eps)
            {
                ans=i;
                break;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
