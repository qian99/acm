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
const int maxn=1000+10;
int changes[maxn][2];
int factor[20],tot,N,cnt;
ll ans;
int gcd(int a,int b) {return b==0?a:gcd(b,a%b);}
void dfs(int pos,ll now,int sign)
{
    int tmp=N/now;
    ans+=((now+tmp*now)*tmp/2)*sign;
    for(int i=pos+1;i<tot;++i)
        dfs(i,now*factor[i],-sign);
}
ll solve(int n,int p)
{
    if(n==0) return 0;
    tot=0;N=n;ans=0;
    int m=sqrt(p+0.5);
    for(int i=2;i<=m;++i)
    {
        if(p%i==0)
        {
            factor[tot++]=i;
            while(p%i==0) p/=i;
        }
    }
    if(p>1) factor[tot++]=p;
    for(int i=0;i<tot;++i)
        dfs(i,factor[i],1);
    return (ll)(1+n)*n/2-ans;
}
ll querys(int L,int R,int p)
{
    ll res=solve(R,p)-solve(L-1,p);
    for(int i=0;i<cnt;++i)
    {
        int x=changes[i][0];
        if(x>=L&&x<=R)
        {
            if(gcd(x,p)==1) res-=x;
            if(gcd(changes[i][1],p)==1) res+=changes[i][1];
        }
    }
    return res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        int op,x,y,p;
        cnt=0;
        while(m--)
        {
            scanf("%d",&op);
            if(op==1)
            {
                scanf("%d%d%d",&x,&y,&p);
                printf("%I64d\n",querys(x,y,p));
            }
            else
            {
                scanf("%d%d",&x,&p);
                int i=0;
                for(i=0;i<cnt;++i)
                    if(changes[i][0]==x)
                    {
                        changes[i][1]=p;
                        break;
                    }
                if(i==cnt) {changes[cnt][0]=x;changes[cnt++][1]=p;}
            }
        }
    }
    return 0;
}
