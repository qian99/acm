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
//const int maxn=200000+10;
typedef long long ll;
struct BigInt
{
    int num[50];
    int len;
    void clear()
    {
        for(int i=0;i<50;++i) num[i]=0;
        len=0;
    }
    void getBigInt(ll n)
    {
        clear();
        while(n!=0)
        {
            num[len++]=n%10;
            n/=10;
        }
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
};
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ll a,b;
    BigInt aa,bb;
    while(cin>>a>>b)
    {
        aa.getBigInt(a);
        bb.getBigInt(b);
        aa=aa*bb;
        for(int i=aa.len-1;i>=0;--i)
          cout<<aa.num[i];
        cout<<endl;
    }
    return 0;
}
