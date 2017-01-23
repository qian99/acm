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
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
typedef bitset<72> bt;
const int mod=1000000007;
class FibonacciXor
{
    public:
    ll f[110];
    map<ll,bt>mp;
    bt Xor(bt a,bt b)
    {
        bt c;
        for(int i=0;i<72;++i)
            c[i]=(a[i]!=b[i]);
        return c;
    }
    void Init()
    {
        f[0]=1;f[1]=2;
        for(int i=2;i<72;++i)
            f[i]=f[i-1]+f[i-2];
        mp.clear();
    }
    bt cal(ll x)
    {
        if(x==1) return bt(1);
        if(x==0) return bt(0);
        if(mp.find(x)!=mp.end()) return mp[x];
        bt msk;
        int i=71;
        for(;i>=0;--i)
        {
            if(f[i]<=x)
                break;
        }
        if(x==f[i])
        {
            msk[i]=1;
            return mp[x]=Xor(msk,cal(x-1));
        }
        ll y=(x-f[i]);
        if(y&1) msk[i]=1;
        msk=Xor(msk,cal(y));
        msk=Xor(msk,cal(f[i]));
        return mp[x]=msk;
    }
    int find(long long A, long long B)
    {
        Init();
        bt res=Xor(cal(B),cal(A-1));
        ll val=1,ans=0;
        for(int i=0;i<72;++i)
        {
            if(res.test(i)) ans=(ans+val)%mod;
            val=val*2%mod;
        }
        return (ans%mod+mod)%mod;
    }
};
//int main()
//{
//    //freopen("in.txt","r",stdin);
//    //freopen("out.txt","w",stdout);
//    FibonacciXor xx;
//    ll a,b;
//    cin>>a>>b;
//    cout<<xx.find(a,b)<<endl;
//    return 0;
//}
