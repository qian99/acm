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
const int maxn=100+10;
int dp[maxn],w[maxn],v[maxn],c[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    cin>>t;
    while(t--)
    {
        int n,m;
        cin>>n>>m;
        for(int i=1;i<=m;++i)
          cin>>w[i]>>v[i]>>c[i];
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=m;++i)
        {
            for(int k=1;k<=c[i];++k)
            {
                for(int j=n;j>=w[i];--j)
                {
                    dp[j]=max(dp[j],dp[j-w[i]]+v[i]);
                }
            }
        }
        cout<<dp[n]<<endl;
    }
    return 0;
}
