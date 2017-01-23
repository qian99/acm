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
const int maxn=100000+10;
int a[maxn],b[maxn];
int type[maxn],n;
ll len[maxn];
int f(ll p)
{
    int l=1,r=n,m;
    while(l<r)
    {
        m=l+(r-l)/2;
        if(len[m]<p)
            l=m+1;
        else r=m;
    }
    return l;
}
int solve(ll p)
{
    int k=f(p);
    if(type[k]==1) return a[k];
    p-=len[k-1];
    p=p%a[k];
    if(p==0) p=a[k];
    return solve(p);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d",&n);
    len[0]=0;
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&type[i]);
        if(type[i]==1)
        {
            scanf("%d",&a[i]);
            len[i]=len[i-1]+1;
        }
        else
        {
            scanf("%d%d",&a[i],&b[i]);
            len[i]=len[i-1]+a[i]*b[i];
        }
    }
    int m;
    ll p;
    scanf("%d",&m);
    while(m--)
    {
        scanf("%I64d",&p);
        int ans=solve(p);
        printf("%d ",ans);
    }
    printf("\n");
    return 0;
}

