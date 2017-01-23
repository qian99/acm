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
const int c[10] = {6,2,5,5,4,5,6,3,7,6};
int dp[55][3010],pw[55],n,m;
void findpath(int x,int mod,int sum)
{
    if(x == 0) return ;
    for(int i = 9;i >= 0;--i)
    {
        int v = (mod + i*pw[x-1])%m;
        int y = (m - v)%m;
        if(c[i] + dp[x-1][y] <= sum)
        {
            printf("%d",i);
            findpath(x-1,v,sum - c[i]);
            return ;
        }
    }
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int tcase = 0;
    while(~scanf("%d",&n))
    {
        if(n == 0) break;
        scanf("%d",&m);
        if(m == 0)
        {
            printf("Case %d: -1\n",++tcase);
            continue;
        }
        memset(dp,0x3f,sizeof(dp));
        pw[0] = 1 % m;
        for(int i = 1;i < 55 ;++i)
            pw[i] = pw[i-1]*10%m;
        for(int i = 0;i <= 9;++i)
            dp[1][i%m] = min(dp[1][i%m],c[i]);
        dp[0][0] = 0;
        for(int i = 1;i < 54 ;++i)
            for(int j = 0;j < m;++j)
            {
                if(dp[i][j] == inf) continue;
                for(int k = 0;k <= 9;++k)
                {
                    int v = (k*pw[i]%m + j)%m;
                    dp[i+1][v] = min(dp[i+1][v],dp[i][j] + c[k]);
                }
            }
        printf("Case %d: ",++tcase);
        bool flag = false;
        for(int i = 50; i >= 1 && !flag; --i)
        {
            for(int j = 9;j >= 1 && !flag;--j)
            {
                int v = (m - j*pw[i-1]%m)%m;
                if(c[j] + dp[i-1][v] <= n)
                {
                    printf("%d",j);
                    findpath(i-1,j*pw[i-1]%m,n - c[j]);
                    flag = true;
                    break;
                }
            }
        }
        if(!flag)
        {
            if(n >= 6) printf("0");
            else printf("-1");
        }
        puts("");
    }
    return 0;
}
