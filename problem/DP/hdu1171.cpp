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
const int maxn=300000+10;
bool dp[maxn];
int num[60],v[60];
int main()
{
    int n;
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(cin>>n)
    {
        if(n<0) break;
        int sum=0;
        for(int i=1;i<=n;++i)
        {
            cin>>v[i]>>num[i];
            sum+=v[i]*num[i];
        }
        int m=sum/2;
        memset(dp,false,sizeof(dp));
        dp[0]=true;
        for(int i=1;i<=n;++i)
        {
            int k=1;
            while(k<=num[i]&&k*v[i]<=m)
            {
                for(int j=m;j>=k*v[i];--j)
                {
                    dp[j]=dp[j-k*v[i]];
                }
                k++;
            }
        }
        if(dp[m]&&sum%2==0)
        {
            cout<<m<<" "<<m<<endl;
        }
        else
        {
            int i;
            for(i=m;i>=0;--i)
            {
                if(dp[i]) break;
            }
            cout<<sum-i<<" "<<i<<endl;
        }
    }
    return 0;
}
