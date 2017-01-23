#include <iostream>
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
const int maxn=2000+10;
const int maxm=8000+10;
const char * str[4]={"LEFT","RIGHT","UP","DOWN"};
struct Node
{
    int x,y,id;
    Node(){}
    Node(int x,int y,int id):x(x),y(y),id(id){}
}node[maxn];
struct Edge
{
    int v,next;
    Edge(){}
    Edge(int v,int next):v(v),next(next){}
}edges[maxm<<1];
int head[maxn],degree[maxn],nEdge,n;
int hash[maxn][2],tot,cnt;
int flag[maxn],S[maxn];
bool inq[maxn];
vector<pair<int,int> >ans;
void AddEdges(int u,int v)
{
    edges[++nEdge]=Edge(v,head[u]);
    head[u]=nEdge;
    edges[++nEdge]=Edge(u,head[v]);
    head[v]=nEdge;
}
bool cmp1(Node a,Node b)
{
    return (a.x==b.x&&a.y<b.y)||(a.x<b.x);
}
bool cmp2(Node a,Node b)
{
    return (a.y==b.y&&a.x<b.x)||(a.y<b.y);
}
void Init()
{
    memset(head,0xff,sizeof(head));
    memset(degree,0,sizeof(degree));
    memset(flag,0,sizeof(flag));
    memset(inq,0,sizeof(inq));
    nEdge=-1;tot=cnt=0;
    ans.clear();
}
void getans(int u,int v)
{
    if(hash[u][0]==hash[v][0])
    {
        if(hash[u][1]<hash[v][1])
            ans.push_back(make_pair(u,2));
        else
            ans.push_back(make_pair(u,3));
    }
    else
    {
        if(hash[u][0]>hash[v][0])
            ans.push_back(make_pair(u,0));
        else
            ans.push_back(make_pair(u,1));
    }
}
void dfs(int u)
{
    flag[u]=tot;
    S[cnt++]=u;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(flag[v]) continue;
        dfs(v);
        getans(v,u);
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d",&n))
    {
        int x,y;
        Init();
        for(int i=1;i<=n;++i)
        {
            scanf("%d%d",&x,&y);
            node[i]=Node(x,y,i);
            hash[i][0]=x;hash[i][1]=y;
        }
        sort(node+1,node+n+1,cmp1);
        for(int i=2;i<=n;++i)
        {
            if(node[i].x==node[i-1].x)
            {
                AddEdges(node[i].id,node[i-1].id);
                degree[node[i].id]++;
                degree[node[i-1].id]++;
            }
        }
        sort(node+1,node+n+1,cmp2);
        for(int i=2;i<=n;++i)
        {
            if(node[i].y==node[i-1].y)
            {
                AddEdges(node[i].id,node[i-1].id);
                degree[node[i].id]++;
                degree[node[i-1].id]++;
            }
        }
        int block=0;
        for(int i=1;i<=n;++i)
        {
            if(!flag[i])
            {
                cnt=0;++tot;
                dfs(i);
                block++;
            }
        }
        printf("%d\n",block);
        int size=ans.size();
        for(int i=0;i<size;++i)
        {
            int u=ans[i].first;
            printf("(%d, %d) %s\n",hash[u][0],hash[u][1],str[ans[i].second]);
        }
    }
    return 0;
}
