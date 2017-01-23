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
const int maxn=1000+10;
const int mod=1000000000+7;
int dp[2][maxn][40];
int a[40],conv[maxn],b[40][40];
int n,m,k,cnt;
int gcd(int a,int b)
{
    int c;
    while(b!=0)
    {
        c=a%b;
        a=b;
        b=c;
    }
    return a;
}
int lcm(int a,int b)
{
    return a*b/gcd(a,b);
}
void Init()
{
    memset(dp,0,sizeof(dp));
    memset(conv,0xff,sizeof(conv));
    cnt=0;
    for(int i=1;i<=m;++i)
    {
        if(m%i==0)
        {
            a[cnt]=i;
            conv[i]=cnt++;
        }
    }
    int tmp;
    for(int i=0;i<cnt;++i)
      for(int j=0;j<cnt;++j)
      {
          tmp=lcm(a[i],a[j]);
          if(tmp<=m&&conv[tmp]!=-1)
          b[i][j]=conv[tmp];
      }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d%d",&n,&m,&k))
    {
        Init();
        for(int i=0;i<cnt;++i)
          dp[1][a[i]][i]=1;
        int wh,tmp;
        for(int i=2;i<=k;++i)
        {
            wh=i&1;
            for(int j=0;j<=n;++j)
              for(int z=0;z<cnt;++z)
                dp[wh][j][z]=0;
            for(int j=i;j<=n;++j)
            {
                for(int z=0;z<cnt;++z)
                {
                    if(j<a[z]) break;
                    for(int u=0;u<cnt;++u)
                    {
                        tmp=b[z][u];
                        dp[wh][j][tmp]+=dp[wh^1][j-a[z]][u]%mod;
                        dp[wh][j][tmp]%=mod;
                    }
                }
            }
        }
        printf("%d\n",dp[k&1][n][conv[m]]%mod);
    }
    return 0;
}
