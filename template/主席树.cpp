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
struct Dog
{
    int v,pos;
    bool operator < (const Dog & a) const
    {
        return v<a.v;
    }
};
Node node[maxn*20];
Dog dogs[maxn];
int root[maxn],rank[maxn],node_cnt;
int build(int l,int r)
{
    int x=node_cnt++;
    node[x].sum=0;
    if(l==r) return x;
    int m=(l+r)>>1;
    node[x].L=build(l,m);
    node[x].R=build(m+1,r);
    return x;
}
int Update(int p,int l,int r,int rt)
{
    int x=node_cnt++;
    node[x]=node[rt];
    node[x].sum++;
    if(l==r) return x;
    int m=(l+r)>>1;
    if(p<=m)
      node[x].L=Update(p,l,m,node[x].L);
    else
      node[x].R=Update(p,m+1,r,node[x].R);
    return x;
}
int Query(int r1,int r2,int l,int r,int k)
{
    if(l==r) return l;
    int tmp=node[node[r2].L].sum-node[node[r1].L].sum;
    int m=(l+r)>>1;
    if(tmp>=k) return Query(node[r1].L,node[r2].L,l,m,k);
    else return Query(node[r1].R,node[r2].R,m+1,r,k-tmp);
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
            scanf("%d",&dogs[i].v);
            dogs[i].pos=i;
        }
        sort(dogs+1,dogs+n+1);
        for(int i=1;i<=n;++i)
          rank[dogs[i].pos]=i;
        for(int i=1;i<=n;++i)
          root[i]=Update(rank[i],1,n,root[i-1]);
        int x,y,k;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&x,&y,&k);
            int ps=Query(root[x-1],root[y],1,n,k);
            printf("%d\n",dogs[ps].v);
        }
    }
    return 0;
}
