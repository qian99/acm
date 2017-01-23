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
const int maxn=70+10;
ll dp[maxn];
ll f(int k)
{
    if(k==0) return 1;
    if(k==2) return 1;
    if(dp[k]>=0) return dp[k];
    dp[k]=0;
    for(int i=2;i<=k;i+=2)
      dp[k]+=f(i-2)*f(k-i);
    return dp[k];
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    memset(dp,0xff,sizeof(dp));
    int k;
    while(cin>>k)
    {
        ll ans=f(k*2);
        cout<<ans<<" "<<k+1<<endl;
    }
    return 0;
}
