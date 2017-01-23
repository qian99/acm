#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=1000+10;
char str[maxn];
int dp[maxn],pre[maxn],last[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    memset(dp,0,sizeof(dp));
    memset(last,0xff,sizeof(last));
    memset(pre,0xff,sizeof(pre));
    scanf("%s",str);
    int n=strlen(str);
    int ans=0;
    for(int i=0;i<n;++i)
    {
        if(last[(int)str[i]]==-1)
        {
            last[(int)str[i]]=i;
            dp[i]=1;
        }
        else
        {
            int x=last[(int)str[i]];
            last[(int)str[i]]=i;
            pre[i]=x;
            while(x!=-1)
            {
                if((i-x)&1)
                    dp[i]=max(dp[i],dp[x]+1);
                x=pre[x];
            }
        }
        ans=max(ans,dp[i]);
    }
    printf("%d\n",ans);
    return 0;
}

