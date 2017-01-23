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
const int maxn=30000+10;
struct Node
{
    int L,R;
    int sum;
}node[maxn*20];
int pre[1000010],n;
int root[maxn],node_cnt;
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
int Update(int p,int l,int r,int rt,int v)
{
    int x=node_cnt++;
    node[x]=node[rt];
    node[x].sum+=v;
    if(l==r) return x;
    int m=(l+r)>>1;
    if(p<=m)
      node[x].L=Update(p,l,m,node[x].L,v);
    else
      node[x].R=Update(p,m+1,r,node[x].R,v);
    return x;
}
int Query(int rt,int l,int r,int p)
{
    if(l==r) return node[rt].sum;
    int m=(l+r)>>1;
    if(p<=m)
      return node[node[rt].R].sum+Query(node[rt].L,l,m,p);
    else
      return Query(node[rt].R,m+1,r,p);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d",&n))
    {
        memset(pre,0xff,sizeof(pre));
        node_cnt=0;
        root[0]=build(1,n);
        int num;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&num);
            if(pre[num]==-1)
              root[i]=Update(i,1,n,root[i-1],1);
            else
            {
                int tmp=Update(pre[num],1,n,root[i-1],-1);
                root[i]=Update(i,1,n,tmp,1);
            }
            pre[num]=i;
        }
        int q,l,r;
        scanf("%d",&q);
        while(q--)
        {
            scanf("%d%d",&l,&r);
            int ans=Query(root[r],1,n,l);
            printf("%d\n",ans);
        }
    }
    return 0;
}
