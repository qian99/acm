#include <iostream>
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
struct BigInt
{
    int num[50];
    int len;
    void clear()
    {
        for(int i=0;i<50;++i) num[i]=0;
        len=1;
    }
    void getBigInt(ll n)
    {
        clear();
        len=0;
        while(n!=0)
        {
            num[len++]=n%10;
            n/=10;
        }
        if(len==0) len=1;
    }
    void getBigInt(int n)
    {
        ll m=(ll)n;
        getBigInt(m);
    }
    BigInt operator + (const BigInt a)const
    {
        int n=max(len,a.len);
        BigInt c;
        c.clear();
        c.len=0;
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
        c.len=0;
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
        while(c.num[c.len-1]==0&&c.len>1)
           c.len--;
        return c;
    }
};
BigInt dp[70][2][70];
BigInt pp[70];
int nu[100];
BigInt f(int m,int b,int d)
{
    BigInt tp,td;
    tp.clear();
    td.clear();
    if(d<0) return tp;
    tp.getBigInt(m);
    if(d==0) return tp;
    if(d==1)
    {
        td.getBigInt(b==1?1:0);
        return td+pp[d]*tp;
    }
    if(d==2)
    {
        td.getBigInt(b==1?3:1);
        return td+pp[d]*tp;
    }
    if(dp[m][b][d].len>0) return dp[m][b][d];
    dp[m][b][d].clear();
    dp[m][b][d]=dp[m][b][d]+f(m+(b==1?1:0),1,d-1);
    dp[m][b][d]=dp[m][b][d]+f(m,0,d-1);
    return dp[m][b][d];
}
BigInt slove(int n)
{
    int m=0,b=0,d=n;
    BigInt res;
    res.clear();
    //res+=f(0,0,n-1);
    for(int i=0;i<n;++i)
    {
        d--;
        if(nu[i]==1)
        {
            res=res+f(m,0,d);
            m+=(b==1)?1:0;
            b=1;
        }
        else
        {
            b=0;
        }
    }
    BigInt tp;
    tp.getBigInt(m);
    res=res+tp;
    return res;
}
void Init()
{
    ll z=1;
    pp[0].getBigInt(z);
    for(int i=1;i<=63;++i)
    {
        z=z<<1;
        pp[i].getBigInt(z);
    }
    for(int i=0;i<70;++i)
    {
        for(int j=0;j<2;++j)
        {
            for(int k=0;k<70;++k)
            {
                dp[i][j][k].len=-1;
            }
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    Init();
    int tcase=0;
    ll x;
    while(cin>>x)
    {
        if(x<0) break;
        tcase++;
        int len=0;
        while(x!=0)
        {
            nu[len++]=x%2;
            x=x>>1;
        }
        int temp;
        for(int i=0;i<len/2;++i)
        {
            temp=nu[i];
            nu[i]=nu[len-i-1];
            nu[len-i-1]=temp;
        }
        BigInt res=slove(len);
        cout<<"Case "<<tcase<<": ";
        for(int i=res.len-1;i>=0;--i)
           cout<<res.num[i];
        cout<<endl;
    }
    return 0;
}