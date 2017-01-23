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
const int maxn=100000+100;
struct Edge
{
    int v,next;
};
Edge edges[maxn<<1];
int head[maxn],nEdge;
void AddEdge(int u,int v)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
int pre[maxn],loop[50],id[maxn],len,dfs_clock;
int degree[maxn];
stack<int>S;
int n;
double down[maxn],up[maxn],lf[50][50],rt[50][50];
int childs[maxn];
void Init()
{
    memset(head,0xff,sizeof(head));
    memset(pre,0,sizeof(pre));
    memset(id,0xff,sizeof(id));
    memset(down,0,sizeof(down));
    memset(childs,0,sizeof(childs));
    memset(degree,0,sizeof(degree));
    nEdge=-1;dfs_clock=0;
}
int tarjan(int u,int fa)
{
    int lowu=pre[u]=++dfs_clock;
    S.push(u);
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
                int x;
                while(true)
                {
                    x=S.top();S.pop();
                    if(x==v) break;
                }
            }
        }
        else if(pre[v]<pre[u])
           lowu=min(lowu,pre[v]);
    }
    if(lowu==pre[u])
    {
        int x;
        x=S.top();
        if(x!=u)
        {
            len=0;
            while(true)
            {
                x=S.top();S.pop();
                loop[len]=x;id[x]=len++;
                if(x==u) {S.push(u);break;}
            }
        }
    }
    return lowu;
}

void fdown(int u,int fa)
{
    sumd[u]=0;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa||id[v]>=0) continue;
        childs[u]++;
        fdown(v,u);
        if(childs[v]!=0)
          down[u]+=down[v]*(1.0/childs[v]);
        down[u]+=(1.0/n)*(1.0/(childs[v]+1));
    }
}
void fup(int u,int fa,int p)
{
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa||id[v]>=0) continue;
        double tmp=0;
        if(childs[v]!=0)
          tmp=down[v]*(1.0/childs[v]);
        tmp+=(1.0/n)*(1.0/(childs[v]+1));
        //up[v]=up[u]+(down[u]-tmp)*(1.0/childs[u]);
        up[v]=up[u]*(1.0/childs[u]);
        if(childs[u]>1)
        {
            if(u==p)
              up[v]+=(down[u]-tmp)*(1.0/(childs[u]+1));
            else up[v]+=(down[u]-tmp)*(1.0/childs[u]);
        }
        if(u!=p) up[v]+=(1.0/n)*(1.0/(childs[u]+1));
        fup(v,u,p);
    }
}
void calloop()
{
    double now,cc;
    int tmp,tmp2;
    for(int i=0;i<len;++i)
    {
        tmp=(i+1)%len;
        now=rt[i][tmp]=down[loop[i]]*(1.0/(childs[loop[i]]+1))+(1.0/n)*(1.0/(childs[loop[i]]+2));
        for(int j=2;j<len;++j)
        {
            tmp2=tmp;
            tmp=(i+j)%len;
            rt[i][tmp]=now*(1.0/(childs[loop[tmp2]]+1));
            now=rt[i][tmp];
        }
        tmp=(i-1+len)%len;
        now=lf[i][tmp]=down[loop[i]]*(1.0/(childs[loop[i]]+1))+(1.0/n)*(1.0/(childs[loop[i]]+2));
        for(int j=2;j<len;++j)
        {
            tmp2=tmp;
            tmp=(i-j+len)%len;
            now=lf[i][tmp]=now*(1.0/(childs[loop[tmp2]]+1));
        }
    }
    for(int i=0;i<len;++i)
    {
        if(childs[loop[i]]==0)
        {
            up[loop[i]]=lf[(i-1+len)%len][i]+rt[(i+1)%len][i];
        }
        else
        {
            cc=0;
            for(int j=0;j<len;++j)
            {
                if(i==j) continue;
                cc+=lf[j][i]+rt[j][i];
            }
            cc-=(rt[(i+1)%len][i]+lf[(i-1+len)%len][i]);
            up[loop[i]]=cc*(1.0*childs[loop[i]]/(childs[loop[i]]+1))+(1.0/n)*(1.0*childs[loop[i]]/(childs[loop[i]]+2));
            up[loop[i]]+=rt[(i+1)%len][i]+lf[(i-1+len)%len][i];
            fup(loop[i],-1,loop[i]);
        }
    }
}
double solve()
{
    double ans=0;
    double res[6]={0};
    tarjan(1,-1);
    for(int i=0;i<len;++i)
       fdown(loop[i],-1);
    calloop();
    for(int i=1;i<=n;++i)
    {
        if(degree[i]==1||(id[i]>=0&&childs[i]==0))
        {
            res[0]=up[i];
            sort(res,res+6);
        }
    }
    for(int i=1;i<6;++i)
      ans+=res[i];
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        Init();
        int u,v;
        for(int i=0;i<n;++i)
        {
            scanf("%d%d",&u,&v);
            degree[u]++;degree[v]++;
            AddEdge(u,v);
            AddEdge(v,u);
        }
        double ans=solve();
        printf("%.5lf\n",ans);
    }
    return 0;
}
