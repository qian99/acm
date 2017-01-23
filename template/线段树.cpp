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
const int maxn=50005<<2;
int sum[maxn];
char str[10];
void Pushup(int rt)
{
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
void build(int l,int r,int rt)
{
    if(l==r)
    {
        scanf("%d",&sum[rt]);
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
    int m=(l+r)>>1;
    int u=0;
    if(L<=m)
       u+=Query(L,R,l,m,rt<<1);
    if(m<R)
       u+=Query(L,R,m+1,r,rt<<1|1);
    return u;
}
void Update(int p,int value,int l,int r,int rt)
{
    if(l==r)
    {
        sum[rt]+=value;
        return ;
    }
    int m=(l+r)>>1;
    if(m>=p)
       Update(p,value,l,m,rt<<1);
    else
       Update(p,value,m+1,r,rt<<1|1);
    Pushup(rt);
}

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        scanf("%d",&n);
        build(1,n,1);
        printf("Case %d:\n",tcase);
        while(~scanf("%s",str))
        {
            int a,b;
            if(str[0]=='E')
               break;
            scanf("%d%d",&a,&b);
            if(str[0]=='Q')
               printf("%d\n",Query(a,b,1,n,1));
            if(str[0]=='A')
               Update(a,b,1,n,1);
            if(str[0]=='S')
               Update(a,-b,1,n,1);
        }
    }
    return 0;
}
