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
typedef unsigned long long ull;
const int maxn = 400 + 10;
const int M = 51;
short ans[200010][52];
ull f[200010];
int W[maxn],T[maxn];
map<ull,int>mp;
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    for(int i = 1;i <= M + 1;++i)
        mp[1LL<<(i-1LL)] = i;
    int t,n,q;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&q);
        memset(ans,0,sizeof(ans));
        memset(f,0,sizeof(f));
        f[0] = 1;
        ull v,x;
        for(int i = 1;i <= n;++i)
        {
            scanf("%d%d",&W[i],&T[i]);
            for(int j = 200000;j >= T[i];--j)
            {
                v = f[j];
                f[j] |= (f[j - T[i]]<<W[i]) & ((1LL<<M+1) - 1);
                for(ull k = v ^ f[j];k ; k &= k-1)
                {
                    x = (k ^ (k - 1)) & k;
                    ans[j][mp[x] - 1] = i;
                }

            }
        }
        int m,s,p;
        for(int i = 0;i < q;++i)
        {
            scanf("%d%d",&m,&s);
            if(!ans[s][m])
                puts("No solution!");
            else
            {
                printf("%d",ans[s][m]);
                p = ans[s][m];
                m -= W[p];
                s -= T[p];
                while(m)
                {
                    p = ans[s][m];
                    printf(" %d",p);
                    m -= W[p];
                    s -= T[p];
                }
                puts("");
            }
        }
    }
    return 0;
}
