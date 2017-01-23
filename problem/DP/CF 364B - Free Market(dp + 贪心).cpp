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
const int maxn = 500000 + 10;
int dp[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,d;
    scanf("%d%d",&n,&d);
    int c;
    dp[0] = 1;
    for(int i = 0;i < n;++i)
    {
        scanf("%d",&c);
        for(int j = 500000;j >= c;--j)
            dp[j] |= dp[j - c];
    }
    int sum = 0,cnt = 0;
    while(true)
    {
        int x = sum + d;
        if(x > 500000) x = 500000;
        while(dp[x] == 0) x--;
        if(x == sum) break;
        sum = x;
        cnt++;
    }
    printf("%d %d\n",sum,cnt);
    return 0;
}
