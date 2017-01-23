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
const int maxn=50000+10;
struct Edge
{
    int u,v,next;
    int w;
    Edge (){};
    Edge(int uu,int vv,int ww,int nx) {u=uu;v=vv;w=ww;next=nx;}
}edges[maxn<<1];
int head[maxn],nEdge;
int n,m,q,filp[maxn],degree[maxn];
ll a[555][555][2],sum[555][2];
ll res[2];
int hash[maxn],cnt;
void AddEdge(int u,int v,int w)
{
    edges[++nEdge]=Edge(u,v,w,head[u]);
    head[u]=nEdge;
}
void Init()
{
    memset(head,0xff,sizeof(head));
    memset(degree,0,sizeof(degree));
    memset(hash,0,sizeof(hash));
    memset(filp,0,sizeof(filp));
    res[0]=res[1]=0;
    nEdge=-1;cnt=0;
}
void precal()
{
    int lim=(int)sqrt((double)m);
    for(int i=1;i<=n;++i)
    {
        if(degree[i]>lim)
        {
            hash[i]=++cnt;
        }
    }
    memset(a,0,sizeof(a));
    memset(sum,0,sizeof(sum));
    int u,v;
    for(int i=0;i<nEdge;i+=2)
    {
        if(edges[i].w>0) res[0]+=edges[i].w;
        else res[1]+=edges[i].w;
        u=edges[i].u;v=edges[i].v;
        if(hash[u]&&hash[v])
        {
            if(edges[i].w>0)
            {
                a[hash[u]][hash[v]][0]+=edges[i].w;
                a[hash[v]][hash[u]][0]+=edges[i].w;
            }
            else
            {
                a[hash[u]][hash[v]][1]+=edges[i].w;
                a[hash[v]][hash[u]][1]+=edges[i].w;
            }
        }
        if(hash[u]) sum[hash[u]][edges[i].w<0]+=edges[i].w;
        if(hash[v]) sum[hash[v]][edges[i].w<0]+=edges[i].w;
    }
}
void changes(int x)
{
    if(hash[x])
    {
        res[0]+=(-sum[hash[x]][1]);
        res[0]-=sum[hash[x]][0];
        res[1]+=(-sum[hash[x]][0]);
        res[1]-=sum[hash[x]][1];

        swap(sum[hash[x]][0],sum[hash[x]][1]);
        sum[hash[x]][0]*=-1;sum[hash[x]][1]*=-1;
        for(int i=1;i<=cnt;++i)
        {
            if(i==hash[x]) continue;
            sum[i][0]-=a[i][hash[x]][0];
            sum[i][0]+=(-a[i][hash[x]][1]);
            sum[i][1]-=a[i][hash[x]][1];
            sum[i][1]+=(-a[i][hash[x]][0]);
            swap(a[i][hash[x]][0],a[i][hash[x]][1]);
            a[i][hash[x]][0]*=-1;a[i][hash[x]][1]*=-1;
            swap(a[hash[x]][i][0],a[hash[x]][i][1]);
            a[hash[x]][i][0]*=-1;a[hash[x]][i][1]*=-1;
        }
        filp[x]^=1;
    }
    else
    {
        int v,tmp;
        filp[x]^=1;
        for(int k=head[x];k!=-1;k=edges[k].next)
        {
            v=edges[k].v;
            if(filp[x]^filp[v]) tmp=-edges[k].w;
            else tmp=edges[k].w;
            if(tmp>0)
            {
                res[0]+=tmp;
                res[1]-=(-tmp);
                if(hash[v])
                {
                    sum[hash[v]][0]+=tmp;
                    sum[hash[v]][1]-=(-tmp);
                }
            }
            else
            {
                res[0]-=(-tmp);
                res[1]+=tmp;
                if(hash[v])
                {
                    sum[hash[v]][0]-=(-tmp);
                    sum[hash[v]][1]+=tmp;
                }
            }
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    char str[5];
    //map<ll,int>mp;
    int first=true;
    while(~scanf("%d%d%d",&n,&m,&q))
    {
        if(!first) printf("\n");
        first=false;
        Init();
        //mp.clear();
        int u,v,w;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            degree[u]++;degree[v]++;
            AddEdge(u,v,w);
            AddEdge(v,u,w);
            //mp[tmp]=nEdge;
        }
        precal();
        ll ans=0;
        int x;
        while(q--)
        {
            scanf("%s",str);
            if(str[0]=='Q')
            {
                scanf("%s",str);
                if(str[0]=='A')
                    ans=res[0]+res[1];
                else if(str[0]=='+')
                    ans=res[0];
                else ans=res[1];
                printf("%lld\n",ans);
            }
            else
            {
                scanf("%d",&x);
                changes(x);
            }
        }
    }
    return 0;
}

