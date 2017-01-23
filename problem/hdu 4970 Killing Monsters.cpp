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
const int maxn = 100000+10;
ll sum[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d",&n))
    {
        if(n == 0) break;
        scanf("%d",&m);
        memset(sum,0,sizeof(sum));
        int L,R,D;
        for(int i = 1;i <= m;++i)
        {
            scanf("%d%d%d",&L,&R,&D);
            sum[L] += D;
            sum[R + 1] -= D;
        }
        for(int i = 1;i <= n;++i) sum[i] += sum[i-1];
        for(int i = 1;i <= n;++i) sum[i] += sum[i-1];
        ll Hp;
        int k,x,ans;
        scanf("%d",&k);
        ans = k;
        while(k--)
        {
            scanf("%I64d%d",&Hp,&x);
            if(sum[n] - sum[x-1] >= Hp) ans --;
        }
        printf("%d\n",ans);
    }
    return 0;
}
