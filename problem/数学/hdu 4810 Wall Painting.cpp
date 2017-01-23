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
const int mod=1000000+3;
ll C[maxn][maxn],res[maxn];
int num[35],p[35];
void Init()
{
    for(int i=0;i<32;++i) p[i]=(1<<i)%mod;
    for(int i=0;i<=1000;++i)
    {
        C[i][0]=1;
        C[i][1]=i;
    }
    for(int i=2;i<=1000;++i)
    {
        for(int j=2;j<=i;++j)
          C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
    }
}
void getnum(int x)
{
    int i=0;
    while(x)
    {
        if(x&1) num[i]++;
        x>>=1;
        i++;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    Init();
    int n;
    while(~scanf("%d",&n))
    {
        memset(num,0,sizeof(num));
        int tmp;
        for(int i=0;i<n;++i)
        {
            scanf("%d",&tmp);
            getnum(tmp);
        }
        ll sum;
        for(int i=1;i<=n;++i)
        {
            res[i]=0;
            for(int j=0;j<32;++j)
            {
                sum=0;tmp=min(num[j],i);
                for(int k=1;k<=tmp;k+=2)
                {
                    if(n-num[j]<i-k) continue;
                    sum=(sum+C[num[j]][k]*C[n-num[j]][i-k])%mod;
                }
                res[i]=(res[i]+sum*(p[j]))%mod;
            }
        }
        printf("%I64d",res[1]);
        for(int i=2;i<=n;++i)
          printf(" %I64d",res[i]);
        printf("\n");
    }
    return 0;
}
