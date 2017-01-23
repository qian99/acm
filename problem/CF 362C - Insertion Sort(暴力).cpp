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
const int maxn = 5000 + 10;
int a[maxn];
int sum[maxn][maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n;
    scanf("%d",&n);
    for(int i = 1;i <= n;++i)
    {
        scanf("%d",&a[i]);
        a[i]++;
    }
    for(int i = 1; i <= n;++i)
    {
        for(int j = 1;j <= i;++j)
            sum[i][a[j]]++;
        for(int j = 1;j <= n;++j)
            sum[i][j] += sum[i][j-1];
    }
    int minv = inf,cnt = 0;
    for(int i = 1;i <= n;++i)
        for(int j = i;j <= n;++j)
        {
            int val = 0;
            val -= (sum[j][n] - sum[j][a[j]]) - (sum[i][n] - sum[i][a[j]]);
            val += sum[j][a[j]-1] - sum[i][a[j]-1];
            val -= sum[j][a[i]-1] - sum[i][a[i]-1];
            val += (sum[j][n] - sum[j][a[i]]) - (sum[i][n] - sum[i][a[i]]);
            if(val < minv)
            {
                minv = val;
                cnt = 1;
            }
            else if(val == minv)
                cnt++;
        }
    int ans = minv;
    for(int i = 1;i <= n;++i)
    {
        ans += sum[i][n] - sum[i][a[i]];
    }
    printf("%d %d\n",ans,cnt);
    return 0;
}