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
const int maxn=50000+10;
const int Size=255;
struct Querys
{
    int L,R,id;
    bool operator <(const Querys & a) const
    {
        if(L/Size!=a.L/Size) return L<a.L;
        return R<a.R;
    }
}querys[maxn];
int c[maxn],wz[maxn],n,m;
ll ans[maxn][2],res;
ll gcd(ll a,ll b) {return b==0?a:gcd(b,a%b);}
inline ll cal(ll x)
{
    if(x<2) return 0;
    return x*(x-1)/2;
}
void Add(int x)
{
    res-=cal(c[wz[x]]);
    res+=cal(c[wz[x]]+1);
    c[wz[x]]++;
}
void Dec(int x)
{
    res-=cal(c[wz[x]]);
    res+=cal(c[wz[x]]-1);
    c[wz[x]]--;
}
void solve()
{
    memset(c,0,sizeof(c));
    res=0;
    int l=1,r=0,p;
    ll d;
    for(int i=0;i<m;++i)
    {
        while(l<querys[i].L) Dec(l++);
        while(l>querys[i].L) Add(--l);
        while(r<querys[i].R) Add(++r);
        while(r>querys[i].R) Dec(r--);
        p=querys[i].id;
        ans[p][0]=res;
        ans[p][1]=(ll)(r-l+1)*(r-l)/2;
        d=gcd(ans[p][0],ans[p][1]);
        ans[p][0]/=d;ans[p][1]/=d;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
        scanf("%d",&wz[i]);
    for(int i=0;i<m;++i)
    {
        scanf("%d%d",&querys[i].L,&querys[i].R);
        querys[i].id=i;
    }
    sort(querys,querys+m);
    solve();
    for(int i=0;i<m;++i)
        printf("%lld/%lld\n",ans[i][0],ans[i][1]);
    return 0;
}
