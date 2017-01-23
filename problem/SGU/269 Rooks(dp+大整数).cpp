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
#include<bitset>
#include<set>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=255;
const int N=10000;
struct BigInt
{
    ll num[150];
    int len;
    void clear()
    {
        memset(num,0,sizeof(num));
        len=1;
    }
    void getBigInt(int n)
    {
        clear();
        num[0]=n;
    }
    BigInt operator + (const BigInt & a) const
    {
        BigInt c;
        c.clear();
        c.len=max(a.len,len);
        for(int i=0;i<c.len;++i)
            c.num[i]=num[i]+a.num[i];
        for(int i=0;i<c.len;++i)
            if(c.num[i]>=N) {c.num[i+1]+=c.num[i]/N;c.num[i]%=N;}
        while(c.num[c.len])
        {
            c.num[c.len+1]+=c.num[c.len]/N;
            c.num[c.len]%=N;
            c.len++;
        }
        return c;
    }
    BigInt operator * (const int & x)
    {
        BigInt c;
        c.clear();
        c.len=len;
        for(int i=0;i<c.len;++i)
            c.num[i]+=num[i]*x;
        for(int i=0;i<c.len;++i)
            if(c.num[i]>=N) {c.num[i+1]+=c.num[i]/N;c.num[i]%=N;}
        while(c.num[c.len])
        {
            c.num[c.len+1]+=c.num[c.len]/N;
            c.num[c.len]%=N;
            c.len++;
        }
        return c;
    }
    void ptBigInt()
    {
        printf("%lld",num[len-1]);
        for(int i=len-2;i>=0;--i)
            printf("%04lld",num[i]);
        printf("\n");
    }
};
BigInt dp[2][maxn];
int b[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;++i)
        scanf("%d",&b[i]);
    sort(b+1,b+n+1);
    for(int i=0;i<=k;++i) dp[0][i].clear();
    dp[0][0].getBigInt(1);b[0]=0;
    for(int i=1;i<=n;++i)
    {
        int p=i&1;
        for(int j=0;j<=k;++j) dp[p][j].clear();
        for(int j=0;j<=k&&b[i]>=j;++j)
        {
            dp[p][j]=dp[p^1][j];
            if(j)
            {
                dp[p][j]=dp[p][j]+(dp[p^1][j-1]*(b[i]-j+1));
            }
        }
    }
    dp[n&1][k].ptBigInt();
    return 0;
}
