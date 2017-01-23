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
const int maxn = 200000+10;
vector<int>fac[maxn];
int n,m;
void Init()
{
    for(int i = 2;i < maxn;++i)
    {
        if(fac[i].size() > 0) continue;
        for(int j = i ;j < maxn;j += i)
            fac[j].push_back(i);
    }
}
ll f[maxn];
inline ll sum(int n)
{
    ll res = 0;
    for(int i = n;i > 0;i -= i&-i)
        res += f[i];
    return res;
}
inline void add(int x,ll v)
{
    for(int i = x;i <= n;i += i&-i)
        f[i] += v;
}
inline void reads(int &x) {
    char c; bool sign = false;
    for (c = getchar(); c<'0' || c>'9'; c = getchar()) if (c=='-') sign = true;
    for (x = 0; c>='0' && c<='9'; c = getchar()) x = (x<<3)+(x<<1)+c-'0';
    sign && (x=-x);
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    Init();
    int tcase = 0;
    while(~scanf("%d%d",&n,&m))
    {
        if(n == 0 && m == 0) break;
        for(int i = 0;i <= n;++i) f[i] = 0;
        printf("Case #%d:\n",++tcase);
        int type,N,d,v;
        while(m--)
        {
//            scanf("%d",&type);
            reads(type);
            if(type == 1)
            {
                reads(N);reads(d);reads(v);
//                scanf("%d%d%d",&N,&d,&v);
                if(N % d) continue;
                int M = N/d;
                int size = fac[M].size();
                int val,cnt;
                for(int i = 0;i < (1<<size);++i)
                {
                    val = 1; cnt = 0;
                    for(int j = 0;j < size;++j)
                        if(i & (1<<j))
                        {
                            val *= fac[M][j];
                            cnt ^= 1;
                        }
                    if(cnt) add(val*d,-v);
                    else add(val*d,v);
                }
            }
            else
            {
//                scanf("%d",&N);
                reads(N);
                ll ans = 0,lastv = 0;
                int next;
                for(int i = 1;i <= N;++i)
                {
                    next = N/(N/i);
                    ans += (sum(next) - lastv)*(N/i);
                    lastv = sum(next);
                    i = next;
                }
                printf("%I64d\n",ans);
            }
        }
    }
    return 0;
}
