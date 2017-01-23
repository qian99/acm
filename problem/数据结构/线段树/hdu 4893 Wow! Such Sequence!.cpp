#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<set>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100000+10;
int fcnt;
ll sum[maxn<<2],Fibo[maxn];
int flag[maxn<<2];
void getFibo()
{
    Fibo[0]=Fibo[1]=1;
    fcnt=1;
    for(int i=2;i<maxn;++i)
    {
        Fibo[i]=Fibo[i-1]+Fibo[i-2];
        if(Fibo[i]>Inf) break;
        fcnt++;
    }
}
void PushUp(int rt)
{
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
    flag[rt]=flag[rt<<1]+flag[rt<<1|1];
}
void build(int l,int r,int rt)
{
    sum[rt]=flag[rt]=0;
    if(l==r)
    {
        return ;
    }
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
}
void Update(int L,int R,int l,int r,int rt)
{
    if(l>=L&&r<=R&&flag[rt]==r-l+1) return ;
    if(l==r)
    {
        int pos=lower_bound(Fibo,Fibo+fcnt,sum[rt])-Fibo;
        if(pos-1>=0&&sum[rt]-Fibo[pos-1]<=Fibo[pos]-sum[rt])
            sum[rt]=Fibo[pos-1];
        else sum[rt]=Fibo[pos];
        flag[rt]=1;
        return ;
    }
    int m=(l+r)>>1;
    if(m>=L) Update(L,R,l,m,rt<<1);
    if(m<R) Update(L,R,m+1,r,rt<<1|1);
    PushUp(rt);
}
void Changes(int p,int l,int r,int rt,int v)
{
    if(l==r)
    {
        sum[rt]+=v;
        int pos=lower_bound(Fibo,Fibo+fcnt,sum[rt])-Fibo;
        if(sum[rt]==Fibo[pos]) flag[rt]=1;
        else flag[rt]=0;
        return ;
    }
    int m=(l+r)>>1;
    if(m>=p) Changes(p,l,m,rt<<1,v);
    else Changes(p,m+1,r,rt<<1|1,v);
    PushUp(rt);
}
ll Query(int L,int R,int l,int r,int rt)
{
    if(l>=L&&r<=R) return sum[rt];
    int m=(l+r)>>1;
    ll res=0;
    if(m>=L) res+=Query(L,R,l,m,rt<<1);
    if(m<R) res+=Query(L,R,m+1,r,rt<<1|1);
    return res;
}

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    getFibo();
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        build(1,n,1);
        int type,l,r;
        while(m--)
        {
            scanf("%d%d%d",&type,&l,&r);
            if(type==1) Changes(l,1,n,1,r);
            else if(type==3) Update(l,r,1,n,1);
            else printf("%I64d\n",Query(l,r,1,n,1));
        }
    }
    return 0;
}
