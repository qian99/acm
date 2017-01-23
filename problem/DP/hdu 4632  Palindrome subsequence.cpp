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
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long LL;
const int mod=10007;
const int maxn=1000+10;
char str[maxn];
int dp[maxn][maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    cin>>t;
    while(t--)
    {
        tcase++;
        cin>>str;
        int n=strlen(str);
        memset(dp,0,sizeof(dp));
        for(int i=0;i<n;++i) dp[i][i]=1;
        for(int i=0;i<n-1;++i)
        {
            int j=0;
            for(int k=i+1;k<n;++j,++k)
            {
                if(j+1==k) dp[j][k]=(str[j]==str[k])+2;
                else
                {
                    dp[j][k]=dp[j+1][k]+dp[j][k-1]-dp[j+1][k-1]+(str[j]==str[k]?dp[j+1][k-1]+1:0);
                    dp[j][k]=(dp[j][k]+mod)%mod;
                }
            }
        }
        cout<<"Case "<<tcase<<": ";
        cout<<dp[0][n-1]<<endl;
    }
    return 0;
}
