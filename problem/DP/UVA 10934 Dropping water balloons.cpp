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
ll dp[110][70];
int main()
{
//    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    memset(dp,0,sizeof(dp));
    for(int i = 1; i <= 63 ; ++i)
        for(int j = 1;j <= 63;++j)
            dp[i][j] = dp[i-1][j-1] + 1 + dp[i][j-1];
    ll k,n;
    while(cin>>k>>n)
    {
        if(k == 0) break;
        k = min(k,63LL);
        if(dp[k][63] < n)
            puts("More than 63 trials needed.");
        else
        {
            int pos = 1;
            for(;pos <= 63;++pos)
                if(dp[k][pos] >= n) break;
            printf("%d\n",pos);
        }
    }
    return 0;
}
