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
//const int maxn=300+10;
int dp[15][105][105];
int pw[11]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};
int s[15],p[15];
int k;
int f(int d,int m1,int m2)
{
    if(d==0) return (m1==0&&m2==0)?1:0;
    if(dp[d][m1][m2]>=0) return dp[d][m1][m2];
    dp[d][m1][m2]=0;
    for(int i=0;i<10;++i)
    {
        dp[d][m1][m2]+=f(d-1,((m1-i)%k+k)%k,((m2-i*pw[d-1])%k+k)%k);
    }
    return dp[d][m1][m2];
}
int work(int n)
{
    int u=n,sum=0;
    int m=0;
    if(n==0) s[m++]=0;
    while(n!=0)
    {
        s[m]=n%10;
        sum+=s[m];
        n/=10;
        m++;
    }
    int ans=0;
    for(int i=0;i<m;++i)
    {
        u-=s[i]*pw[i];
        sum-=s[i];
        if(i==0)
        {
            for(int j=0;j<=s[i];++j)
            {
                ans+=f(0,(k-(sum+j)%k)%k,(k-(u+j*pw[i])%k)%k);
            }
        }
        else
        {
            for(int j=0;j<s[i];++j)
            {
                ans+=f(i,(k-(sum+j)%k)%k,(k-(u+j*pw[i])%k)%k);
            }
        }
    }
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,a,b;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d",&a,&b,&k);
        if(k>=100)
        {
            printf("0\n");continue;
        }
        memset(dp,0xff,sizeof(dp));
        printf("%d\n",work(b)-work(a-1));
    }
    return 0;
}

