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
const ll mod = 10000000000007LL;
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t,tcase = 0;
    scanf("%d",&t);
    while(t--)
    {
        int L,M,N;
        scanf("%d%d%d",&L,&M,&N);
        int X = L*L;
        int val = X - N + 1;
        ll ans = 0;
        for(int i = 1;i <= N - M + 1;++i)
        {
            ans = (ans + 1)*val%mod;
            val++;
        }
        for(int i = X - M + 2;i <= X;++i)
            ans = ans*i%mod;
        printf("Case %d: %lld\n",++tcase,ans);
    }
    return 0;
}

