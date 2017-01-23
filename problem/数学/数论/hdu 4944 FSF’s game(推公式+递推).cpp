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
typedef unsigned int uint;
const int maxn= 500000+10;
uint dp[maxn],f[maxn],sum[maxn];
vector<int>factor[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    for(int i = 1;i < maxn ;++i)
        for(int j = i;j < maxn;j += i)
        {
            factor[j].push_back(i);
            sum[j] += (uint)i;
        }
    f[1] = 1;
    for(int i = 2;i < maxn ;++i)
    {
        if(i & 1) f[i] = (i+1)/2*i;
        else f[i] = i/2*(i+1);
        for(int j = 1;j < (int)factor[i].size();++j)
        {
            int d = factor[i][j];
            f[i] -= f[i/d]*d;
        }
    }
    dp[1] = 1;
    for(int i = 2; i < maxn ;++i)
    {
        dp[i] = 0;
        for(int j = 0;j < (int)factor[i].size();++j)
        {
            int d = factor[i][j];
            dp[i] += sum[d] * f[i/d];
        }
        dp[i] *= i;
        dp[i] += dp[i-1];
    }
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        int n;
        scanf("%d",&n);
        printf("Case #%d: %I64d\n",++tcase,(ll)dp[n]);
    }
    return 0;
}
