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
const int maxn=100+10;
struct BigInt
{
    int num[maxn],len;
    void clear()
    {
        for(int i=0;i<maxn;++i) num[i]=0;
        len=0;
    }
    void Init(int x)
    {
        memset(num,0,sizeof(num));
        num[0]=x;len=1;
    }
     BigInt operator + (const BigInt a)const
    {
        int n=max(len,a.len);
        BigInt c;
        c.clear();
        int jinwei=0;
        int tp;
        for(int i=0;i<n;++i)
        {
            tp=a.num[i]+num[i]+jinwei;
            c.num[c.len++]=tp%10;
            jinwei=tp/10;
        }
        while(jinwei!=0)
        {
            c.num[c.len++]=jinwei%10;
            jinwei/=10;
        }
        return c;
    }
    BigInt operator * (const BigInt a) const
    {
        int m=a.len;
        int n=len;
        BigInt c;
        c.clear();
        int bs=0,w=0,jinwei=0,tp;
        for(int i=0;i<m;++i)
        {
            jinwei=0;
            w=0;
            for(int j=0;j<n;++j)
            {
                tp=a.num[i]*num[j]+jinwei+c.num[bs+w];
                c.num[bs+w]=tp%10;
                jinwei=tp/10;
                w++;
            }
            while(jinwei!=0)
            {
                c.num[bs+w]=jinwei%10;
                jinwei/=10;
                w++;
            }
            c.len=max(c.len,bs+w);
            bs++;
        }
        return c;
    }
    void ptnum()
    {
        for(int i=len-1;i>=0;--i)
            printf("%d",num[i]);
        printf("\n");
    }
}dp[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    for(int i=0;i<maxn;++i) dp[i].Init(0);
    dp[0].Init(1);dp[1].Init(1);
    for(int i=2;i<=100;i++)
    {
        for(int j=1;j<=i;j++)
            dp[i]=dp[i]+dp[j-1]*dp[i-j];
    }
    int n;
    while(cin>>n)
    {
        if(n==-1) break;
        dp[n].ptnum();
    }
    return 0;
}
