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
const int mod=100000000+7;
const int maxb=500+10;
const int maxn=(1<<17)-1;
int n,k,b,m,r,x[maxb],y[maxb];
map<pair<int,int>,int>mp;
bool flag;
ll gcd(ll a,ll b) { return b==0?a:gcd(b,a%b); }
ll ext_gcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0)
    {
        x=1;y=0;
        return a;
    }
    ll d=ext_gcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}
ll inv(ll a,ll n)
{
    ll d,x,y;
    d=ext_gcd(a,n,x,y);
    return d==1?(x+n)%n:-1;
}
ll pow_mod(ll a,ll b)
{
    ll res=1;
    while(b)
    {
        if(b&1) res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}
struct HashNode
{
    ll data,id,next;
    HashNode(){}
    HashNode(ll data,ll id,ll next):data(data),id(id),next(next){}
}hash[maxn<<1];
bool vis[maxn<<1];
int totnode;
void Insert(ll val,ll i)
{
    int p=val&maxn;
    if(!vis[p])
    {
        vis[p]=true;
        hash[p]=HashNode(val,i,-1);
        return ;
    }
    while(hash[p].next!=-1)
    {
        if(hash[p].data==val) return;
        p=hash[p].next;
    }
    if(hash[p].data==val) return ;
    hash[p].next=++totnode;
    hash[totnode]=HashNode(val,i,-1);
}
ll find(ll val)
{
    int p=val&maxn;
    if(!vis[p]) return -1;
    while(p!=-1)
    {
        if(hash[p].data==val) return hash[p].id;
        p=hash[p].next;
    }
    return -1;
}
ll Baby_Step(ll A,ll B,ll C)
{
    B%=C;
    ll tmp=1;
    totnode=maxn;
    ll M=ceil(sqrt((double)C));
    for(int i=0;i<=M;++i)
    {
        Insert(tmp,i);
        tmp=tmp*A%C;
    }
    ll AA=pow_mod(A,M),j,x,y;
    tmp=1;
    for(int i=0;i<=M;++i)
    {
        ext_gcd(tmp,C,x,y);
        ll K=((B*x%C)+C)%C;
        j=find(K);
        if(j!=-1) return i*M+j;
        tmp=tmp*AA%C;
    }
    return -1;
}
ll cal()
{
    flag=false;
    mp.clear();
    for(int i=0;i<b;++i)
        mp[make_pair(x[i],y[i])]=1;
    int fcnt=0,lcnt=0,cnt=0;
    for(int i=0;i<b;++i)
    {
        if(x[i]==1) fcnt++;
        if(x[i]==m) {lcnt++;continue;}
        if(!mp[make_pair(x[i]+1,y[i])])
            cnt++;
    }
    cnt+=n;
    cnt-=fcnt;
    ll ans=pow_mod(k,cnt)*pow_mod(k-1,(ll)m*n-b-cnt)%mod;
    if(ans==r)
    {
        flag=true;
        return m;
    }
    ans=(ans*(pow_mod(k,lcnt)*pow_mod(k-1,n-lcnt)%mod))%mod;
    if(ans==r)
    {
        flag=true;
        return m+1;
    }
    return ans;
}
ll solve()
{
    ll cnt=cal();
    if(flag) return cnt;
    ll P=pow_mod(k-1,n);
    cnt=inv(cnt,mod);
    ll R=(r*cnt)%mod;
    memset(vis,0,sizeof(vis));
    ll v=Baby_Step(P,R,mod);
    return v+m+1;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        scanf("%d%d%d%d",&n,&k,&b,&r);
        m=1;
        for(int i=0;i<b;++i)
        {
            scanf("%d%d",&x[i],&y[i]);
            m=max(m,x[i]);
        }
        ll ans=solve();
        printf("Case %d: %lld\n",tcase,ans);
    }
    return 0;
}
