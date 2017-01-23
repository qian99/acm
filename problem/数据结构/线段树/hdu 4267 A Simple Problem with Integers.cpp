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
int sum[maxn<<2],addv[maxn<<2][55];
int state[55][2],link[10][11];
void getState()
{
    int m=0;
    for(int i=0;i<10;++i)
    {
        for(int j=i+1;j<=10;++j)
        {
            state[m][0]=i;
            state[m][1]=j;
            link[i][j]=m++;
        }
    }
}
inline void PushUp(int rt)
{
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
void PushDown(int l,int r,int rt)
{
    int ls=rt<<1,rs=rt<<1|1;
    int m=(l+r)>>1;
    int x,y;
    for(int i=0;i<55;++i)
    {
        if(addv[rt][i]!=0)
        {
            x=state[i][0];y=state[i][1];
            if(m-l+1>x)
            {
                addv[ls][i]+=addv[rt][i];
                sum[ls]+=((m-l-x)/y+1)*addv[rt][i];
            }
            if(r-l+1>x)
            {
                if(x>=m-l+1) x=x-(m-l+1);
                else x=y-(m-l-x)%y-1;
                if(r-m>x)
                {
                    addv[rs][link[x][y]]+=addv[rt][i];
                    sum[rs]+=((r-m-x-1)/y+1)*addv[rt][i];
                }
            }
            addv[rt][i]=0;
        }
    }
}
void build(int l,int r,int rt)
{
    memset(addv[rt],0,sizeof(addv[rt]));
    if(l==r)
    {
        scanf("%d",&sum[rt]);
        return;
    }
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    PushUp(rt);
}
void Update(int L,int R,int l,int r,int rt,int k,int c)
{
    if(l>=L&&r<=R)
    {
        int x=(l-L);
        if(x!=0)
            x=k-(x-1)%k-1;
        if(r-l+1>x)
        {
            sum[rt]+=((r-l-x)/k+1)*c;
            addv[rt][link[x][k]]+=c;
        }
        return ;
    }
    PushDown(l,r,rt);
    int m=(l+r)>>1;
    if(m>=L)
      Update(L,R,l,m,rt<<1,k,c);
    if(m<R)
      Update(L,R,m+1,r,rt<<1|1,k,c);
    PushUp(rt);
}
int Query(int p,int l,int r,int rt)
{
    if(l==r)
        return sum[rt];
    PushDown(l,r,rt);
    int m=(l+r)>>1;
    if(m>=p)
      return Query(p,l,m,rt<<1);
    else return Query(p,m+1,r,rt<<1|1);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,q;
    getState();
    while(~scanf("%d",&n))
    {
        build(1,n,1);
        scanf("%d",&q);
        int a,b,k,c,tp;
        while(q--)
        {
            scanf("%d",&tp);
            if(tp==1)
            {
                scanf("%d%d%d%d",&a,&b,&k,&c);
                Update(a,b,1,n,1,k,c);
            }
            else
            {
                scanf("%d",&a);
                int ans=Query(a,1,n,1);
                printf("%d\n",ans);
            }
        }
    }
    return 0;
}
