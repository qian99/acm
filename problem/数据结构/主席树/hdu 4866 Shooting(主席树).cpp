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
struct Node
{
    int L,R,sum;
    ll val;
};
struct Data
{
    int x,d,type;
    Data(){}
    Data(int x,int d,int type):x(x),d(d),type(type){}
    bool operator <(const Data &a) const
    {
        if(x!=a.x) return x<a.x;
        if(d!=a.d) return d<a.d;
        return type<a.type;
    }
}data[maxn<<1];
Node node[maxn*50];
int root[maxn],tot;
int num[maxn];
int Insert(int p,int l,int r,int val,int v,int rt)
{
    int x=++tot;
    node[x]=node[rt];
    node[x].sum+=v;
    node[x].val+=v*val;
    if(l==r) return x;
    int m=(l+r)>>1;
    if(m>=p) node[x].L=Insert(p,l,m,val,v,node[rt].L);
    else node[x].R=Insert(p,m+1,r,val,v,node[rt].R);
    return x;
}
ll Query(int l,int r,int rt,int k)
{
    if(l==r) return k==0?0:(ll)node[rt].val/node[rt].sum*k;
    int m=(l+r)>>1;
    if(node[node[rt].L].sum>=k) return Query(l,m,node[rt].L,k);
    else return node[node[rt].L].val+Query(m+1,r,node[rt].R,k-node[node[rt].L].sum);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,X,P;
    while(~scanf("%d%d%d%d",&n,&m,&X,&P))
    {
        tot=0;
        int l,r,d,N=0,x;
        for(int i=0;i<n;++i)
        {
            scanf("%d%d%d",&l,&r,&d);
            data[i]=Data(l,d,1);
            data[i+n]=Data(r+1,d,-1);
            num[i]=d;
        }
        sort(num,num+n);
        N=unique(num,num+n)-num;
        sort(data,data+n*2);
        root[0]=0;
        for(int i=0;i<n*2;++i)
        {
            int x=lower_bound(num,num+N,data[i].d)-num+1;
            root[i+1]=Insert(x,1,N,data[i].d,data[i].type,root[i]);
        }
        int a,b,c;
        ll pre=1;
        while(m--)
        {
            scanf("%d%d%d%d",&x,&a,&b,&c);
            int pos=upper_bound(data,data+n*2,Data(x,inf,0))-data-1;
            if(pos<0) {printf("0\n");pre=0;}
            else
            {
                int k=(a*pre+b)%c;
                ll ans=Query(1,N,root[pos+1],k);
                if(pre>P) ans*=2;
                printf("%I64d\n",ans);
                pre=ans;
            }
        }
    }
    return 0;
}
