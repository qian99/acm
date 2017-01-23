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
#pragma comment(linker, "/STACK:1024000000,1024000000")

using namespace std;
typedef long long ll;
const int maxn=1000000+10;
struct Edge
{
    int v;
    int next;
};
int head[maxn],nEdge,ans;
Edge edges[maxn<<1];
void AddEdge(int u,int v)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
int dfs(int u,int fa)
{
    int cnt=0;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        cnt+=dfs(v,u);
    }
    if(cnt>=2)
    {
        if(fa==-1)
          ans+=(cnt-2);
        else
          ans+=(cnt-2)+1;
        return 0;
    }
    return 1;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        int a,b;
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        for(int i=1;i<n;++i)
        {
            scanf("%d%d",&a,&b);
            AddEdge(a,b);
            AddEdge(b,a);
        }
        ans=0;
        dfs(1,-1);
        printf("%d\n",ans*2+1);
    }
    return 0;
}
