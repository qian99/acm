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
const int maxn=200000+10;
int sum[maxn<<2];
void getMax(int rt)
{
    sum[rt]=max(sum[rt<<1],sum[rt<<1|1]);
}
void build(int l,int r,int rt,int w)
{
    sum[rt]=w;
    if(l==r) return;
    int m=(r+l)>>1;
    build(l,m,rt<<1,w);
    build(m+1,r,rt<<1|1,w);
}
int Query(int value,int l,int r,int rt)
{
    if(l==r)
    {
        sum[rt]-=value;
        return l;
    }
    int m=(l+r)>>1;
    int u=r;
    if(value<=sum[rt<<1])
       u=min(Query(value,l,m,rt<<1),u);
    else
       u=min(u,Query(value,m+1,r,rt<<1|1));
    getMax(rt);
    return u;

}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,w,h;
    while(~scanf("%d%d%d",&h,&w,&n))
    {
        if(h>n) h=n;
        build(1,n,1,w);
        int temp;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&temp);
            if(sum[1]<temp)
            {
                printf("-1\n");continue;
            }
            printf("%d\n",Query(temp,1,h,1));
        }
    }
    return 0;
}
