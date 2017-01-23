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
const int maxn=50000+10;
int sum[maxn<<2],set[maxn<<2],zz[maxn<<2];
void PushUp(int rt)
{
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
    zz[rt]=min(zz[rt<<1],zz[rt<<1|1]);
}
void PushDown(int l,int r,int rt)
{
    int m=(l+r)>>1;
    if(set[rt]>=0)
    {
        sum[rt<<1]=(m-l+1)*set[rt];
        sum[rt<<1|1]=(r-m)*set[rt];
        if(set[rt]==1) zz[rt<<1]=zz[rt<<1|1]=inf;
        else zz[rt<<1]=l,zz[rt<<1|1]=m+1;
        set[rt<<1]=set[rt<<1|1]=set[rt];
        set[rt]=-1;
    }
}
void build(int l,int r,int rt)
{
    sum[rt]=0;
    set[rt]=-1;
    zz[rt]=l;
    if(l==r) return;
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
    PushDown(l,r,rt);
    int m=(l+r)>>1;
    int sum=0;
    if(m>=L)
      sum+=Query(L,R,l,m,rt<<1);
    if(m<R)
      sum+=Query(L,R,m+1,r,rt<<1|1);
    return sum;
}
int Query2(int v,int l,int r,int rt)   //第一个大于v的下标
{
    if(l==r) return l;
    PushDown(l,r,rt);
    int m=(l+r)>>1;
    if(m-l+1-sum[rt<<1]>=v) return Query2(v,l,m,rt<<1);
    return Query2(v-(m-l+1-sum[rt<<1]),m+1,r,rt<<1|1);
}
int Query3(int L,int R,int l,int r,int rt)
{
    if(l>=L&&r<=R)
    {
        return zz[rt];
    }
    PushDown(l,r,rt);
    int m=(l+r)>>1;
    int minz=inf;
    if(m>=L)
      minz=min(minz,Query3(L,R,l,m,rt<<1));
    if(m<R)
      minz=min(minz,Query3(L,R,m+1,r,rt<<1|1));
    return minz;
}
void Update(int L,int R,int l,int r,int rt,int v)
{
    if(l>=L&&r<=R)
    {
        sum[rt]=(r-l+1)*v;
        set[rt]=v;
        if(v==1) zz[rt]=inf;
        else zz[rt]=l;
        return;
    }
    PushDown(l,r,rt);
    int m=(l+r)>>1;
    if(m>=L)
      Update(L,R,l,m,rt<<1,v);
    if(m<R)
      Update(L,R,m+1,r,rt<<1|1,v);
    PushUp(rt);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    int n,m;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        build(1,n,1);
        int k,a,f;
        for(int i=0;i<m;++i)
        {
            scanf("%d",&k);
            if(k==1)
            {
                scanf("%d%d",&a,&f);
                a++;
                int u=Query(a,n,1,n,1);
                if(u==n-a+1)
                {
                    printf("Can not put any one.\n");
                    continue;
                }
                //cout<<Query(7,7,1,n,1)<<"ss"<<endl;
                int x=Query3(a,n,1,n,1);
                if(n-a+1-u<f) f=n-a+1-u;
                int v=a-sum[1]+u-1;
                int y=Query2(v+f,1,n,1);
                printf("%d %d\n",x-1,y-1);
                Update(x,y,1,n,1,1);

            }
            else
            {
                scanf("%d%d",&a,&f);
                a++;f++;
                int ss=Query(a,f,1,n,1);
                Update(a,f,1,n,1,0);
                printf("%d\n",ss);
            }
        }
        printf("\n");
    }
    return 0;
}
