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
const int maxn=100000+10;
int sum[maxn<<2],lf[maxn],rn[maxn];
int val[maxn],color[maxn],lz[maxn];
inline void PushUp(int rt)
{
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
void build(int l,int r,int rt)
{
    if(l==r)
    {
        if(color[l]==0) sum[rt]=1;
        else sum[rt]=0;
        return ;
    }
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    PushUp(rt);
}
void Update(int p,int l,int r,int rt)
{
    if(l==r)
    {
        sum[rt]^=1;
        return ;
    }
    int m=(l+r)>>1;
    if(m>=p) Update(p,l,m,rt<<1);
    else Update(p,m+1,r,rt<<1|1);
    PushUp(rt);
}
int Query(int L,int R,int l,int r,int rt)
{
    if(L>R) return 0;
    if(l>=L&&r<=R)
    {
        return sum[rt];
    }
    int m=(l+r)>>1;
    int res=0;
    if(m>=L) res+=Query(L,R,l,m,rt<<1);
    if(m<R) res+=Query(L,R,m+1,r,rt<<1|1);
    return res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n,m,K;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d",&n,&m,&K);
        for(int i=1;i<=n;++i)
            scanf("%d",&val[i]);
        for(int i=1;i<=n;++i)
            scanf("%d",&color[i]);
        build(1,n,1);
        lf[0]=-1;rn[n+1]=-1;
        for(int i=1;i<=n;++i)
            if(val[i]<K) lf[i]=i;
            else lf[i]=lf[i-1];
        for(int i=n;i>=1;--i)
            if(val[i]<K) rn[i]=i;
            else rn[i]=rn[i+1];
        lz[0]=0;
        for(int i=1;i<=n;++i)
            lz[i]=lz[i-1]+(color[i]==0);
        ll ans=0;
        int L,R;
        for(int i=1;i<=n;++i)
        {
            L=lf[i];
            if(L!=-1)
            {
                if(color[i]) ans+=lz[L];
                else ans+=L-lz[L];
            }
        }
        int type,pos,tmp;
        while(m--)
        {
            scanf("%d",&type);
            if(type) printf("%I64d\n",ans);
            else
            {
                scanf("%d",&pos);
                L=lf[pos];
                R=rn[pos];
                if(L!=-1)
                {
                    if(pos==L) L--;
                    tmp=Query(1,L,1,n,1);
                    if(color[pos])
                        ans+=((L-tmp)-tmp);
                    else
                        ans+=(tmp-(L-tmp));
                }
                if(R!=-1)
                {
                    if(pos==R) R++;
                    tmp=Query(R,n,1,n,1);
                    if(color[pos])
                        ans+=((n-R+1)-tmp-tmp);
                    else
                        ans+=(tmp-((n-R+1)-tmp));
                }
                Update(pos,1,n,1);
                color[pos]^=1;
            }
        }
    }
    return 0;
}
