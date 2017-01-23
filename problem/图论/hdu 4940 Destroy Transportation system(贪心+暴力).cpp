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
const int maxn = 200+10;
const int maxm = 5000+10;
struct Edge
{
    int v,D,B,type,next;
    Edge(int v = 0,int D =0,int B=0,int type = 0,int next=0):v(v),D(D),B(B),type(type),next(next){}
}edges[maxm<<1];
int head[maxn],nEdge;
void AddEdges(int u,int v,int D,int B)
{
    edges[++nEdge]=Edge(v,D,B,0,head[u]);
    head[u]=nEdge;
    edges[++nEdge]=Edge(u,D,B,1,head[v]);
    head[v]=nEdge;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        printf("Case #%d: ",++tcase);
        int u,v,D,B;
        int n,m;
        scanf("%d%d",&n,&m);
        for(int i = 0;i < m;++i)
        {
            scanf("%d%d%d%d",&u,&v,&D,&B);
            AddEdges(u,v,D,B);
        }
        bool flag = false;
        int X,Y;
        for(int u = 1; u <= n;++u)
        {
            X = Y =0;
            for(int k=head[u];k!=-1;k=edges[k].next)
            {
                if(edges[k].type == 0) X += edges[k].D;
                else Y += edges[k].D + edges[k].B;
            }
            if(X > Y)
            {
                flag = true;
                break;
            }
        }
        if(flag) printf("unhappy\n");
        else printf("happy\n");
    }
    return 0;
}