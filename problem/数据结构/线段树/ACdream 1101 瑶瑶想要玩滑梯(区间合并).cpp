/*
* this code is made by qian99
* Problem: 1101
* Verdict: Accepted
* Submission Date: 2014-06-14 22:26:35
* Time: 3204 MS
* Memory: 21208 KB
*/
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
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=200000+10;
int num[maxn];
int sum[maxn<<2],pre[maxn<<2],prev[maxn<<2];
int suff[maxn<<2],suffv[maxn<<2],setv[maxn<<2];
void PushUp(int l,int r,int rt)
{
    sum[rt]=max(sum[rt<<1],sum[rt<<1|1]);
    if(suffv[rt<<1]<prev[rt<<1|1])
        sum[rt]=max(sum[rt],suff[rt<<1]+pre[rt<<1|1]);
 
    int m=(l+r)>>1;
    pre[rt]=pre[rt<<1];
    prev[rt]=prev[rt<<1];
    if((m-l+1)==pre[rt<<1]&&suffv[rt<<1]<prev[rt<<1|1])
        pre[rt]=(m-l+1)+pre[rt<<1|1];
 
    suff[rt]=suff[rt<<1|1];
    suffv[rt]=suffv[rt<<1|1];
    if((r-m)==suff[rt<<1|1]&&suffv[rt<<1]<prev[rt<<1|1])
        suff[rt]=(r-m)+suff[rt<<1];
}
void PushDown(int rt)
{
    if(setv[rt]!=-inf)
    {
        setv[rt<<1]=setv[rt<<1|1]=setv[rt];
        pre[rt<<1]=suff[rt<<1]=sum[rt<<1]=1;
        pre[rt<<1|1]=suff[rt<<1|1]=sum[rt<<1|1]=1;
        prev[rt<<1]=suffv[rt<<1]=setv[rt];
        prev[rt<<1|1]=suffv[rt<<1|1]=setv[rt];
        setv[rt]=-inf;
    }
}
void build(int l,int r,int rt)
{
    setv[rt]=-inf;
    if(l==r)
    {
        sum[rt]=pre[rt]=suff[rt]=1;
        prev[rt]=suffv[rt]=num[l];
        return ;
    }
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    PushUp(l,r,rt);
}
void Update(int L,int R,int l,int r,int rt,int v)
{
    if(l>=L&&r<=R)
    {
        sum[rt]=pre[rt]=suff[rt]=1;
        prev[rt]=suffv[rt]=v;
        setv[rt]=v;
        return ;
    }
    PushDown(rt);
    int m=(l+r)>>1;
    if(m>=L) Update(L,R,l,m,rt<<1,v);
    if(m<R) Update(L,R,m+1,r,rt<<1|1,v);
    PushUp(l,r,rt);
}
void Query(int L,int R,int l,int r,int rt,int &sans,int &psum,int& pval,int &ssum,int &sval)
{
    if(l>=L&&r<=R)
    {
        sans=sum[rt];
        psum=pre[rt];pval=prev[rt];
        ssum=suff[rt];sval=suffv[rt];
        return ;
    }
    PushDown(rt);
    int m=(l+r)>>1;
    if(m>=R) Query(L,R,l,m,rt<<1,sans,psum,pval,ssum,sval);
    else if(m<L) Query(L,R,m+1,r,rt<<1|1,sans,psum,pval,ssum,sval);
    else
    {
        int Lsans,Lpsum,Lpval,Lssum,Lsval;
        int Rsans,Rpsum,Rpval,Rssum,Rsval;
        Query(L,R,l,m,rt<<1,Lsans,Lpsum,Lpval,Lssum,Lsval);
        Query(L,R,m+1,r,rt<<1|1,Rsans,Rpsum,Rpval,Rssum,Rsval);
 
        sans=max(Lsans,Rsans);
        if(Lsval<Rpval)
            sans=max(sans,Lssum+Rpsum);
 
        psum=Lpsum;
        pval=Lpval;
        if((m-max(L,l)+1)==Lpsum&&Lsval<Rpval)
            psum=(m-max(L,l)+1)+Rpsum;
 
        ssum=Rssum;
        sval=Rsval;
        if((min(R,r)-m)==Rssum&&Lsval<Rpval)
            ssum=(min(R,r)-m)+Lssum;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    char str[5];
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
        scanf("%d",&num[i]);
    build(1,n,1);
    int L,R,x;
    while(m--)
    {
        scanf("%s",str);
        scanf("%d%d",&L,&R);
        if(L>R) swap(L,R);
        if(str[0]=='Q')
        {
            int res,a,b,c,d;
            Query(L,R,1,n,1,res,a,b,c,d);
            printf("%d\n",res);
        }
        else
        {
            scanf("%d",&x);
            Update(L,R,1,n,1,x);
        }
    }
    return 0;
}