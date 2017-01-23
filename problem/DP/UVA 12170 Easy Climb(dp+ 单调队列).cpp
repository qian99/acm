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
const int maxn = 100 + 10;
ll dp[maxn][maxn*maxn*3],val[maxn*maxn*3],h[maxn],d;
int q[maxn*maxn*3],head,fail,tot,n;
inline void Insert(int p,int x)
{
    if(dp[p][x] == -1) return ;
    while(head < fail && dp[p][q[fail-1]] >= dp[p][x]) fail--;
    q[fail++] = x;
}
inline void Remove(int x)
{
    while(head < fail && val[q[head]] < val[x] - d) head++;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%lld",&n,&d);
        tot = 0;
        for(int i = 1;i <= n;++i)
        {
            scanf("%lld",&h[i]);
            for(int j = 0;j < n;++j)
            {
                val[tot++] = h[i] + j*d;
                if(h[i] - j*d >= 0)
                    val[tot++] = h[i] - j*d;
            }
        }
        sort(val,val + tot);
        tot = unique(val,val + tot) - val;
        memset(dp,0xff,sizeof(dp));
        int pos = lower_bound(val,val + tot,h[1]) - val;
        dp[1][pos] = 0;
        for(int i = 2 ;i <= n;++i)
        {
            head = 0;fail = 0;
            pos = 0;
            for(int j = 0;j < tot;++j)
            {
                Remove(j);
                while(pos < tot && val[pos] <= val[j] + d)
                {
                    Insert(i-1,pos);
                    pos++;
                }
                if(head < fail)
                    dp[i][j] = abs(h[i] - val[j]) + dp[i-1][q[head]];
            }
        }
        pos = lower_bound(val,val + tot,h[n]) - val;
        ll ans = dp[n][pos];
        if(ans == -1) puts("impossible");
        else printf("%lld\n",ans);
    }
    return 0;
}
