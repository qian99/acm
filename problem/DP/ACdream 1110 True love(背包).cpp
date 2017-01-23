/*
* this code is made by qian99
* Problem: 1110
* Verdict: Accepted
* Submission Date: 2014-06-10 06:48:28
* Time: 468 MS
* Memory: 2460 KB
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<vector>
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100000+10;
int dp[maxn],cnt[maxn];
int a[110],b[110];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    int n,m;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i)
            scanf("%d",&a[i]);
        for(int j=1;j<=n;++j)
            scanf("%d",&b[j]);
        memset(dp,0,sizeof(dp));
        dp[0]=1;
        int ans=0;
        for(int i=1;i<=n;++i)
        {
            memset(cnt,0,sizeof(cnt));
            for(int j=a[i];j<=m;++j)
            {
                if(dp[j-a[i]]&&!dp[j]&&cnt[j-a[i]]<b[i])
                {
                    ans++;
                    dp[j]=1;
                    cnt[j]=cnt[j-a[i]]+1;
                }
            }
        }
        printf("Case %d: %d\n",++tcase,ans);
    }
    return 0;
}