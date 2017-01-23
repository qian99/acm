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
const int maxn=500+10;
struct Node
{
    double x,L,R;
    int c;
    Node(){}
    Node(double x,double L,double R,int c):x(x),L(L),R(R),c(c){}
    bool operator <(const Node &a) const
    {
        return x<a.x;
    }
}node[maxn];
double num[maxn],sum[maxn<<2];
int cover[maxn<<2];
map<double,int>mp;
inline void PushUp(int l,int r,int rt)
{
    if(cover[rt]) sum[rt]=num[r]-num[l-1];
    else if(l==r) sum[rt]=0;
    else sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
void build(int l,int r,int rt)
{
    sum[rt]=0;
    cover[rt]=0;
    if(l==r) return ;
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
}
void Update(int L,int R,int l,int r,int rt,int v)
{
    if(l>=L&&r<=R)
    {
        cover[rt]+=v;
        PushUp(l,r,rt);
        return ;
    }
    int m=(l+r)>>1;
    if(m>=L) Update(L,R,l,m,rt<<1,v);
    if(m<R) Update(L,R,m+1,r,rt<<1|1,v);
    PushUp(l,r,rt);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,tcase=0;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        tcase++;
        double x1,y1,x2,y2;
        int tot=0,N;
        mp.clear();
        for(int i=0;i<n;++i)
        {
            scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
            if(x1>x2) swap(x1,x2);
            if(y1>y2) swap(y1,y2);
            num[tot++]=y1;
            num[tot++]=y2;
            node[i]=Node(x1,y1,y2,1);
            node[i+n]=Node(x2,y1,y2,-1);
        }
        sort(num,num+tot);
        sort(node,node+tot);
        N=unique(num,num+tot)-num;
        for(int i=0;i<N;++i)
            mp[num[i]]=i+1;
        num[N]=num[N-1];
        build(1,N,1);
        double area=0;
        int L,R;
        for(int i=0;i<tot-1;++i)
        {
            L=mp[node[i].L];
            R=mp[node[i].R]-1;
            Update(L,R,1,N,1,node[i].c);
            area+=sum[1]*(node[i+1].x-node[i].x);
        }
        printf("Test case #%d\n",tcase);
        printf("Total explored area: %.2lf\n\n",area);
    }
    return 0;
}
