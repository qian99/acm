#pragma comment(linker,"/STACK:100000000,100000000")
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
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 100000 + 10;
struct Edge
{
    int v,next;
    Edge(){};
    Edge(int vv,int nx) {v=vv;next=nx;}
}edges[maxn<<1];
struct Node
{
    int u,v,w,type;
    Node(int u = 0,int v = 0,int w = 0,int type = 0):u(u),v(v),w(w),type(type){}
}node[maxn];
vector<pair<int,int> >querys[maxn];
int head[maxn],pa[maxn],convertE[maxn],anc[maxn],nEdge;
ll val[maxn],Eval[maxn],ans[maxn];
int q[maxn];
bool vis[maxn];
int Find(int x)
{
    return x == pa[x]?x:pa[x] = Find(pa[x]);
}
void AddEdges(int u,int v)
{
    edges[++nEdge]=Edge(v,head[u]);
    head[u]=nEdge;
    edges[++nEdge]=Edge(u,head[v]);
    head[v]=nEdge;
}
void tarjan(int u,int fa)
{
    pa[u]=u;
    vis[u]=true;
    int size=querys[u].size();
    int v;
    pair<int,int>pii;
    for(int i=0;i < size;++i)
    {
        pii = querys[u][i];
        v=pii.first;
        if(vis[v])
        {
            anc[pii.second] = Find(v);
        }
    }
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        v=edges[k].v;
        if(v==fa) continue;
        tarjan(v,u);
        pa[v]=u;
    }
}
void reads(int & x)
{
    char c;
    bool neg=false;
    while(((c=getchar())<'0'||c>'9')&&c!='-');
    if(c=='-')
    {
        neg=true;
        while((c=getchar())<'0'||c>'9');
    }
    x=c-'0';
    while(c=getchar(),c>='0'&&c<='9') x=x*10+c-'0';
    if(neg) x=-x;
}
void outs(ll num)
{
     if(num<0)
     {
         putchar('-');
         num=-num;
     }
     int ans[20],top=0;
     while(num!=0)
     {
         ans[top++]=num%10;
         num/=10;
     }
     if(top==0)
     putchar('0');
     for(int i=top-1;i>=0;i--){
         char ch=ans[i]+'0';
         putchar(ch);
     }
//     putchar('\n');
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    char str[20];
    int t,tcase = 0;
    scanf("%d",&t);
    while(t--)
    {
        int n,m,u,v,w;
        reads(n);reads(m);
//        scanf("%d%d",&n,&m);
        memset(head,0xff,sizeof(head));
        memset(vis,0,sizeof(vis));
        nEdge = -1;
        for(int i = 0;i <= n;++i)
            val[i] = Eval[i] = 0;
        for(int i = 1;i < n;++i)
        {
            scanf("%d%d",&u,&v);
            AddEdges(u,v);
        }
        for(int i = 0;i <= n;++i)
            querys[i].clear();
        for(int i = 1;i <= m;++i)
        {
            scanf("%s",str);
            reads(u);reads(v);reads(w);
//            scanf("%d%d%d",&u,&v,&w);
            node[i] = Node(u,v,w);
            querys[u].push_back(make_pair(v,i));
            querys[v].push_back(make_pair(u,i));
            if(str[3] == '1')
                node[i].type = 0;
            else
                node[i].type = 1;
        }
        tarjan(1,-1);
        int tail = 0;
        q[tail++] = 1;
        for(int i = 0;i < tail;++i)
        {
            u = q[i];
            for(int k = head[u];k != -1;k = edges[k].next)
            {
                v = edges[k].v;
                if(v == pa[u]) continue;
                convertE[v] = k/2;
                pa[v] = u;
                q[tail++] = v;
            }
        }
        pa[1] = 0;
        for(int i = 1;i <= m;++i)
        {
            if(node[i].type == 0)
            {
                val[node[i].u] += node[i].w;
                val[node[i].v] += node[i].w;
                val[pa[anc[i]]] -= node[i].w;
                val[anc[i]] -= node[i].w;
            }
            else
            {
                Eval[node[i].u] += node[i].w;
                Eval[node[i].v] += node[i].w;
                Eval[anc[i]] -= 2*node[i].w;
            }
        }
        for(int i = tail - 1;i >= 0;--i)
        {
            u = q[i];
            val[pa[u]] += val[u];
            Eval[pa[u]] += Eval[u];
        }
        printf("Case #%d:\n",++tcase);
        for(int i = 1;i <= n;++i)
        {
            if(i > 1) putchar(' ');
            outs(val[i]);
//            printf("%I64d",val[i]);
        }
        puts("");
        for(int i = 2;i <= n;++i)
            ans[convertE[i]] = Eval[i];
        for(int i = 0;i < n - 1;++i)
        {
            if(i) putchar(' ');
            outs(ans[i]);
//            printf("%I64d",ans[i]);
        }
        puts("");
    }
    return 0;
}