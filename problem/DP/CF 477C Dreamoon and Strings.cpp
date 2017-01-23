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
const int maxn = 2000 + 10;
int dp[maxn][maxn],ans[maxn];
char a[maxn],b[maxn];
pair<int,int>next[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    scanf("%s",a + 1);
    scanf("%s",b + 1);
    int n = strlen(a + 1);
    int m = strlen(b + 1);
    for(int i = 1;i <= n;++i)
    {
        next[i] = make_pair(-1,-1);
        if(a[i] != b[1]) continue;
        int cnt = 0,pos = i,now = 1;
        while(now <= m && pos <= n)
        {
            if(a[pos] == b[now])
                now++;
            else
                cnt++;
            if(now > m)
            {
                next[i] = make_pair(pos,cnt);
                break;
            }
            pos++;
        }
    }
    memset(dp,0xff,sizeof(dp));
    dp[0][0] = 0;
    for(int i = 0;i < n;++i)
    {
        for(int j = 0;j < n;++j)
        {
            if(dp[i][j] == -1) continue;
            dp[i + 1][j] = max(dp[i + 1][j],dp[i][j]);
            dp[i + 1][j + 1] = max(dp[i + 1][j + 1],dp[i][j]);
            if(next[i + 1].first != -1)
            {
                dp[next[i + 1].first][j + next[i + 1].second] = max(dp[next[i + 1].first][j + next[i + 1].second],dp[i][j] + 1);
            }
        }
    }
    for(int i = 0;i <= n;++i)
        printf("%d ",dp[n][i]);
    puts("");
    return 0;
}
