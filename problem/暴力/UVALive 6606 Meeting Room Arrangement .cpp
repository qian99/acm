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
const int maxn = 21;
int s[maxn],f[maxn],cnt[1<<20],g[maxn][maxn];
void Init()
{
    memset(cnt,0,sizeof(cnt));
    for(int i = 0;i < (1<<20);++i)
    {
        int x = i;
        while(x)
        {
            cnt[i]++;
            x &= (x-1);
        }
    }
}
bool check(int L1,int R1,int L2,int R2)
{
    if(L2 < R1 && R2 >= R1) return false;
    if(L2 >= L1 && R2 <= R1) return false;
    if(L2 <= L1 && R2 > L1) return false;
    if(L2 <= L1 && R2 >= R1) return false;
    return true;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    Init();
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n = 0;
        while(true)
        {
            scanf("%d%d",&s[n],&f[n]);
            if(s[n] == 0 && f[n] == 0) break;
            n++;
        }
        memset(g,0,sizeof(g));
        for(int i = 0;i < n;++i)
            for(int j = 0;j < n;++j)
                if(check(s[i],f[i],s[j],f[j]))
                    g[i][j] = 1;
        int ans = 0;
        for(int i = (1<<n) - 1;i > 0 ;--i)
        {
            if(ans >= cnt[i]) continue;
            bool flag = true;
            for(int j = 0;j < n && flag;++j)
                if(i & (1<<j))
                for(int k = j + 1;k < n && flag;++k)
                    if(i & (1<<k))
                        if(!g[j][k]) flag = false;
            if(flag) ans = max(ans,cnt[i]);
        }
        printf("%d\n",ans);
    }
    return 0;
}

