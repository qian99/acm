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
const int maxn=100000+10;
const int Size=300+10;
struct Query
{
    int L,R,id;
    bool operator <(const Query &a) const
    {
        if(L/Size!=a.L/Size) return L<a.L;
        return R<a.R;
    }
}querys[maxn];
int c[maxn],num[maxn],n,m;
ll ans[maxn],res;
map<int,int>mp;
inline ll cal(ll x)
{
    return x*x*x;
}
void Add(int x)
{
    res-=cal(c[num[x]]);
    res+=cal(c[num[x]]+1);
    c[num[x]]++;
}
void Dec(int x)
{
    res-=cal(c[num[x]]);
    res+=cal(c[num[x]]-1);
    c[num[x]]--;
}
void solve()
{
    memset(c,0,sizeof(c));
    res=0;
    int l=1,r=0;
    for(int i=0;i<m;++i)
    {
        while(l<querys[i].L) Dec(l++);
        while(l>querys[i].L) Add(--l);
        while(r<querys[i].R) Add(++r);
        while(r>querys[i].R) Dec(r--);
        ans[querys[i].id]=res;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d",&n))
    {
        mp.clear();
        int tmp=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&num[i]);
            if(mp[num[i]]) num[i]=mp[num[i]];
            else num[i]=mp[num[i]]=++tmp;
        }
        scanf("%d",&m);
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&querys[i].L,&querys[i].R);
            querys[i].id=i;
        }
        sort(querys,querys+m);
        solve();
        for(int i=0;i<m;++i)
            printf("%I64d\n",ans[i]);
    }
    return 0;
}
