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
const int maxn=(1<<17)-1;
struct HashNode
{
    ll data,id,next;
    HashNode(){}
    HashNode(ll data,ll id,ll next):data(data),id(id),next(next){}
}hash[maxn<<1];
bool flag[maxn<<1];
int tot;
void Insert(ll val,ll i)
{
    ll p=val&maxn;
    if(!flag[p])
    {
        flag[p]=true;
        hash[p]=HashNode(val,i,-1);
    }
    else
    {
        while(hash[p].next!=-1)
        {
            if(hash[p].data==val) return;
            p=hash[p].next;
        }
        if(hash[p].data==val) return ;
        hash[p].next=++tot;
        hash[tot]=HashNode(val,i,-1);
    }
}
ll find(ll val)
{
    ll p=val&maxn;
    if(!flag[p]) return -1;
    while(p!=-1)
    {
        if(hash[p].data==val) return hash[p].id;
        p=hash[p].next;
    }
    return -1;
}
ll gcd(ll a,ll b) { return b==0?a:gcd(b,a%b); }
ll ext_gcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0)
    {
        x=1,y=0;
        return a;
    }
    ll d=ext_gcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}
ll pow_mod(ll a,ll n,ll m)
{
    ll res=1;
    a%=m;
    while(n)
    {
        if(n&1) res=res*a%m;
        a=a*a%m;
        n>>=1;
    }
    return res;
}
ll BabyStep_GiantStep(ll A,ll B,ll C)
{
    tot=maxn;B%=C;
    ll tmp=1;
    for(int i=0;i<=100;++i)
    {
        if(tmp==B%C) return i;
        tmp=tmp*A%C;
    }
    ll D=1,d=0;
    while((tmp=gcd(A,C))!=1)
    {
        if(B%tmp) return -1;
        C/=tmp;
        B/=tmp;
        D=D*A/tmp%C;
        d++;
    }
    ll m=(ll)ceil(sqrt((double)C));
    tmp=1;
    for(int i=0;i<=m;++i)
    {
        Insert(tmp,i);
        tmp=tmp*A%C;
    }
    ll x,y,K=pow_mod(A,m,C);
    for(int i=0;i<=m;++i)
    {
        ext_gcd(D,C,x,y);
        tmp=((B*x)%C+C)%C;
        if((y=find(tmp))!=-1)
            return i*m+y+d;
        D=D*K%C;
    }
    return -1;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ll A,B,C;
    while(cin>>C>>A>>B)
    {
        memset(flag,0,sizeof(flag));
        ll ans=BabyStep_GiantStep(A,B,C);
        if(ans==-1)
            cout<<"no solution"<<endl;
        else
            cout<<ans<<endl;
    }
    return 0;
}
