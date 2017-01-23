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
const int mod=9;
int msk[maxn<<2],sum[maxn<<2],pre[maxn<<2],suff[maxn<<2];
int num[maxn],val[1024][1024];
void Init()
{
    int z;
    for(int x=0;x<(1<<10);++x)
        for(int y=0;y<(1<<10);++y)
        {
            val[x][y]=0;
            for(int i=0;i<=mod;++i)
                if(x&(1<<i))
                for(int j=0;j<=mod;++j)
                    if(y&(1<<j))
                    {
                        z=i+j;
                        if(z>=mod)
                        {
                            z-=mod;
                            if(z==0) z=mod;
                        }
                        val[x][y]|=(1<<z);
                    }
        }
}
inline int cal(int x,int y) {return val[x][y];}
inline void PushUp(int rt)
{
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
    if(sum[rt]>=mod)
    {
        sum[rt]-=mod;
        if(sum[rt]==0) sum[rt]=mod;
    }
    msk[rt]=msk[rt<<1]|msk[rt<<1|1];
    msk[rt]|=cal(suff[rt<<1],pre[rt<<1|1]);
    pre[rt]=pre[rt<<1]|cal(1<<sum[rt<<1],pre[rt<<1|1]);
    suff[rt]=suff[rt<<1|1]|cal(1<<sum[rt<<1|1],suff[rt<<1]);
}
void build(int l,int r,int rt)
{
    if(l==r)
    {
        if(num[l])
        {
            num[l]%=mod;
            if(num[l]==0) num[l]=mod;
        }
        sum[rt]=num[l];
        msk[rt]=pre[rt]=suff[rt]=1<<sum[rt];
        return ;
    }
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    PushUp(rt);
}
int Query(int L,int R,int l,int r,int rt,int &p,int &f,int &s)
{
    if(l>=L&&r<=R)
    {
        p=pre[rt];
        f=suff[rt];
        s=sum[rt];
        return msk[rt];
    }
    int m=(l+r)>>1;
    if(m>=R) return Query(L,R,l,m,rt<<1,p,f,s);
    else if(m<L) return Query(L,R,m+1,r,rt<<1|1,p,f,s);
    else
    {
        int p1,p2,f1,f2,s1,s2,m1,m2;
        m1=Query(L,R,l,m,rt<<1,p1,f1,s1);
        m2=Query(L,R,m+1,r,rt<<1|1,p2,f2,s2);
        s=s1+s2;
        if(s>=mod)
        {
            s-=mod;
            if(s==0) s=mod;
        }
        p=p1|cal(1<<s1,p2);
        f=f2|cal(1<<s2,f1);
        return (m1|m2)|cal(f1,p2);
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    Init();
    scanf("%d",&t);
    while(t--)
    {
        if(tcase) printf("\n");
        tcase++;
        int n,m;
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
            scanf("%d",&num[i]);
        build(1,n,1);
        scanf("%d",&m);
        printf("Case #%d:\n",tcase);
        int L,R,p,f,s,res,tot;
        while(m--)
        {
            scanf("%d%d",&L,&R);
            res=Query(L,R,1,n,1,p,f,s);
            tot=5;
            for(int i=mod;i>=0&&tot;--i)
                if(res&(1<<i))
                {
                    if(tot<5) printf(" ");
                    printf("%d",i);
                    tot--;
                }
            while(tot)
            {
                if(tot<5) printf(" ");
                printf("-1");
                tot--;
            }
            printf("\n");
        }
    }
    return 0;
}
