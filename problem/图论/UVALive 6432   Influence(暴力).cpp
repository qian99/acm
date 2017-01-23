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
const int maxn=5000+10;
const int maxm=250000+10;
struct Edge
{
    int v,next;
    Edge(){}
    Edge(int v,int next):v(v),next(next){}
}edges[maxm<<1];
int head[maxn],nEdge;
bool vis[maxn];
void AddEdges(int u,int v)
{
    edges[++nEdge]=Edge(v,head[u]);
    head[u]=nEdge;
}
char str[maxm];
int X[maxn],cnt;
void dfs(int u)
{
    if(vis[u]) return ;
    vis[u]=true;
    cnt++;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        dfs(v);
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,k;
    while(~scanf("%d%d",&n,&k))
    {
        for(int i=0;i<k;++i)
            scanf("%d",&X[i]);
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        getchar();
        for(int i=0;i<n;++i)
        {
            gets(str);
            int len=strlen(str);
            int j=0,u=0,v;
            while(j<len&&str[j]>='0'&&str[j]<='9') u=u*10+str[j++]-'0';
            while(j<len)
            {
                while(j<len&&(str[j]<'0'||str[j]>'9')) j++;
                v=0;
                while(j<len&&str[j]>='0'&&str[j]<='9') v=v*10+str[j++]-'0';
                if(v) AddEdges(u,v);
            }
        }
        int maxv=-1,id;
        for(int i=0;i<k;++i)
        {
            int u=X[i];
            memset(vis,0,sizeof(vis));
            cnt=0;
            dfs(u);
            if(cnt>maxv) {maxv=cnt;id=u;}
        }
        printf("%d\n",id);
    }
    return 0;
}
