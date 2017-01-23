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
const int maxn=(200000+10)<<2;
int point[maxn];
void setMax(int rt)
{
    point[rt]=max(point[rt<<1],point[rt<<1|1]);
}
void build(int l,int r,int rt)
{
    if(l==r)
    {
        scanf("%d",&point[rt]);
        return ;
    }
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    setMax(rt);
}
int Query(int L,int R,int l,int r,int rt)
{
    if(l>=L&&r<=R)
    {
        return point[rt];
    }
    int m=(l+r)>>1;
    int u=0;
    if(m>=L)
       u=max(u,Query(L,R,l,m,rt<<1));
    if(m<R)
       u=max(u,Query(L,R,m+1,r,rt<<1|1));
    return u;
}
void Update(int p,int value,int l,int r,int rt)
{
    if(l==r)
    {
        point[rt]=value;return;
    }
    int m=(l+r)>>1;
    if(p<=m)
      Update(p,value,l,m,rt<<1);
    else
      Update(p,value,m+1,r,rt<<1|1);
    setMax(rt);
}

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        build(1,n,1);
        char c[2];
        int a,b;
        while(m--)
        {
            scanf("%s%d%d",c,&a,&b);
            if(c[0]=='Q')
              printf("%d\n",Query(a,b,1,n,1));
            else
            Update(a,b,1,n,1);
        }
    }
    return 0;
}
