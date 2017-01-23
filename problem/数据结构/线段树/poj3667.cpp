#include <iostream>
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
//typedef long long ll;
const int maxn=50000+10;
int tsum[maxn<<2],presum[maxn<<2],fixsum[maxn<<2],setv[maxn<<2];
void PushUp(int l,int r,int rt)
{
    int ls=rt<<1,rs=rt<<1|1;
    int m=(l+r)>>1;
    tsum[rt]=max(tsum[ls],tsum[rs]);
    tsum[rt]=max(tsum[rt],fixsum[ls]+presum[rs]);
    presum[rt]=presum[ls];
    if(presum[ls]==m-l+1) presum[rt]+=presum[rs];
    fixsum[rt]=fixsum[rs];
    if(fixsum[rs]==r-m) fixsum[rt]+=fixsum[ls];
}
void PushDown(int l,int r,int rt)
{
    if(setv[rt]>=0)
    {
        int m=(l+r)>>1;
        int ls=rt<<1,rs=rt<<1|1;
        setv[ls]=setv[rs]=setv[rt];
        presum[ls]=fixsum[ls]=tsum[ls]=setv[rt]?0:m-l+1;
        presum[rs]=fixsum[rs]=tsum[rs]=setv[rt]?0:r-m;
        setv[rt]=-1;
    }
}
void build(int l,int r,int rt)
{
    tsum[rt]=presum[rt]=fixsum[rt]=r-l+1;
    setv[rt]=-1;
    if(l==r) return;
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
}
int Query(int v,int l,int r,int rt)
{
    if(l==r) return l;
    PushDown(l,r,rt);
    int m=(l+r)>>1;
    int ls=rt<<1,rs=rt<<1|1;
    if(tsum[ls]>=v) return Query(v,l,m,ls);
    if(presum[rs]+fixsum[ls]>=v) return m-fixsum[ls]+1;
    return Query(v,m+1,r,rs);
}
void Update(int v,int L,int R,int l,int r,int rt)
{
    if(l>=L&&r<=R)
    {
        setv[rt]=v;
        presum[rt]=fixsum[rt]=tsum[rt]=v?0:r-l+1;
        return;
    }
    int m=(l+r)>>1;
    PushDown(l,r,rt);
    if(m>=L)
       Update(v,L,R,l,m,rt<<1);
    if(m<R)
       Update(v,L,R,m+1,r,rt<<1|1);
    PushUp(l,r,rt);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        int type,v,x,d;
        build(1,n,1);
        while(m--)
        {
            scanf("%d",&type);
            if(type==1)
            {
                scanf("%d",&v);
                if(tsum[1]<v)
                {
                    printf("0\n");
                    continue;
                }
                int res=Query(v,1,n,1);
                Update(1,res,res+v-1,1,n,1);
                printf("%d\n",res);
            }
            else
            {
                scanf("%d%d",&x,&d);
                Update(0,x,x+d-1,1,n,1);
            }
        }
    }
    return 0;
}
