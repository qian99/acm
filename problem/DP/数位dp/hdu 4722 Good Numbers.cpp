#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
ll dp[20][20];
char str[20];
int num[20];
ll f(int x,int y)
{
    if(x==0)
    {
        if(y%10) return 0;
        return 1;
    }
    if(dp[x][y]>=0) return dp[x][y];
    dp[x][y]=0;
    for(int i=0;i<10;++i)
     dp[x][y]+=f(x-1,(y+i)%10);
    return dp[x][y];
}
ll solve(int *a,int n)
{
    int s=n-1;
    int sum=0;
    ll res=0;
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<a[i];++j)
          res+=f(s,(sum+j)%10);
        sum+=a[i];
        s--;
    }
    if(sum%10==0) res++;
    return res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        int len,sum;
        memset(dp,0xff,sizeof(dp));
        ll ans;
        scanf("%s",str);
        len=strlen(str);
        sum=0;
        ans=0;
        for(int i=0;i<len;++i)
        {
            num[i]=(int)(str[i]-'0');
            sum+=num[i];
        }
        ans-=solve(num,len);
        if(sum%10==0) ans++;
        scanf("%s",str);
        len=strlen(str);
        for(int i=0;i<len;++i)
            num[i]=(int)(str[i]-'0');
        ans+=solve(num,len);
        printf("Case #%d: %I64d\n",tcase,ans);
    }
    return 0;
}
