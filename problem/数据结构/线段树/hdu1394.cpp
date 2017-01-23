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
const int maxn=5000+10;
int num[maxn];
int sum[maxn<<2];
void Pushup(int rt)
{
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
void build(int l,int r,int rt)
{
    sum[rt]=0;
    if(l==r)return;
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
}
int Query(int L,int R,int l,int r,int rt)
{
    if(l>=L&&r<=R)
    {
        return sum[rt];
    }
    int m=(l+r)>>1;
    int u=0;
    if(m>=L)
      u+=Query(L,R,l,m,rt<<1);
    if(m<R)
      u+=Query(L,R,m+1,r,rt<<1|1);
    return u;
}
void Update(int p,int l,int r,int rt)
{
    if(l==r)
    {
        sum[rt]++;
        return;
    }
    int m=(l+r)>>1;
    if(p<=m)
      Update(p,l,m,rt<<1);
    else
      Update(p,m+1,r,rt<<1|1);
    Pushup(rt);
}

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        build(0,n-1,1);
        int r=0;
        for(int i=0;i<n;++i)
        {
            scanf("%d",&num[i]);
            r+=Query(num[i],n-1,0,n-1,1);
            Update(num[i],0,n-1,1);
        }
        int ans=r;
        for(int i=0;i<n;++i)
        {
            r=r-num[i]+(n-num[i]-1);
            ans=min(r,ans);
        }
        printf("%d\n",ans);
    }
    return 0;
}
