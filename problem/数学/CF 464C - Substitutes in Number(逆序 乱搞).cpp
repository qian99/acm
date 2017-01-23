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
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 100000 + 10;
const int mod = 1e9 + 7;
char str[maxn];
struct Node
{
    int c;
    string token;
}node[maxn];
struct Num
{
    ll val,bit;
}num[11];
string s;
ll pow_mod(ll x,ll n)
{
    ll res = 1;
    while(n)
    {
        if(n & 1) res = res*x%mod;
        x = x*x%mod;
        n >>= 1;
    }
    return res;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    cin>>str;
    int len = strlen(str);
    int m;
    cin>>m;
    for(int i = 0;i < m;++i)
    {
        cin>>s;
//        cout<<s<<endl;
        int slen = s.length();
        node[i].c = s[0] - '0';
        node[i].token = "";
        int j = 3;
        while(j < slen)
        {
//            cout<<s[j]<<endl;
            node[i].token += s[j++];
        }
//        cout<<node[i].token<<endl;
    }
    for(int i = 0;i < 10;++i)
        num[i].val = i,num[i].bit = 10;
    for(int i = m - 1;i >= 0;--i)
    {
        int c = node[i].c,x;
        int slen = node[i].token.length();
        ll vnow = 0,bnow = 1;
        for(int j = slen - 1; j >= 0;--j)
        {
            x = node[i].token[j] - '0';
            vnow += num[x].val*bnow%mod;
            vnow %= mod;
            bnow *= num[x].bit;
            bnow %= mod;
        }
        num[c].val = vnow;
        num[c].bit = bnow;
    }
    ll ans = 0,bl = 1,x;
    for(int j = len - 1; j >= 0;--j)
    {
        x = str[j] - '0';
        ans += num[x].val*bl%mod;
        ans %= mod;
        bl *= num[x].bit;
        bl %= mod;
    }
    printf("%I64d\n",ans);
    return 0;
}