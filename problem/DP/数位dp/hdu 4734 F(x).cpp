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
const int maxn=30000+10;
int dp[maxn][15];
int p[15],a[15];
int f(int x,int y)
{
    if(y==0)
    {
        if(x>=0) return 1;
        return 0;
    }
    if(x<0) return 0;
    if(dp[x][y]>=0) return dp[x][y];
    dp[x][y]=0;
    for(int i=0;i<10;++i)
      dp[x][y]+=f(x-i*p[y-1],y-1);
    return dp[x][y];
}
int solve(int x,int len)
{
    int s=len-1;
    int sum=x;
    int ans=0;
    for(int i=0;i<len;++i)
    {
        for(int j=0;j<a[i];++j)
          ans+=f(sum-j*p[s],s);
        sum-=a[i]*p[s];
        s--;
    }
    if(sum>=0) ans++;
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    for(int i=0;i<15;++i) p[i]=1<<i;
    memset(dp,0xff,sizeof(dp));
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        int A,B;
        scanf("%d%d",&A,&B);
        int v=0,k=0,len=0;
        while(A!=0)
        {
            v+=(A%10)*p[k];
            A/=10;
            k++;
        }
        while(B!=0)
        {
            a[len++]=B%10;
            B/=10;
        }
        for(int i=0;i<len/2;++i)
        {
            k=a[i];
            a[i]=a[len-i-1];
            a[len-i-1]=k;
        }
        int ans=solve(v,len);
        printf("Case #%d: %d\n",tcase,ans);
    }
    return 0;
}
