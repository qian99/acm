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
const int maxn = 1000 + 10;
int dp[maxn],ispal[maxn][maxn],n;
char str[maxn];
void precal()
{
    memset(ispal,0,sizeof(ispal));
    for(int i = 0;i < n;++i) ispal[i][i] = 1;
    for(int i = 2;i <= n;++i)
    {
        for(int j = 0;j + i - 1 < n;++j)
        {
            if(str[j] == str[j + i - 1] && (i < 3 ||ispal[j+1][j+i-2]))
                ispal[j][j+i-1] = true;
        }
    }
}
int main()
{
//    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%s",str);
        n = strlen(str);
        precal();
        for(int i = 1;i <= n;++i)
            dp[i] = i;
        dp[0] = 0;
        for(int i = 1;i <= n;++i)
        {
            for(int j = 1;j <= i;++j)
            {
                if(ispal[j-1][i-1])
                    dp[i] = min(dp[i],dp[j-1] + 1);
            }
        }
        printf("%d\n",dp[n]);
    }
    return 0;
}
