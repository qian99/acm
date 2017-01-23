#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<set>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100000+10;
char str[maxn],s[maxn];
int cnt[maxn];
ll dp[maxn][2];
void cal(int val,ll &even,ll &odd)
{
    if(val==1)
    {
        odd++;
        return ;
    }
    if(val&1)
    {
        ll n=val/2;
        even+=n*(n+1);
        odd+=n+1+(n+1)*n;
    }
    else
    {
        ll n=val/2;
        odd+=n*(n+1);
        even+=n+n*(n-1);
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%s",str);
    int n=strlen(str);
    memset(cnt,0,sizeof(cnt));
    memset(dp,0,sizeof(dp));
    int m=0;
    s[m]=str[0];
    for(int i=0;i<n;++i)
    {
        if(str[i]==s[m]) cnt[m]++;
        else s[++m]=str[i],cnt[m]=1;
    }
    ll even=0,odd=0;
    for(int i=0;i<n;++i)
        cal(cnt[i],even,odd);
    dp[0][0]=cnt[0]/2;
    dp[0][1]=cnt[0]/2+(cnt[0]&1);
    dp[1][0]=cnt[1]/2;
    dp[1][1]=cnt[1]/2+(cnt[1]&1);
    for(int i=2;i<=m;++i)
    {
        int v0=cnt[i]/2;
        int v1=cnt[i]/2+(cnt[i]&1);
        int tmp=cnt[i]+cnt[i-1];
        if(cnt[i-1]&1)
        {
            even+=dp[i-2][0]*v1+dp[i-2][1]*v0;
            odd+=dp[i-2][0]*v0+dp[i-2][1]*v1;
        }
        else
        {
            odd+=dp[i-2][0]*v1+dp[i-2][1]*v0;
            even+=dp[i-2][0]*v0+dp[i-2][1]*v1;
        }
        if(tmp&1)
        {
            dp[i][0]=dp[i-2][1]+v0;
            dp[i][1]=dp[i-2][0]+v1;
        }
        else
        {
            dp[i][0]=dp[i-2][0]+v0;
            dp[i][1]=dp[i-2][1]+v1;
        }
    }
    printf("%I64d %I64d\n",even,odd);
    return 0;
}