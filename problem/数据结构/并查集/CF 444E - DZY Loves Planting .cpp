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
const int maxn = 3000+10;
struct Edge
{
    int u,v,w;
}edges[maxn];
int pa[maxn],size[maxn],sum[maxn],x[maxn],tot,n;
int Find(int x)
{
    return x == pa[x]?x:pa[x] = Find(pa[x]);
}
bool check(int mid)
{
    for(int i = 1 ;i <= n;++i)
    {
        pa[i] = i;
        sum[i] = x[i];
        size[i] = 1;
    }
    for(int i = 0;i < n-1;++i)
    {
        if(edges[i].w >= mid) continue;
        int a = Find(edges[i].u);
        int b = Find(edges[i].v);
        size[a] += size[b];
        sum[a] += sum[b];
        pa[b] = a;
    }
    for(int i = 1;i <= n;++i)
    {
        int a = Find(i);
        if(tot - sum[a] < size[a]) return false;
    }
    return true;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    scanf("%d",&n);
    tot = 0;
    for(int i = 0;i < n-1;++i)
    {
        scanf("%d%d%d",&edges[i].u,&edges[i].v,&edges[i].w);
    }
    for(int i = 1;i <= n;++i)
    {
        scanf("%d",&x[i]);
        tot += x[i];
    }
    int l = 0, r =10001;
    while(r - l > 1)
    {
        int mid = (l+r)>>1;
        if(check(mid)) l = mid;
        else r = mid;
    }
    printf("%d\n",l);
    return 0;
}
