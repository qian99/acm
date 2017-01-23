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
const int maxn=2000+10;
const int maxm=20000+10;
struct Edge
{
    int v,w,c,next;
    Edge(int v=0,int w=0,int c=0,int next=0):v(v),w(w),c(c),next(next){}
}edges[maxm<<1];
struct Node
{
    int u,st;
    Node(int u=0,int st=0):u(u),st(st){}
};
int head[maxn],nEdge;
ll d[maxn][4],mx[maxn][4];
bool inq[maxn][4];
inline int getx(char c)
{
    if(c=='L') return 0;
    else if(c=='O') return 1;
    else if(c=='V') return 2;
    return 3;
}
void AddEdges(int u,int v,int w,int c)
{
    edges[++nEdge]=Edge(v,w,c,head[u]);
    head[u]=nEdge;
    edges[++nEdge]=Edge(u,w,c,head[v]);
    head[v]=nEdge;
}
void spfa(int n)
{
    queue<Node>q;
    memset(inq,0,sizeof(inq));
    memset(mx,0,sizeof(mx));
    for(int i=1;i<=n;++i)
        for(int j=0;j<4;++j)
            d[i][j]=Inf;
    d[1][3]=0;
    q.push(Node(1,3));
    Node node;
    int u,st;
    while(!q.empty())
    {
        node=q.front();q.pop();
        u=node.u;
        st=node.st;
        inq[u][st]=false;
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            int v=edges[k].v;
            if(edges[k].c!=(st+1)%4) continue;
            int tmp=mx[u][st]+(edges[k].c==3);
            if(d[v][edges[k].c]>d[u][st]+edges[k].w)
            {
                d[v][edges[k].c]=d[u][st]+edges[k].w;
                mx[v][edges[k].c]=tmp;
                if(!inq[v][edges[k].c])
                {inq[v][edges[k].c]=true;q.push(Node(v,edges[k].c));}
            }
            else if(d[v][edges[k].c]==d[u][st]+edges[k].w&&tmp>mx[v][edges[k].c])
            {
                mx[v][edges[k].c]=tmp;
                if(!inq[v][edges[k].c])
                {inq[v][edges[k].c]=true;q.push(Node(v,edges[k].c));}
            }
        }
    }
    ll ans=d[n][3],ans2=mx[n][3];
    if(n==1)
    {
        ll a[5]={0},sum=0;
        for(int k=head[1];k!=-1;k=edges[k].next)
            if(!a[edges[k].c]) a[edges[k].c]=edges[k].w;
            else a[edges[k].c]=min(a[edges[k].c],(ll)edges[k].w);
        bool flag=true;
        for(int i=0;i<4;++i)
            if(!a[i]) flag=false;
            else sum+=a[i];
        if(flag) ans=sum,ans2=1;
        else ans=ans2=Inf;
    }
    if(ans==Inf)
        printf("Binbin you disappoint Sangsang again, damn it!\n");
    else
        printf("Cute Sangsang, Binbin will come with a donkey after travelling %I64d meters and finding %I64d LOVE strings at last.\n",ans,ans2);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    int n,m;
    char str[5];
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        int u,v,w;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d%s",&u,&v,&w,str);
            AddEdges(u,v,w,getx(str[0]));
        }
        printf("Case %d: ",++tcase);
        spfa(n);
    }
    return 0;
}
