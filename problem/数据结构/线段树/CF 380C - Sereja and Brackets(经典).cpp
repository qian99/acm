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
const int maxn=1000000+10;
int sum[maxn<<2],lf[maxn<<2],rn[maxn<<2];
char str[maxn];
void PushUp(int rt)
{
    int tmp=min(lf[rt<<1],rn[rt<<1|1]);
    sum[rt]=sum[rt<<1]+sum[rt<<1|1]+tmp*2;
    lf[rt]=lf[rt<<1]+lf[rt<<1|1]-tmp;
    rn[rt]=rn[rt<<1]+rn[rt<<1|1]-tmp;
}
void build(int l,int r,int rt)
{
    if(l==r)
    {
        lf[rt]=rn[rt]=sum[rt]=0;
        if(str[l-1]=='(') lf[rt]=1;
        else rn[rt]=1;
        return ;
    }
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    PushUp(rt);
}
int Query(int L,int R,int l,int r,int rt,int &lfs,int &rns)
{
    if(l>=L&&r<=R)
    {
        lfs=lf[rt];
        rns=rn[rt];
        return sum[rt];
    }
    int m=(l+r)>>1;
    if(m>=R) return Query(L,R,l,m,rt<<1,lfs,rns);
    else if(m<L) return Query(L,R,m+1,r,rt<<1|1,lfs,rns);
    else
    {
        int sum1,sum2,lf2,rn2,tmp;
        sum1=Query(L,R,l,m,rt<<1,lfs,rns);
        sum2=Query(L,R,m+1,r,rt<<1|1,lf2,rn2);
        tmp=min(lfs,rn2);
        lfs=lfs+lf2-tmp;
        rns=rns+rn2-tmp;
        return sum1+sum2+tmp*2;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    scanf("%s",str);
    n=strlen(str);
    build(1,n,1);
    int m,l,r,ltmp,rtmp;
    scanf("%d",&m);
    while(m--)
    {
        scanf("%d%d",&l,&r);
        int ans=Query(l,r,1,n,1,ltmp,rtmp);
        printf("%d\n",ans);
    }
    return 0;
}

