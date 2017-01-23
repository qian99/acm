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
#pragma comment(linker, "/STACK:1024000000,1024000000")
using namespace std;
typedef long long ll;
const int maxn=100000+10;
int lson[maxn],rson[maxn],rnk[maxn];
int ans1[maxn],ans2[maxn],ww[maxn];
bool flag[maxn];
int n,m,q,cnt,lf,rn;
struct Node
{
    int u,w;
    bool operator < (const Node &a) const
    {
        return w<a.w;
    }
};
Node node[maxn];
vector<Node>querys[maxn];
int maxv[maxn<<1][2],minv[maxn<<1][2],sum[maxn<<1][2];
void Init()
{
    memset(lson,0xff,sizeof(lson));
    memset(rson,0xff,sizeof(rson));
    memset(flag,0,sizeof(flag));
    for(int i=1;i<=n;++i) querys[i].clear();
}
void PushUp(int rt,int h)
{
    sum[rt][h]=sum[rt<<1][h]+sum[rt<<1|1][h];
    maxv[rt][h]=max(maxv[rt<<1][h],maxv[rt<<1|1][h]);
    minv[rt][h]=min(minv[rt<<1][h],minv[rt<<1|1][h]);
}
void build(int l,int r,int rt)
{
    sum[rt][0]=sum[rt][1]=0;
    maxv[rt][0]=maxv[rt][1]=-1;
    minv[rt][0]=minv[rt][1]=inf;
    if(l==r) return ;
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
}
int Query1(int l,int r,int rt,int v,int h)
{
    if(maxv[rt][h]<v) return sum[rt][h];
    if(minv[rt][h]>=v||l==r) return 0;
    int m=(l+r)>>1;
    int ls=rt<<1,rs=rt<<1|1;
    if(maxv[ls][h]<v)
      return sum[ls][h]+Query1(m+1,r,rs,v,h);
    else return Query1(l,m,ls,v,h);
}
int Query2(int l,int r,int rt,int v,int h)
{
    if(minv[rt][h]>v) return sum[rt][h];
    if(maxv[rt][h]<=v||l==r) return 0;
    int m=(l+r)>>1;
    int ls=rt<<1,rs=rt<<1|1;
    if(minv[rs][h]>v)
      return sum[rs][h]+Query2(l,m,ls,v,h);
    else return Query2(m+1,r,rs,v,h);
}
void Update(int p,int l,int r,int rt,int v,int h)
{
    if(l==r)
    {
        if(v<0)
        {
            maxv[rt][h]=-1;minv[rt][h]=inf;
            sum[rt][h]=0;
        }
        else
        {
            maxv[rt][h]=minv[rt][h]=v;
            sum[rt][h]=1;
        }
        return;
    }
    int m=(l+r)>>1;
    if(p<=m)
      Update(p,l,m,rt<<1,v,h);
    else Update(p,m+1,r,rt<<1|1,v,h);
    PushUp(rt,h);
}
void dfs(int u)
{
    int lbg,lsm,rbg,rsm;
    int sz=querys[u].size();
    Node tmp;
    for(int i=0;i<sz;++i)
    {
        tmp=querys[u][i];
        lsm=Query1(1,n,1,tmp.w,0);
        rsm=Query1(1,n,1,tmp.w,1);
        lbg=Query2(1,n,1,tmp.w,0);
        rbg=Query2(1,n,1,tmp.w,1);
        if(cnt-lsm-rsm-lbg-rbg>0)
          ans1[tmp.u]=-1;
        else
        {
            ans1[tmp.u]=rsm;
            ans2[tmp.u]=lbg+rbg+(lsm+rsm)*3;
        }
    }
    if(lson[u]<0) return ;
    cnt++;
    Update(rnk[u],1,n,1,ww[u],0);
    dfs(lson[u]);
    Update(rnk[u],1,n,1,-1,0);
    Update(rnk[u],1,n,1,ww[u],1);
    dfs(rson[u]);
    Update(rnk[u],1,n,1,-1,1);
    cnt--;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        Init();
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&ww[i]);
            node[i].w=ww[i];
            node[i].u=i;
        }
        sort(node+1,node+n+1);
        for(int i=1;i<=n;++i)
          rnk[node[i].u]=i;
        scanf("%d",&m);
        int u,a,b;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&u,&a,&b);
            flag[a]=flag[b]=true;
            lson[u]=a;rson[u]=b;
        }
        for(int i=1;i<=n;++i)
           if(!flag[i]) {u=i;break;}
        scanf("%d",&q);
        Node tmp;
        for(int i=0;i<q;++i)
        {
            scanf("%d%d",&a,&b);
            tmp.u=i;tmp.w=b;
            querys[a].push_back(tmp);
        }
        build(1,n,1);
        lf=rn=cnt=0;
        dfs(u);
        for(int i=0;i<q;++i)
        {
            if(ans1[i]==-1)
              printf("0\n");
            else printf("%d %d\n",ans1[i],ans2[i]);
        }
    }
    return 0;
}
