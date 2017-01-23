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
const int maxn=1000+10;
int head[maxn],parents[maxn],dd[maxn],vv[maxn];
bool vis[maxn<<1];
int n,m,nEdge,ansm,sum,ss;
int Find(int x)
{
    return x==parents[x]?x:parents[x]=Find(parents[x]);
}
void Uion(int x,int y)
{
    int a=Find(x);
    int b=Find(y);
    if(a!=b)
    {
        parents[b]=a;
        sum++;
    }
}
struct NODE
{
    int to;
    int next;
};
NODE edge[maxn<<1],ans[maxn];
void connects(int u,int v)
{
    nEdge++;
    edge[nEdge].next=head[u];
    edge[nEdge].to=v;
    head[u]=nEdge;
}
bool Init()
{
    nEdge=-1;
    memset(head,0xff,sizeof(head));
    memset(dd,0,sizeof(dd));
    for(int i=0;i<maxn;++i)
      parents[i]=i;
    int u,v;
    sum=0;
    for(int i=0;i<m;++i)
    {
        cin>>u>>v;
        connects(u,v);
        connects(v,u);
        Uion(u,v);
        if(dd[u]==0) vv[n++]=u;
        dd[u]++;
        if(dd[v]==0) vv[n++]=v;
        dd[v]++;
        ss=v;
    }
    if(sum!=n-1) return false;
    for(int i=0;i<n;++i)
    {
        if(dd[vv[i]]%2!=0) return false;
    }
    return true;
}
void dfs(int now)
{
    int k;
    for(k=head[now];k!=-1;k=edge[k].next)
    {
        if(!vis[k])
        {
            vis[k]=vis[k^1]=true;
            dfs(edge[k].to);
            ans[ansm].next=now;
            ans[ansm].to=edge[k].to;
            ansm++;
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    cin>>t;
    while(t--)
    {
        tcase++;
        cin>>m;
        if(tcase>1) cout<<endl;
        cout<<"Case #"<<tcase<<endl;
        n=0;
        bool flag=Init();
        if(!flag)
        {
            cout<<"some beads may be lost"<<endl;
            continue;
        }
        memset(vis,0,sizeof(vis));
        ansm=0;
        dfs(ss);
        for(int i=0;i<m;++i)
        {
            cout<<ans[i].to<<" "<<ans[i].next<<endl;
        }
    }
    return 0;
}
