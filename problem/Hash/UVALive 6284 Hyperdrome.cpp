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
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 300000 + 10;
const int maxm = 1000000 + 3;
struct HashTable
{
    ll val;
    int cnt,next;
    HashTable(){}
    HashTable(ll val,int cnt,int next):val(val),cnt(cnt),next(next){}
}hash[maxm<<2];
int vis[maxm+10];
int tot,id;
void Insert(ll x)
{
    int v = x%maxm;
    if(vis[v] != id)
    {
        vis[v] = id;
        hash[v] = HashTable(x,1,-1);
        return ;
    }
    int p = v;
    while(hash[p].next != -1)
    {
        if(hash[p].val == x)
        {
            hash[p].cnt++;
            return ;
        }
        p=hash[p].next;
    }
    if(hash[p].val == x)
    {
        hash[p].cnt++;
        return ;
    }
    hash[p].next=++tot;
    hash[tot]=HashTable(x,1,-1);
}
int Find(ll x)
{
    int v = x%maxm;
    if(vis[v] != id) return 0;
    if(hash[v].val == x) return hash[v].cnt;
    int p = v;
    while(hash[p].next != -1)
    {
        p = hash[p].next;
        if(hash[p].val == x) return hash[p].cnt;
    }
    return 0;
}
char str[maxn];
map<ll,int>mp;
ll ans,p[255];
inline bool check(ll x)
{
    if(x == 0) return true;
    return (x & (x - 1)) == 0;
}
void solve(int L,int R)
{
    if(L >= R) return ;
    int m = (L + R)>>1;
    id++;
    ll last = p[str[m]];
    Insert(last);
//    mp[last]++;
    for(int i = m - 1;i >= L;--i)
    {
        last ^= p[str[i]];
        if(check(last)) ans++;
        Insert(last);
//        mp[last]++;
    }
    last = 0;
    for(int i = m + 1;i <= R;++i)
    {
        last ^= p[str[i]];
        ans += Find(last);// mp[last];
        for(ll j = 0;j < 52;++j)
        {
            ans += Find(last^(1LL<<j));
        }
    }
    solve(L,m - 1);
    solve(m + 1,R);
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    for(int i = 'a';i <= 'z';++i)
        p[i] = 1LL<<(i - 'a');
    for(int i = 'A';i <= 'Z';++i)
        p[i] = 1LL<<(i - 'A' + 26LL);
    memset(vis,0,sizeof(vis));
    id = 0;
    int n;
    while(~scanf("%d",&n))
    {
        scanf("%s",str);
        id++;
        ans = 0;
        tot = 0;
        ll last = 0;
        for(int i = 0;i < n;++i)
        {
            ans++;
            ans += Find(p[str[i]]^last);
            for(ll j = 0;j < 52;++j)
                ans += Find(p[str[i]]^last^(1LL<<j));
            last ^= p[str[i]];
            Insert(last^p[str[i]]);
        }
        printf("%lld\n",ans);
    }
    return 0;
}
