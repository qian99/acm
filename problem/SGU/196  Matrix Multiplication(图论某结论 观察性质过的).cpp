#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=10000+10;
const int maxm=100000+10;
int d[maxn],u[maxm],v[maxm];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    scanf("%d%d",&n,&m);
    memset(d,0,sizeof(d));
    for(int i=0;i<m;++i)
    {
        scanf("%d%d",&u[i],&v[i]);
        d[u[i]]++;d[v[i]]++;
    }
    ll ans=0;
    for(int i=0;i<m;++i)
      ans+=d[u[i]]+d[v[i]];
    printf("%lld\n",ans);
    return 0;
}

