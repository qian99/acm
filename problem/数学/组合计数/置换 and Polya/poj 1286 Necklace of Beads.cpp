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
const int maxn=30;
ll p[maxn];
int c[maxn],a[maxn],cnt;
bool vis[maxn];
void dfs(int u)
{
    if(vis[u]) return ;
    vis[u]=true;
    dfs(a[u]);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    p[0]=1;
    for(int i=1;i<maxn;++i) p[i]=p[i-1]*3;
    int n;
    while(cin>>n)
    {
        if(n==-1) break;
        if(n==0)
        {
            cout<<0<<endl;
            continue;
        }
        memset(c,0,sizeof(c));
        for(int i=1;i<=n;++i) a[i]=i;
        for(int i=1;i<=n;++i)
        {
            memset(vis,0,sizeof(vis));
            cnt=0;
            for(int j=1;j<=n;++j)
            {
                if(!vis[j])
                {
                    cnt++;
                    dfs(j);
                }
            }
            c[cnt]++;
            int tmp=a[1];
            for(int j=1;j<n;++j) a[j]=a[j+1];
            a[n]=tmp;
        }
        if(n&1)
        {
            c[(n-1)/2+1]+=n;
        }
        else
        {
            c[n/2]+=n/2;
            c[n/2+1]+=n/2;
        }
        ll ans=0;
        for(int i=1;i<=n;++i)
            ans+=c[i]*p[i];
        ans/=2*n;
        cout<<ans<<endl;
    }
    return 0;
}
