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
const int maxn = 100000 + 10;
struct Node
{
    ll gval;
    int l,r;
    Node(ll gval = 0,int l = 0,int r = 0):gval(gval),l(l),r(r){}
};
vector<Node>vt[maxn];
ll a[maxn],ans;
int n;
ll gcd(ll a,ll b) {return b == 0 ? a : gcd(b,a%b);}
void solve()
{
    for(int i = 0;i <= n;++i) vt[i].clear();
    vt[n].push_back(Node(a[n],n,n));
    ans = a[n];
    Node ntmp;
    for(int i = n - 1;i >= 1;--i)
    {
        int size = 1;
        vt[i].push_back(Node(a[i],i,i));
        for(int j = 0;j < (int)vt[i + 1].size();++j)
        {
            ntmp = vt[i+1][j];
            ntmp.gval = gcd(ntmp.gval,a[i]);
            if(ntmp.gval == vt[i][size - 1].gval)
                vt[i][size-1].r = ntmp.r;
            else
                vt[i].push_back(ntmp),size++;
        }
    }
    for(int i = 1;i <= n;++i)
    {
        for(int j = 0;j < (int)vt[i].size();++j)
        {
            ntmp = vt[i][j];
            ans = max(ans,ntmp.gval*(ntmp.r - i + 1));
        }
    }
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(int i = 1;i <= n;++i)
            scanf("%lld",&a[i]);
        solve();
        printf("%lld\n",ans);
    }
    return 0;
}

