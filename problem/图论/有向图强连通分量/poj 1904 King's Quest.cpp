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
using namespace std;
const int maxn=4000+10;
const int maxm=200000+4000+10;
struct Edge
{
    int v,next;
};
Edge edges[maxm];
int head[maxn],pre[maxn],sccno[maxn],nEdge,dfs_clock,scc_cnt,n;
int num[maxn>>1];
stack<int>S;
void AddEdge(int u,int v)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
void Init()
{
    memset(head,0xff,sizeof(head));
    memset(pre,0,sizeof(pre));
    memset(sccno,0,sizeof(sccno));
    nEdge=-1;dfs_clock=scc_cnt=0;
}
int tarjan(int u)
{
    int lowu=pre[u]=++dfs_clock;
    S.push(u);
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(!pre[v])
        {
            int lowv=tarjan(v);
            lowu=min(lowu,lowv);
        }
        else if(!sccno[v])
           lowu=min(lowu,pre[v]);
    }
    if(lowu==pre[u])
    {
        scc_cnt++;
        while(true)
        {
            int x=S.top();S.pop();
            sccno[x]=scc_cnt;
            if(x==u) break;
        }
    }
    return lowu;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d",&n);
    Init();
    int k,tmp;
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&k);
        for(int j=0;j<k;++j)
        {
            scanf("%d",&tmp);
            AddEdge(i,tmp+n);
        }
    }
    int sz;
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&tmp);
        AddEdge(tmp+n,i);
    }
    for(int i=1;i<=n*2;++i)
      if(!pre[i]) tarjan(i);
    for(int i=1;i<=n;++i)
    {
        sz=0;
        for(int k=head[i];k!=-1;k=edges[k].next)
        {
            int v=edges[k].v;
            if(sccno[i]==sccno[v])
              num[sz++]=v-n;
        }
        sort(num,num+sz);
        printf("%d",sz);
        for(int j=0;j<sz;++j)
          printf(" %d",num[j]);
        printf("\n");
    }
    return 0;
}
