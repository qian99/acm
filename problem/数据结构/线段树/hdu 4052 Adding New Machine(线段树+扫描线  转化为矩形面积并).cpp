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
    int x,L,R,c;
    Node(){}
    Node(int x,int L,int R,int c):x(x),L(L),R(R),c(c){}
    bool operator <(const Node &a) const
    {
        return x<a.x;
    }
}node[maxn];
struct Mat
{
    int x1,y1,x2,y2;
    void read()
    {
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        if(x1>x2) swap(x1,x2);
        if(y1>y2) swap(y1,y2);
    }
}mat[maxn];
map<int,int>mp;
int num[maxn];
int sum[maxn<<2],cover[maxn<<2];
inline void PushUp(int l,int r,int rt)
{
    if(cover[rt]) sum[rt]=num[r]-num[l-1];
    else if(l==r) sum[rt]=0;
    else sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
void build(int l,int r,int rt)
{
    sum[rt]=cover[rt]=0;
    if(l==r) return ;
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
}
void Update(int L,int R,int l,int r,int rt,int v)
{
    if(l>=L&&r<=R)
    {
        cover[rt]+=v;
        PushUp(l,r,rt);
        return ;
    }
    int m=(l+r)>>1;
    if(m>=L) Update(L,R,l,m,rt<<1,v);
    if(m<R) Update(L,R,m+1,r,rt<<1|1,v);
    PushUp(l,r,rt);
}
ll solve(int W,int H,int n,int m)
{
    if(m>H) return 0;
    mp.clear();
    int tot=0,L,R,N;
    for(int i=0;i<n;++i)
    {
        L=mat[i].y1;
        R=min(H,mat[i].y2+m-1)+1;
        num[tot++]=L;
        num[tot++]=R;
        node[i]=Node(mat[i].x1,L,R,1);
        node[i+n]=Node(mat[i].x2+1,L,R,-1);
    }
    L=1;
    R=min(H,m-1)+1;
    if(L<=R)
    {
        node[tot]=Node(1,L,R,1);
        num[tot++]=L;
        node[tot]=Node(W+1,L,R,-1);
        num[tot++]=R;
    }
    sort(num,num+tot);
    sort(node,node+tot);
    ll ans=0;
    N=unique(num,num+tot)-num;
    for(int i=0;i<N;++i)
        mp[num[i]]=i+1;
    if(N) build(1,N,1);
    for(int i=0;i<tot-1;++i)
    {
        L=mp[node[i].L];
        R=mp[node[i].R]-1;
        if(L<=R) Update(L,R,1,N,1,node[i].c);
        ans+=(ll)sum[1]*(node[i+1].x-node[i].x);
    }
    ans=(ll)H*W-ans;
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int W,H,n,m;
    while(~scanf("%d%d%d%d",&W,&H,&n,&m))
    {
        for(int i=0;i<n;++i)
            mat[i].read();
        ll ans=solve(W,H,n,m);
        for(int i=0;i<n;++i)
        {
            swap(mat[i].x1,mat[i].y1);
            swap(mat[i].x2,mat[i].y2);
        }
        swap(W,H);
        ans+=solve(W,H,n,m);
        if(m==1) ans/=2;
        printf("%I64d\n",ans);
    }
    return 0;
}
