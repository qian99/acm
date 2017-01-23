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
const int maxn=100000+10;
struct Node
{
    int L,R;
    int sum;
};
struct Num
{
    int v,pos;
    bool operator <(const Num &a) const
    {
        return v<a.v;
    }
};
Node node[maxn*20];
Num a[maxn];
int node_cnt;
int rank[maxn],root[maxn];
int build(int l,int r)
{
    if(l==r)
    {
        node[node_cnt++].sum=0;
        return node_cnt-1;
    }
    int m=(l+r)>>1;
    int x;
    node[node_cnt++].sum=0;
    x=node_cnt-1;
    node[x].L=build(l,m);
    node[x].R=build(m+1,r);
    return x;
}
int insert(int p,int l,int r,int rt)
{
    node[node_cnt++]=node[rt];
    int x=node_cnt-1;
    node[x].sum++;
    if(l==r)
    {
        return x;
    }
    int m=(l+r)>>1;
    if(m>=p)
      node[x].L=insert(p,l,m,node[x].L);
    else
      node[x].R=insert(p,m+1,r,node[x].R);
    return x;
}
int Query(int r1,int r2,int l,int r,int k)
{
    if(l==r) return l;
    int m=(l+r)>>1;
    int tmp=node[node[r2].L].sum-node[node[r1].L].sum;
    if(tmp>=k)
      return Query(node[r1].L,node[r2].L,l,m,k);
    else
      return Query(node[r1].R,node[r2].R,m+1,r,k-tmp);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        node_cnt=0;
        root[0]=build(1,n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i].v);
            a[i].pos=i;
        }
        sort(a+1,a+n+1);
        for(int i=1;i<=n;++i)
          rank[a[i].pos]=i;
        for(int i=1;i<=n;++i)
          root[i]=insert(rank[i],1,n,root[i-1]);
        int x,y,k,ps;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&x,&y,&k);
            ps=Query(root[x-1],root[y],1,n,k);
            printf("%d\n",a[ps].v);
        }
    }
    return 0;
}
