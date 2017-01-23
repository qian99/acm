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
#include<set>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=10000+10;
const int maxm=100000+10;
struct Edge
{
    int v,next;
    Edge(int v=0,int next=0):v(v),next(next){}
}edges[maxm<<1];
int head[maxn],pre[maxn],dfs_clock,nEdge;
int tot,flag[maxm<<1];
char graph[maxm<<1][2][22];
map<string,int>mp;
char strA[22],strB[22];
void AddEdges(int u,int v)
{
    edges[++nEdge]=Edge(v,head[u]);
    head[u]=nEdge;
    edges[++nEdge]=Edge(u,head[v]);
    head[v]=nEdge;
}
int tarjan(int u,int fa)
{
    int lowu=pre[u]=++dfs_clock;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        if(!pre[v])
        {
            int lowv=tarjan(v,u);
            lowu=min(lowu,lowv);
            if(lowv>pre[u])
            {
                flag[k]=flag[k^1]=1;
                tot++;
            }
        }
        else if(pre[v]<lowu)
            lowu=pre[v];
    }
    return lowu;
}
void Init()
{
    memset(head,0xff,sizeof(head));
    memset(flag,0,sizeof(flag));
    memset(pre,0,sizeof(pre));
    nEdge=-1;dfs_clock=tot=0;
    mp.clear();
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n,m;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        Init();
        string a,b;
        int u,v,N=0;
        for(int i=0;i<m;++i)
        {
            scanf("%s",strA);
            scanf("%s",strB);
            a=(string)strA;
            b=(string)strB;
            if(mp.find(a)!=mp.end()) u=mp[a];
            else u=mp[a]=++N;
            if(mp.find(b)!=mp.end()) v=mp[b];
            else v=mp[b]=++N;
            AddEdges(u,v);
            int len=strlen(strA);
            for(int j=0;j<len;++j) graph[i][0][j]=strA[j];
            graph[i][0][len]='\0';
            len=strlen(strB);
            for(int j=0;j<len;++j) graph[i][1][j]=strB[j];
            graph[i][1][len]='\0';
        }
        tarjan(1,-1);
        int ft=true;
        for(int i=1;i<=n;++i)
            if(!pre[i]) ft=false;
        if(!ft)
        {
            printf("0\n");
            continue;
        }
        printf("%d\n",tot);
        for(int i=0;i<m;i++)
            if(flag[i<<1])
            {
                printf("%s %s\n",graph[i][0],graph[i][1]);
            }
    }
    return 0;
}