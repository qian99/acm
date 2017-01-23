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
const int maxn=100000+10;
char str[maxn];
int dp[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(cin>>str)
    {
        int m,n;
        n=strlen(str);
        dp[0]=dp[1]=0;
        for(int i=1;i<n;++i)
        {
            if(str[i]==str[i-1])
            dp[i+1]=dp[i]+1;
            else
            dp[i+1]=dp[i];
        }
        cin>>m;
        int a,b;
        for(int i=0;i<m;++i)
        {
            cin>>a>>b;
            cout<<dp[b]-dp[a]<<endl;
        }
    }
    return 0;
}