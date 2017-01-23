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
const int maxn=2000+10;
const int maxm=maxn*maxn;
struct Edge
{
    int v,w,next;
}edges[maxm];
int head[maxn],hash[70000],d[maxn],nEdge,N;
bool inq[maxn];
char str[100];
void AddEdge(int u,int v,int w)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].w=w;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
int getnum(int a,int b)
{
    int rnt=0,tmp;
    for(int i=a;i<=b;++i)
    {
        if(str[i]>='0'&&str[i]<='9')
          tmp=str[i]-'0';
        else tmp=str[i]-'A'+10;
        rnt=rnt*16+tmp;
    }
    return rnt;
}
int spfa(int s,int t,int fd)
{
    memset(d,0x3f,sizeof(d));
    memset(inq,0,sizeof(inq));
    d[s]=fd;
    queue<int>q;
    q.push(s);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        inq[u]=false;
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            int v=edges[k].v;
            if(d[v]>d[u]+edges[k].w)
            {
                d[v]=d[u]+edges[k].w;
                if(!inq[v]) {inq[v]=true;q.push(v);}
            }
        }
    }
    if(d[t]==inf) return -1;
    return d[t];
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,s,t,fd;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        N=1;nEdge=-1;
        memset(head,0xff,sizeof(head));
        memset(hash,0,sizeof(hash));
        int u,v,w,len;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&w);
            scanf("%s",str);
            len=strlen(str);
            u=getnum(0,3);
            v=getnum(len-4,len-1);
            if(!hash[u]) hash[u]=N++;
            if(!hash[v]) hash[v]=N++;
            AddEdge(hash[u],hash[v],w);
            if(i==1) s=hash[v],fd=w;
            if(i==n) t=hash[u];
        }
        int ans=spfa(s,t,fd);
        printf("%d\n",ans);
    }
    return 0;
}
