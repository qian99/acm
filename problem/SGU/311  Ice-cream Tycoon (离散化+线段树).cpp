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
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100000+10;
struct Opera
{
    int type,x,id;
    ll t;
    Opera(){}
    Opera(int type,int x,int id,ll t):type(type),x(x),id(id),t(t){}
}op[maxn];
ll sum[maxn<<2],cost[maxn<<2];
int setv[maxn<<2],val[maxn],num[maxn];
map<int ,int >mp;
void build(int l,int r,int rt)
{
    sum[rt]=cost[rt]=0;
    setv[rt]=-1;
    if(l==r) return ;
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
}
void PushUp(int rt)
{
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
    cost[rt]=cost[rt<<1]+cost[rt<<1|1];
}
void PushDown(int rt)
{
    if(setv[rt]!=-1)
    {
        setv[rt<<1]=setv[rt<<1|1]=0;
        sum[rt<<1]=sum[rt<<1|1]=0;
        cost[rt<<1]=cost[rt<<1|1]=0;
        setv[rt]=-1;
    }
}
bool Query(int l,int r,int rt,int n,ll t)
{
    if(sum[rt]<n) return false;
    if(sum[rt]==n) return cost[rt]<=t;
    if(l==r)
    {
        if(sum[rt]>=n&&(ll)val[l]*n<=t)
            return true;
        return false;
    }
    PushDown(rt);
    int m=(l+r)>>1;
    if(sum[rt<<1]>=n)
        return Query(l,m,rt<<1,n,t);
    else if(cost[rt<<1]<=t)
        return Query(m+1,r,rt<<1|1,n-sum[rt<<1],t-cost[rt<<1]);
    return false;
}
void Update(int l,int r,int rt,int n)
{
    if(sum[rt]==n)
    {
        setv[rt]=0;
        sum[rt]=cost[rt]=0;
        return ;
    }
    if(l==r)
    {
        sum[rt]-=n;
        cost[rt]=val[l]*sum[rt];
        return ;
    }
    PushDown(rt);
    int m=(l+r)>>1;
    if(sum[rt<<1]>=n)
        Update(l,m,rt<<1,n);
    else
    {
        Update(m+1,r,rt<<1|1,n-sum[rt<<1]);
        Update(l,m,rt<<1,sum[rt<<1]);
    }
    PushUp(rt);
}
void Update2(int p,int l,int r,int rt,int n,int c)
{
    if(l==r)
    {
        sum[rt]+=n;
        cost[rt]+=(ll)n*c;
        return ;
    }
    PushDown(rt);
    int m=(l+r)>>1;
    if(m>=p) Update2(p,l,m,rt<<1,n,c);
    else Update2(p,m+1,r,rt<<1|1,n,c);
    PushUp(rt);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    char str[10];
    int q=0,tot=0;
    while(~scanf("%s",str))
    {
        int n,c;
        ll t;
        if(str[0]=='A')
        {
            scanf("%d%d",&n,&c);
            op[q]=Opera(0,n,q,c);
            num[tot++]=c;q++;
        }
        else
        {
            scanf("%d%lld",&n,&t);
            op[q]=Opera(1,n,q,t);
            q++;
        }
    }
    sort(num,num+tot);
    int N=unique(num,num+tot)-num;
    mp.clear();
    for(int i=0;i<N;++i)
    {
        mp[num[i]]=i+1;
        val[i+1]=num[i];
    }
    build(1,N,1);
    for(int i=0;i<q;++i)
    {
        if(op[i].type==0)
        {
            int p=mp[(int)op[i].t];
            Update2(p,1,N,1,op[i].x,val[p]);
        }
        else
        {

            if(Query(1,N,1,op[i].x,op[i].t))
            {
                Update(1,N,1,op[i].x);
                printf("HAPPY\n");
            }
            else printf("UNHAPPY\n");

        }
    }
    return 0;
}
