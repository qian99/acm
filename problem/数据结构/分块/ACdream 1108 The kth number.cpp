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
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100000+10;
const int SIZE=355;
struct Query
{
    int L,R,k,id;
    Query(int L=0,int R=0,int k=0,int id=0):L(L),R(R),k(k),id(id){}
    bool operator <(const Query &a) const
    {
        if(L/SIZE!=a.L/SIZE) return L<a.L;
        return R<a.R;
    }
}querys[maxn];
int a[maxn],num[maxn],sum[maxn],ans[maxn],n,m;
inline void Add(int pos)
{
    sum[++num[a[pos]]]++;
}
inline void Dec(int pos)
{
    sum[num[a[pos]]--]--;
}
int f(int k)
{
    int l=0,r=maxn;
    while(r-l>1)
    {
        int mid=(l+r)>>1;
        if(sum[mid]>=k) l=mid;
        else r=mid;
    }
    return l;
}
void solve()
{
    memset(sum,0,sizeof(sum));
    memset(num,0,sizeof(num));
    int l=1,r=0;
    for(int i=0;i<m;++i)
    {
        while(r<querys[i].R) Add(++r);
        while(l>querys[i].L) Add(--l);
        while(l<querys[i].L) Dec(l++);
        while(r>querys[i].R) Dec(r--);
        ans[querys[i].id]=f(querys[i].k);
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i)
            scanf("%d",&a[i]);
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&querys[i].L,&querys[i].R,&querys[i].k);
            querys[i].id=i;
        }
        sort(querys,querys+m);
        solve();
        for(int i=0;i<m;++i)
            printf("%d\n",ans[i]);
    }
    return 0;
}