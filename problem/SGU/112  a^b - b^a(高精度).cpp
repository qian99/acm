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
const int maxn=200+10;
const int M=1e8;
const int N=8;
struct BigInt
{
    int len;
    ll num[maxn];
    void Init(int x)
    {
        memset(num,0,sizeof(num));
        num[0]=x;
        len=1;
    }
    void mul(int x)
    {
        for(int i=0;i<len;++i)
          num[i]*=x;
        for(int i=0;i<len;++i)
        {
            num[i+1]+=num[i]/M;
            num[i]=num[i]%M;
        }
        while(num[len])
        {
            num[len+1]=num[len]/M;
            num[len]=num[len]%M;
            len++;
        }
    }
    int operator < (const BigInt &b) const
    {
        if(len<b.len) return -1;
        if(len>b.len) return 1;
        for(int i=len-1;i>=0;--i)
          if(num[i]<b.num[i])
            return -1;
          else if(num[i]>b.num[i])
            return 1;
        return 0;
    }
    BigInt operator - (const BigInt &b) const
    {
        BigInt c;
        c.Init(0);
        c.len=len;
        ll jw=0;
        for(int i=0;i<len;++i)
        {
            if(num[i]-jw<b.num[i])
            {
                c.num[i]=num[i]-jw+M-b.num[i];
                jw=1;
            }
            else
            {
                c.num[i]=num[i]-jw-b.num[i];
                jw=0;
            }
        }
        while(!c.num[len-1]) c.len--;
        return c;
    }
    void pinrtnum()
    {
        printf("%lld",num[len-1]);
        int S[10],c;
        ll x;
        for(int i=len-2;i>=0;--i)
        {
            memset(S,0,sizeof(S));
            x=num[i];
            c=0;
            while(x)
            {
                S[c++]=x%10;
                x/=10;
            }
            for(int j=N-1;j>=0;--j)
              printf("%d",S[j]);
        }
        printf("\n");
    }
};
int main()
{
    //freopen("a.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int x,y;
    BigInt a,b,c;
    while(cin>>x>>y)
    {
        a.Init(x);
        b.Init(y);
        for(int i=2;i<=y;++i)
          a.mul(x);
        for(int i=2;i<=x;++i)
          b.mul(y);
        bool neg=false;
        int z=(a<b);
        if(z==0)
        {
            printf("0\n");
            continue;
        }
        if(z<0)
        {
            neg=true;
            c=b-a;
        }
        else c=a-b;
        if(neg) printf("-");
        c.pinrtnum();
    }
    return 0;
}
