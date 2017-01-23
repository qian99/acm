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
//ll dp[1<<20][20][2],ans[25];
//void solve()
//{
//    for(int i = 0;i < 20;++i)
//        for(int j = 0;j < 20;++j)
//        {
//            if(i == j) continue;
//            dp[(1<<i)|(1<<j)][j][i < j] = 1;
//        }
//    for(int i = 1;i < (1<<20);++i)
//    {
//        for(int j = 0;j < 20;++j)
//        {
//            for(int k = 0;k < 2;++k)
//            {
//                if(dp[i][j][k] == 0) continue;
//                if(k == 1)
//                for(int x = 0;x < j;++x)
//                    if(!(i & (1<<x)))
//                        dp[i|(1<<x)][x][0] += dp[i][j][k];
//                if(k == 0)
//                for(int x = j + 1;x < 20;++x)
//                    if(!(i & (1<<x)))
//                        dp[i|(1<<x)][x][1] += dp[i][j][k];
//            }
//        }
//    }
//    for(int i = 1;i <= 20;++i)
//    {
//        ans[i] = 0;
//        for(int j = 0;j < 20;++j)
//            ans[i] += dp[(1<<i)-1][j][0] + dp[(1<<i)-1][j][1];
//    }
//    ans[1] = 1;
//}
ll ans[21] = {0LL,1LL,
2LL,
4LL,
10LL,
32LL,
122LL,
544LL,
2770LL,
15872LL,
101042LL,
707584LL,
5405530LL,
44736512LL,
398721962LL,
3807514624LL,
38783024290LL,
419730685952LL,
4809759350882LL,
58177770225664LL,
740742376475050LL};
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
//    memset(dp,0,sizeof(dp));
//
//    for(int i = 1;i <= 20;++i)
//        cout<<ans[i]<<endl;
    int t,tcase;
    scanf("%d",&t);
    while(t--)
    {
        int n;
        scanf("%d%d",&tcase,&n);
        printf("%d %I64d\n",tcase,ans[n]);
    }
    return 0;
}

