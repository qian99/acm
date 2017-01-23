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
const int maxn=60000+10;
struct Node
{
    int x,L,R,c;
    Node(){}
    Node(int x,int L,int R,int c):x(x),L(L),R(R),c(c){}
    bool operator <(const Node &a) const
    {
        return x<a.x;
    }
}node[maxn<<1];
int sum[maxn<<2][11],cover[maxn<<2],num[maxn<<1],k;
map<int,int>mp;
inline void PushUp(int l,int r,int rt)
{
    if(cover[rt]>k) sum[rt][k]=num[r]-num[l-1];
    else if(l==r)
    {
        memset(sum[rt],0,sizeof(sum[rt]));
        sum[rt][cover[rt]]=num[r]-num[l-1];
    }
    else
    {
        memset(sum[rt],0,sizeof(sum[rt]));
        for(int i=cover[rt];i<=k;++i)
            sum[rt][i]=sum[rt<<1][i-cover[rt]]+sum[rt<<1|1][i-cover[rt]];
        for(int i=k-cover[rt]+1;i<=k;++i)
            sum[rt][k]+=sum[rt<<1][i]+sum[rt<<1|1][i];
    }
}
void build(int l,int r,int rt)
{
    cover[rt]=0;
    memset(sum[rt],0,sizeof(sum[rt]));
    sum[rt][0]=num[r]-num[l-1];
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
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    int n,tot,N;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        scanf("%d%d",&n,&k);
        int x1,y1,x2,y2;
        tot=0;
        for(int i=0;i<n;++i)
        {
            scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
            num[tot++]=y1;
            num[tot++]=y2+1;
            node[i]=Node(x1,y1,y2+1,1);
            node[i+n]=Node(x2+1,y1,y2+1,-1);
        }
        sort(num,num+tot);
        sort(node,node+tot);
        N=unique(num,num+tot)-num;
        num[N]=num[N-1];
        mp.clear();
        for(int i=0;i<N;++i)
            mp[num[i]]=i+1;
        build(1,N,1);
        ll ans=0;
        int L,R;
        for(int i=0;i<tot-1;++i)
        {
            L=mp[node[i].L];
            R=mp[node[i].R]-1;
            Update(L,R,1,N,1,node[i].c);
            ans+=(ll)sum[1][k]*(node[i+1].x-node[i].x);
        }
        printf("Case %d: %lld\n",tcase,ans);
    }
    return 0;
}
