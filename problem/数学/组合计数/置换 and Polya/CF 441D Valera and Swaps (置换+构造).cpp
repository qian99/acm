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
const int maxn=3000+10;
int a[maxn],cnt,n,m;
bool vis[maxn];
void dfs(int i)
{
    if(vis[i]) return ;
    vis[i]=true;
    dfs(a[i]);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        scanf("%d",&a[i]);
    scanf("%d",&m);
    cnt=0;
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;++i)
        if(!vis[i]) dfs(i),cnt++;
    cnt=n-cnt;
    printf("%d\n",abs(cnt-m));
    if(cnt<m)
    {

        for(int i=0;i<m-cnt;++i)
        {
            if(i) printf(" ");
            memset(vis,0,sizeof(vis));
            dfs(1);
            int j;
            for(j=1;j<=n;++j)
                if(!vis[j]) break;
            printf("%d %d",1,j);
            swap(a[1],a[j]);
        }
        printf("\n");
    }
    else
    {
        for(int i=0;i<cnt-m;++i)
        {
            if(i) printf(" ");
            int j,k,x;
            for(j=1;j<=n;++j)
                if(a[j]!=j) break;
            for(k=x=a[j];k!=j;k=a[k])
                x=min(x,k);
            printf("%d %d",j,x);
            swap(a[j],a[x]);
        }
        printf("\n");
    }
    return 0;
}
