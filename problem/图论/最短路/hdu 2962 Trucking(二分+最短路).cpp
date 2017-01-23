//2962
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
using namespace std;
typedef long long ll;
const int maxn=1000+10;
struct Edge
{
    int v,h,w,next;
}edges[maxn*maxn*2];
int head[maxn],d[maxn],nEdge;
int n,m,s,z,hlim,mxh,sht;
bool inq[maxn];
void AddEdge(int u,int v,int h,int w)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].h=h;
    edges[nEdge].w=w;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
int spfa(int hh)
{
    memset(d,0x3f,sizeof(d));
    memset(inq,0,sizeof(inq));
    d[s]=0;
    queue<int>q;
    q.push(s);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        inq[u]=false;
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            int v=edges[k].v;
            if(edges[k].h>=hh&&d[v]>d[u]+edges[k].w)
            {
                d[v]=d[u]+edges[k].w;
                if(!inq[v]) {inq[v]=true;q.push(v);}
            }
        }
    }
    if(d[z]==inf) return -1;
    return d[z];
}
void solve()
{
    if(spfa(0)==-1)
    {
        mxh=-1;
        return ;
    }
    int L=0,R=hlim;
    int M,tmp;
    while(L<=R)
    {
        M=(L+R)>>1;
        tmp=spfa(M);
        if(tmp==-1)
          R=M-1;
        else
        {
            L=M+1;
            mxh=M;
            sht=tmp;
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int tcase=0;
    while(~scanf("%d%d",&n,&m))
    {
        if(n==0&&m==0) break;
        if(tcase) printf("\n");
        tcase++;
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        int u,v,h,w;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d%d",&u,&v,&h,&w);
            if(h==-1) h=inf;
            AddEdge(u,v,h,w);
            AddEdge(v,u,h,w);
        }
        scanf("%d%d%d",&s,&z,&hlim);
        solve();
        printf("Case %d:\n",tcase);
        if(mxh==-1) printf("cannot reach destination\n");
        else
        {
            printf("maximum height = %d\n",mxh);
            printf("length of shortest route = %d\n",sht);
        }
    }
    return 0;
}
