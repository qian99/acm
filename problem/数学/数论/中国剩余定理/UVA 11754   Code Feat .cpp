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
const int limit=10000;
int x[15],y[15][150],k[15],r[15],C,S;
set<int>values[15];
vector<ll>ans;
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
void solve1(int S,int bestp)
{
    for(int i=0;i<C;++i)
    {
        if(i==bestp) continue;
        values[i].clear();
        for(int j=0;j<k[i];++j)
            values[i].insert(y[i][j]);
    }
    for(int t=0;S!=0;++t)
    {
        for(int i=0;i<k[bestp];++i)
        {
            ll n=(ll)t*x[bestp]+y[bestp][i];
            if(n==0) continue;
            bool flag=true;
            for(int j=0;j<C;++j)
                if(j!=bestp&&!values[j].count(n%x[j])) {flag=false;break;}
            if(flag) { printf("%lld\n",n);if(--S==0) break;}
        }
    }
}
ll china()
{
    ll M=1,d,X=0,Y;
    for(int i=0;i<C;++i) M*=x[i];
    for(int i=0;i<C;++i)
    {
        ll w=M/x[i];
        ext_gcd(x[i],w,d,Y);
        X=(X+Y*w*r[i])%M;
    }
    return (X+M)%M;
}
void dfs(int p)
{
    if(p==C)
    {
        ans.push_back(china());
        return ;
    }
    for(int i=0;i<k[p];++i)
    {
        r[p]=y[p][i];
        dfs(p+1);
    }
}
void solve2(int S)
{
    ans.clear();
    dfs(0);
    sort(ans.begin(),ans.end());
    ll M=1;
    for(int i=0;i<C;++i) M*=x[i];
    for(int i=0;S!=0;++i)
    {
        for(int j=0;j<(int)ans.size();++j)
        {
            ll tmp=i*M+ans[j];
            if(tmp>0)
            {
                printf("%lld\n",tmp);
                if(--S==0) break;
            }
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&C,&S))
    {
        if(C==0&&S==0) break;
        int bestp=0;
        ll tot=1;
        for(int i=0;i<C;++i)
        {
            scanf("%d%d",&x[i],&k[i]);
            tot*=k[i];
            for(int j=0;j<k[i];++j)
                scanf("%d",&y[i][j]);
            sort(y[i],y[i]+k[i]);
            if(x[bestp]*k[i]<x[i]*k[bestp]) bestp=i;
        }
        if(tot>limit)
            solve1(S,bestp);
        else
            solve2(S);
        printf("\n");
    }
    return 0;
}
