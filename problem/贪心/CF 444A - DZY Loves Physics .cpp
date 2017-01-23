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
const int maxn = 500+10;
int w[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= n;++i)
        scanf("%d",&w[i]);
    int u,v,c;
    double ans = 0;
    for(int i = 0;i < m;++i)
    {
        scanf("%d%d%d",&u,&v,&c);
        ans = max(ans,(double)(w[u]+w[v])/c);
    }
    printf("%.9lf\n",ans);
    return 0;
}
