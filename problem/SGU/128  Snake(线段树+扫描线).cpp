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
const int maxn=10000+1000;
struct Point
{
    int x,y,id;
}p[maxn];
struct Event
{
    int type,v;
    Point d;
    bool operator <(const Event & a) const
    {
        if(d.x!=a.d.x) return d.x<a.d.x;
        if(type==a.type)
        {
            if(type==0) return v;
            return true;
        }
        if(type==0) return v;
        return !a.v;
    }
}event[maxn<<1];
bool pcmp1(Point a,Point b)
{
    return (a.x==b.x&&a.y<b.y)||(a.x<b.x);
}
bool pcmp2(Point a,Point b)
{
    return (a.y==b.y&&a.x<b.x)||(a.y<b.y);
}
bool pcmp3(Point a,Point b)
{
    return a.id<b.id;
}
int Len(Point a,Point b)
{
    return abs(a.x-b.x+a.y-b.y);
}
int sum[maxn<<2];
void PushUp(int rt)
{
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
void build(int l,int r,int rt)
{
    sum[rt]=0;
    if(l==r) return ;
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
}
int Query(int L,int R,int l,int r,int rt)
{
    if(l>=L&&r<=R) return sum[rt];
    int m=(l+r)>>1;
    int tmp=0;
    if(m>=L) tmp+=Query(L,R,l,m,rt<<1);
    if(m<R) tmp+=Query(L,R,m+1,r,rt<<1|1);
    return tmp;
}
void Update(int p,int l,int r,int rt,int v)
{
    if(l==r)
    {
        sum[rt]+=v;
        return ;
    }
    int m=(l+r)>>1;
    if(m>=p) Update(p,l,m,rt<<1,v);
    else Update(p,m+1,r,rt<<1|1,v);
    PushUp(rt);
}
int con[maxn][2];
bool vis[maxn];
void dfs(int u)
{
    vis[u]=true;
    int v=con[u][0];
    if(v!=-1&&!vis[v]) return dfs(v);
    v=con[u][1];
    if(v!=-1&&!vis[v]) return dfs(v);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,N;
    scanf("%d",&n);
    for(int i=0;i<n;++i)
    {
        scanf("%d%d",&p[i].x,&p[i].y);
        p[i].id=i;
    }
    memset(vis,0,sizeof(vis));
    memset(con,0xff,sizeof(con));
    int lastv=-inf;
    N=1;m=0;
    ll sum=0;
    bool flag=true;

    sort(p,p+n,pcmp1);
    for(int i=0;i<n;i+=2)
        sum+=Len(p[i],p[i+1]);

    sort(p,p+n,pcmp2);
    for(int i=0;i<n;++i)
    {
        if(p[i].y!=lastv)
        {
            lastv=p[i].y;
            p[i].y=++N;
        }
        else p[i].y=N;
    }
    for(int i=0;i<n;i+=2)
    {
        if(i+1>=n||p[i].y!=p[i+1].y) {flag=false;break;}
        if(p[i].x==p[i+1].x) {flag=false;break;}
        event[m].d=p[i];event[m].type=0;event[m++].v=0;
        event[m].d=p[i+1];event[m].type=0;event[m++].v=1;
        con[p[i].id][0]=p[i+1].id;
        con[p[i+1].id][0]=p[i].id;
        sum+=Len(p[i],p[i+1]);
    }
    sort(p,p+n,pcmp1);
    for(int i=0;i<n;i+=2)
    {
        if(i+1>=n||p[i].x!=p[i+1].x) {flag=false;break;}
        event[m].d=p[i];event[m].type=1;event[m++].v=p[i+1].y;
        con[p[i].id][1]=p[i+1].id;
        con[p[i+1].id][1]=p[i].id;
    }
    if(flag)
    {
        sort(p,p+n,pcmp3);
        dfs(0);
        for(int i=0;i<n;++i)
            if(!vis[i]) {flag=false;break;}
    }
    if(flag)
    {
        sort(event,event+m);
        build(1,N,1);
        int L,R,tmp;
        for(int i=0;i<m;++i)
        {
            if(event[i].type==0)
            {
                if(event[i].v==0) Update(event[i].d.y,1,N,1,1);
                else Update(event[i].d.y,1,N,1,-1);
            }
            else
            {
                L=event[i].d.y;
                R=event[i].v;
                L++;R--;
                if(L<=R)
                {
                    tmp=Query(L,R,1,N,1);
                    if(tmp) {flag=false;break;}
                }
            }
        }
    }
    if(flag) printf("%lld\n",sum);
    else printf("0\n");
    return 0;
}

