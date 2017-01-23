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
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=55;
int a[maxn],sum[maxn],ans,n,m;
bool vis[maxn];
bool cmp(int a,int b) { return a>b; }
void dfs(int p,int now)
{
    if(now>ans) ans=now;
    if(now+sum[n]-sum[p-1]<=ans) return ;
    for(int i=p;i<=n;++i)
    {
        if(!vis[i]&&now+a[i]<=m)
        {
            vis[i]=true;
            dfs(i+1,now+a[i]);
            vis[i]=false;
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&n,&m))
    {
        for(int i=1;i<=n;++i)
            scanf("%d",&a[i]);
        sort(a+1,a+n+1,cmp);
        sum[0]=0;
        for(int i=1;i<=n;++i)
            sum[i]=sum[i-1]+a[i];
        ans=sum[n];
        if(ans>m)
        {
            for(int i=n;i>=1;--i)
                if(ans>m) ans-=a[i];
                else break;
            memset(vis,0,sizeof(vis));
            dfs(1,0);
        }
        printf("%d\n",ans);
    }
    return 0;
}
