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
const int maxn=4000000+10;
struct SegTree
{
    ll sum[maxn<<2],addv[maxn<<2];
    void PushUp(int rt)
    {
        sum[rt]=sum[rt<<1]+sum[rt<<1|1];
    }
    void PushDown(int l,int r,int rt)
    {
        if(addv[rt])
        {
            addv[rt<<1]+=addv[rt];
            addv[rt<<1|1]+=addv[rt];
            int m=(l+r)>>1;
            sum[rt<<1]+=(m-l+1)*addv[rt];
            sum[rt<<1|1]+=(r-m)*addv[rt];
            addv[rt]=0;
        }
    }
    void build(int l,int r,int rt)
    {
        sum[rt]=addv[rt]=0;
        if(l==r) return ;
        int m=(l+r)>>1;
        build(l,m,rt<<1);
        build(m+1,r,rt<<1|1);
    }
    ll Query(int L,int R,int l,int r,int rt)
    {
        if(l>=L&&r<=R)
            return sum[rt];
        PushDown(l,r,rt);
        int m=(l+r)>>1;
        ll tot=0;
        if(m>=L) tot+=Query(L,R,l,m,rt<<1);
        if(m<R) tot+=Query(L,R,m+1,r,rt<<1|1);
        return tot;
    }
    void Update(int L,int R,int l,int r,int rt,ll v)
    {
        if(l>=L&&r<=R)
        {
            addv[rt]+=v;
            sum[rt]+=(r-l+1)*v;
            return ;
        }
        PushDown(l,r,rt);
        int m=(l+r)>>1;
        if(m>=L) Update(L,R,l,m,rt<<1,v);
        if(m<R) Update(L,R,m+1,r,rt<<1|1,v);
        PushUp(rt);
    }
}xsum,ysum;
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,w;
    scanf("%d%d%d",&n,&m,&w);
    xsum.build(1,n,1);
    ysum.build(1,m,1);
    int type,x1,y1,x2,y2,v;
    while(w--)
    {
        scanf("%d%d%d%d%d",&type,&x1,&y1,&x2,&y2);
        if(type==0)
        {
            scanf("%d",&v);
            xsum.Update(x1,x2,1,n,1,(ll)(y2-y1+1)*v);
            ysum.Update(y1,y2,1,m,1,(ll)(x2-x1+1)*v);
        }
        else
        {
            ll ans=xsum.Query(x1,x2,1,n,1)-ysum.Query(1,y1-1,1,m,1)-ysum.Query(y2+1,m,1,m,1);
            printf("%I64d\n",ans);
        }
    }
    return 0;
}
