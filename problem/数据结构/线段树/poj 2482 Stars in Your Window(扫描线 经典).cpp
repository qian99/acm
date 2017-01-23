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
const int maxn=20000+10;
struct Node
{
    ll x,L,R,val;
    Node(){}
    Node(ll x,ll L,ll R,ll val) :x(x),L(L),R(R),val(val){}
    bool operator <(const Node &a) const
    {
        if(x==a.x) return val<a.val;
        return x<a.x;
    }
}node[maxn];
map<ll,int>mp;
ll maxv[maxn<<2],addv[maxn<<2],num[maxn];
inline void PushUp(int rt)
{
    maxv[rt]=max(maxv[rt<<1],maxv[rt<<1|1]);
}
inline void PushDown(int rt)
{
    if(addv[rt])
    {
        addv[rt<<1]+=addv[rt];
        addv[rt<<1|1]+=addv[rt];
        maxv[rt<<1]+=addv[rt];
        maxv[rt<<1|1]+=addv[rt];
        addv[rt]=0;
    }
}
void build(int l,int r,int rt)
{
    maxv[rt]=addv[rt]=0;
    if(l==r) return ;
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
}
void Update(int L,int R,int l,int r,int rt,ll v)
{
    if(l>=L&&r<=R)
    {
        addv[rt]+=v;
        maxv[rt]+=v;
        return ;
    }
    int m=(l+r)>>1;
    PushDown(rt);
    if(m>=L) Update(L,R,l,m,rt<<1,v);
    if(m<R) Update(L,R,m+1,r,rt<<1|1,v);
    PushUp(rt);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,W,H;
    while(~scanf("%d%d%d",&n,&W,&H))
    {
        mp.clear();
        int tot=0,x,y,c;
        for(int i=0;i<n;++i)
        {
            scanf("%d%d%d",&x,&y,&c);
            num[tot++]=y;
            num[tot++]=(ll)y+H-1;
            node[i]=Node(x,y,(ll)y+H-1,c);
            node[i+n]=Node((ll)x+W,y,(ll)y+H-1,-c);
        }
        sort(num,num+tot);
        sort(node,node+tot);
        int N=unique(num,num+tot)-num;
        for(int i=0;i<N;++i)
            mp[num[i]]=i+1;
        build(1,N,1);
        ll ans=0;
        for(int i=0;i<tot;++i)
        {
            int L=mp[node[i].L];
            int R=mp[node[i].R];
            Update(L,R,1,N,1,node[i].val);
            ans=max(ans,maxv[1]);
        }
        printf("%I64d\n",ans);
    }
    return 0;
}
