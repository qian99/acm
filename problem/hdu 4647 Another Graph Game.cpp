#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<vector>
#define inf 2139062143
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100000+10;
ll val[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        ll tmp;
        for(int i=1;i<=n;++i)
        {
            scanf("%I64d",&tmp);
            val[i]=tmp*2;
        }
        int u,v;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%I64d",&u,&v,&tmp);
            val[u]+=tmp;
            val[v]+=tmp;
        }
        sort(val+1,val+n+1);
        ll ans=0;
        for(int i=n;i>0;--i)
        {
            if(i&1) ans-=val[i];
            else ans+=val[i];
        }
        printf("%I64d\n",ans/2);
    }
    return 0;
}
