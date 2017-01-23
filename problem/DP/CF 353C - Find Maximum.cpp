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
const int maxn=100000+10;
int dp[maxn][2],val[maxn];
char str[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(cin>>n)
    {
        memset(val,0,sizeof(val));
        for(int i=1;i<=n;++i)
          cin>>val[i];
        cin>>str;
        dp[n+1][0]=0;dp[n+1][1]=-inf;
        int k;
        for(int i=n;i>=1;--i)
        {
            k=str[i-1]-'0';
            if(k)
            {
                dp[i][0]=dp[i+1][0]+val[i];
                dp[i][1]=max(dp[i+1][0],dp[i+1][1]+val[i]);
            }
            else
            {
                dp[i][0]=dp[i+1][0];
                dp[i][1]=dp[i+1][1]+val[i];
            }
        }
        cout<<max(dp[1][0],dp[1][1])<<endl;
    }
    return 0;
}
