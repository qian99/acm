
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
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=1000000+10;
ll dp[maxn];
int a[maxn],f[maxn],d[maxn],s[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        memset(f,0,sizeof(f));
        memset(d,0,sizeof(d));
        memset(s,0,sizeof(s));
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
            d[i-f[a[i]]]++;
            f[a[i]]=i;
        }
        memset(f,0,sizeof(f));
        s[1]=1;f[a[n]]=1;
        for(int i=2;i<=n;++i)
        {
            if(!f[a[n-i+1]])
            {
                f[a[n-i+1]]=1;
                s[i]=s[i-1]+1;
            }
            else s[i]=s[i-1];
        }
        dp[1]=n;
        int tmp=n;
        for(int i=2;i<=n;++i)
        {
            dp[i]=dp[i-1]-s[i-1];
            tmp-=d[i-1];
            dp[i]+=tmp;
        }
        int q;
        scanf("%d",&q);
        while(q--)
        {
            scanf("%d",&tmp);
            printf("%I64d\n",dp[tmp]);
        }
    }
    return 0;
}
