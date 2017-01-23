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
const int maxn=100000+10;
int s[maxn],p[maxn];
ll vv[maxn];
int n,m;
int f(int val)
{
    int L=1,R=n;
    if(val>=s[n]) return n;
    int M;
    while(L<R-1)
    {
        M=(L+R)>>1;
        if(s[M]==val) return M;
        if(s[M]>val)
        {
            R=M;
        }
        else
        {
            L=M;
        }
    }
    return L;
}
int main()
{
//    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i)
          scanf("%d%d",&s[i],&p[i]);
        for(int i=0;i<=n;++i) vv[i]=Inf;
        for(int i=n;i>=1;--i)
          vv[i-1]=min(vv[i],(ll)s[i]*p[i]);
        int num;
        ll ans;
        for(int i=0;i<m;++i)
        {
            scanf("%d",&num);
            int pos=f(num);
            if(pos==n) ans=(ll)p[pos]*num;
            else ans=min((ll)p[pos]*num,vv[pos]);
            printf("%lld\n",ans);
        }
    }
    return 0;
}

