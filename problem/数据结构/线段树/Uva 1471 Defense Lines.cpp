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
#include<bitset>
#include<set>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=200000+10;
int num[maxn],pre[maxn],suff[maxn],maxv[maxn<<2];
struct Node
{
    int x,val,id;
    Node(int x=0,int val=0,int id=0):x(x),val(val),id(id){}
    bool operator <(const Node &a) const
    {
        return x<a.x;
    }
}node[maxn];
inline void PushUp(int rt)
{
    maxv[rt]=max(maxv[rt<<1],maxv[rt<<1|1]);
}
void build(int l,int r,int rt)
{
    maxv[rt]=0;
    if(l==r) return ;
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
}
void Update(int p,int l,int r,int rt,int v)
{
    if(l==r)
    {
        maxv[rt]=max(maxv[rt],v);
        return ;
    }
    int m=(l+r)>>1;
    if(m>=p) Update(p,l,m,rt<<1,v);
    else Update(p,m+1,r,rt<<1|1,v);
    PushUp(rt);
}
int Query(int L,int R,int l,int r,int rt)
{
    if(l>=L&&r<=R) return maxv[rt];
    int m=(l+r)>>1;
    int res=0;
    if(m>=L) res=max(res,Query(L,R,l,m,rt<<1));
    if(m<R) res=max(res,Query(L,R,m+1,r,rt<<1|1));
    return res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        pre[0]=suff[n+1]=0;
        num[0]=0;num[n+1]=inf;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&num[i]);
            if(num[i]>num[i-1]) pre[i]=pre[i-1]+1;
            else pre[i]=1;
            node[i]=Node(num[i],pre[i],i);
        }
        for(int i=n;i>=1;--i)
            if(num[i]<num[i+1]) suff[i]=suff[i+1]+1;
            else suff[i]=1;
        sort(node+1,node+n+1);
        build(0,n,1);
        int ans=0,tmp;
        for(int i=1;i<=n;)
        {
            int j=i;
            while(j<=n&&node[j].x==node[i].x)
            {
                tmp=Query(0,node[j].id-1,0,n,1);
                ans=max(tmp+suff[node[j].id],ans);
                j++;
            }
            for(;i<j;++i)
                Update(node[i].id,0,n,1,node[i].val);
        }
        printf("%d\n",ans);
    }
    return 0;
}
