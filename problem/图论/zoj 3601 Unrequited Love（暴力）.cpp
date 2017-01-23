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
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 60000+10;
struct Edge
{
    int v,next;
    Edge(int v = 0,int next = 0):v(v),next(next){}
}edges[1000000];
int head[maxn],nEdge;
map<string,int>id;
int flag[maxn],in[maxn],out[maxn],S[maxn];
char str[55],names[maxn][55];
void AddEdges(int u,int v)
{
    edges[++nEdge] = Edge(v,head[u]);
    head[u] = nEdge;
}
void Init()
{
    id.clear();
    memset(flag,0,sizeof(flag));
    memset(in,0,sizeof(in));
    memset(out,0,sizeof(out));
    memset(head,0xff,sizeof(head));
    nEdge = -1;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    int n,m,q;
    while(t--)
    {
        scanf("%d%d%d",&n,&m,&q);
        Init();
        int N = n + m,k,cnt = 0;
        int u,v;
        for(int i = 1;i <= N;++i)
        {
            scanf("%s",str);
            if(id.find((string)str) != id.end())
                u = id[(string)str];
            else
            {
                u = id[(string)str] = ++cnt;
                strcpy(names[u],str);
            }
            scanf("%d",&k);
            for(int j = 0;j < k;++j)
            {
                scanf("%s",str);
                if(id.find((string)str) != id.end())
                    v = id[(string)str];
                else
                {
                    v = id[(string)str] = ++cnt;
                    strcpy(names[v],str);
                }
                AddEdges(u,v);
            }
        }
        while(q--)
        {
            scanf("%d",&k);
            for(int i = 0;i < k;++i)
            {
                scanf("%s",str);
                u = id[(string)str];
                S[i] = u;
                flag[u] = true;
                in[u] = out[u] = 0;
            }
            for(int i = 0;i < k;++i)
            {
                u = S[i];
                for(int j = head[u];j != -1;j = edges[j].next)
                {
                    v = edges[j].v;
                    if(!flag[v]) continue;
                    in[v]++;out[u]++;
                }
            }
            u = -1;
            for(int i = 0;i < k;++i)
            {
                if(in[S[i]] == 0 && out[S[i]] == k-1)
                {
                    u = S[i];
                }
                flag[S[i]] = false;
            }
            if(u == -1) puts("0");
            else
            {
                printf("1 %s\n",names[u]);
            }
        }
        puts("");
    }
    return 0;
}
