#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
const int maxn=500000+50;
int id;
int sum[maxn<<2],num[maxn];
struct Children
{
    char name[11];
    int next;
};
Children child[maxn];

void Pushup(int rt)
{
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
void build(int l,int r,int rt)
{
    if(l==r)
    {
        sum[rt]=1;
        return ;
    }
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    Pushup(rt);
}
int Query(int L,int R,int l,int r,int rt)
{
    if(l>=L&&r<=R)
    {
        return sum[rt];
    }
    int m=(r+l)>>1;
    int u=0;
    if(m>=L)
      u+=Query(L,R,l,m,rt<<1);
    if(m<R)
      u+=Query(L,R,m+1,r,rt<<1|1);
    return u;
}
void Query2(int v,int l,int r,int rt)
{
    if(l==r)
    {
        id=l;
        return;
    }
    int m=(l+r)>>1;
    if(sum[rt<<1]>=v)
       Query2(v,l,m,rt<<1);
    else
    {
        v-=sum[rt<<1];
        Query2(v,m+1,r,rt<<1|1);
    }
}
void Update(int p,int l,int r,int rt)
{
    if(l==r)
    {
        sum[rt]=0;
        return;
    }
    int m=(l+r)>>1;
    if(p<=m)
       Update(p,l,m,rt<<1);
    else
       Update(p,m+1,r,rt<<1|1);
    Pushup(rt);
}
int yue(int w)
{
    int t=0;
    for(int i=1;i<=w;++i)
    {
        if(w%i==0) t++;
    }
    return t;
}

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int mxd=1,mxp=1;
    for(int i=1;i<=500040;++i)
        num[i]=2;
    num[1]=1;
    for(int i=2;i<=250020;++i)
    {
        for(int j=2;i*j<=500040;++j)
        {
            num[i*j]++;
        }
    }
    for(int i=1;i<=500040;++i)
    {
        if(num[i]>mxd)
        {
            mxd=num[i];
            mxp=i;
            num[i]=i;
        }
        else
        {
            num[i]=mxp;
        }
    }
    int n,k;
    while(~scanf("%d%d",&n,&k))
    {
        for(int i=1;i<=n;++i)
        {
            scanf("%s%d",child[i].name,&child[i].next);
        }
        build(1,n,1);
        int p=k;
        int m=n;
        int d=n-num[n];
        if(d==0) d=1;
        while(m>d)
        {
            Update(p,1,n,1);
            int u=child[p].next;
            m--;
            if(u<0)
            {
                u=-u;
                u%=m;
                if(u==0) u=m;
                int b=Query(1,p,1,n,1);
                if(b>=u)
                   Query2(b-u+1,1,n,1);
                else
                {
                    u-=b;
                    int r=Query(p,n,1,n,1);
                    Query2(r-u+1+Query(1,p,1,n,1),1,n,1);
                }
            }
            else
            {
                u%=m;
                if(u==0) u=m;
                int b=Query(p,n,1,n,1);
                if(b>=u)
                Query2(u+Query(1,p,1,n,1),1,n,1);
                else
                {
                    u-=b;
                    Query2(u,1,n,1);
                }
            }
            if(m>d)
            p=id;
        }
        if(n-num[n]==0)
        {
            Query2(1,1,n,1);
            p=id;
        }
        printf("%s %d\n",child[p].name,yue(num[n]));
    }
    return 0;
}

