#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<set>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100000+10;
int num[maxn];
int gcd(int a,int b) { return b==0?a:gcd(b,a%b);}
vector<int>vt[maxn<<2];
int setv[maxn<<2];
struct Node
{
    int type,l,r,v;
}node[maxn];
void build(int l,int r,int rt)
{
    vt[rt].clear();
    setv[rt]=-1;
    if(l==r) return ;
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
}
//gcd->val   noting to do
//gcd->gcd   uion
//val->gcd   uion->val
//val->val   noting to do
void PushDown(int rt)
{
    if(setv[rt]!=-1)
    {
        if(vt[rt<<1].size())
        {
            setv[rt<<1]=setv[rt];
            for(int i=vt[rt<<1].size()-1;i>=0;--i)
            {
                int x=vt[rt<<1][i];
                if(setv[rt<<1]>x)
                    setv[rt<<1]=gcd(setv[rt<<1],x);
            }
            vt[rt<<1].clear();
        }
        else if(setv[rt<<1]==-1)
            setv[rt<<1]=setv[rt];
        if(vt[rt<<1|1].size())
        {
            setv[rt<<1|1]=setv[rt];
            for(int i=vt[rt<<1|1].size()-1;i>=0;--i)
            {
                int x=vt[rt<<1|1][i];
                if(setv[rt<<1|1]>x)
                    setv[rt<<1|1]=gcd(setv[rt<<1|1],x);
            }
            vt[rt<<1|1].clear();
        }
        else if(setv[rt<<1|1]==-1)
            setv[rt<<1|1]=setv[rt];
        setv[rt]=-1;
        return ;
    }
    if(vt[rt].size())
    {
        if(setv[rt<<1]==-1)
        {
            for(int i=0;i<(int)vt[rt].size();++i)
                vt[rt<<1].push_back(vt[rt][i]);
        }
        if(setv[rt<<1|1]==-1)
        {
            for(int i=0;i<(int)vt[rt].size();++i)
                vt[rt<<1|1].push_back(vt[rt][i]);
        }
        vt[rt].clear();
    }
}
void Update(int L,int R,int l,int r,int rt,int v,int type)
{
    if(l>=L&&r<=R)
    {
        if(type==1)
        {
            if(vt[rt].size())
            {
                for(int i=vt[rt].size()-1;i>=0;--i)
                {
                    int x=vt[rt][i];
                    if(v>x) v=gcd(v,x);
                }
                vt[rt].clear();
                setv[rt]=v;
            }
            else if(setv[rt]==-1) setv[rt]=v;
        }
        else
        {
            if(setv[rt]==-1)
                vt[rt].push_back(v);
        }
        return ;
    }
    PushDown(rt);
    int m=(l+r)>>1;
    if(m>=L) Update(L,R,l,m,rt<<1,v,type);
    if(m<R) Update(L,R,m+1,r,rt<<1|1,v,type);
}
void traval(int l,int r,int rt)
{
    if(l==r)
    {
        if(setv[rt]!=-1) num[l]=setv[rt];
        else
        {
            for(int i=vt[rt].size()-1;i>=0;--i)
            {
                int x=vt[rt][i];
                if(num[l]>x) num[l]=gcd(num[l],x);
            }
        }
        return ;
    }
    PushDown(rt);
    int m=(l+r)>>1;
    traval(l,m,rt<<1);
    traval(m+1,r,rt<<1|1);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n,m;
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
            scanf("%d",&num[i]);
        build(1,n,1);
        scanf("%d",&m);
        for(int i=0;i<m;++i)
            scanf("%d%d%d%d",&node[i].type,&node[i].l,&node[i].r,&node[i].v);
        for(int i=m-1;i>=0;--i)
            Update(node[i].l,node[i].r,1,n,1,node[i].v,node[i].type);
        traval(1,n,1);
        for(int i=1;i<=n;++i)
            printf("%d ",num[i]);
        printf("\n");
    }
    return 0;
}
