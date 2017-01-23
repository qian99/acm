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
const int maxn=35;
int a[maxn],c[maxn];
int vis[maxn];
void dfs(int u)
{
    if(vis[u]) return ;
    vis[u]=true;
    dfs(a[u]);
}
ll solve(int k,int n)
{
    memset(c,0,sizeof(c));
    for(int i=1;i<=n;++i) a[i]=i;
    int cnt=0;
    for(int i=1;i<=n;++i)
    {
        memset(vis,0,sizeof(vis));
        cnt=0;
        for(int j=1;j<=n;++j)
        {
            if(!vis[j])
            {
                dfs(j);
                cnt++;
            }
        }
        c[cnt]++;
        int tmp=a[1];
        for(int j=1;j<n;++j) a[j]=a[j+1];
        a[n]=tmp;
    }
    if(n&1)
        c[(n-1)/2+1]+=n;
    else
    {
        c[n/2+1]+=n/2;
        c[n/2]+=n/2;
    }
    ll res=0,x=k;
    for(int i=1;i<=n;++i)
    {
        res+=x*c[i];
        x*=k;
    }
    return res/(2*n);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int k,n;
    while(cin>>k>>n)
    {
        if(k==0&&n==0) break;
        ll res=solve(k,n);
        cout<<res<<endl;
    }
    return 0;
}
