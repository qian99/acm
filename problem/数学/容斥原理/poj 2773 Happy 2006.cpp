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
int factor[20],tot;
ll M,K,sum;
void fenjie(ll n)
{
    tot=0;
    int m=sqrt(n+0.5);
    for(int i=2;i<=m;++i)
    {
        if(n%i==0)
        {
            factor[tot++]=i;
            while(n%i==0) n/=i;
        }
    }
    if(n>1) factor[tot++]=n;
}
void dfs(int pos,ll now,int cnt,ll x)
{
    if(pos==tot)
    {
        if(now==1) return ;
        if(cnt&1) sum+=x/now;
        else sum-=x/now;
        return ;
    }
    dfs(pos+1,now*factor[pos],cnt+1,x);
    dfs(pos+1,now,cnt,x);
}
bool test(ll x)
{
    sum=0;
    dfs(0,1,0,x);
    return (x-sum)>=K;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(cin>>M>>K)
    {
        fenjie(M);
        ll l=1,r=Inf,m;
        while(l<r)
        {
            m=(l+r)>>1;
            if(!test(m))
                l=m+1;
            else r=m;
        }
        cout<<l<<endl;
    }
    return 0;
}
