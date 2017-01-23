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
const int maxn=1000000+10;
int x[maxn],n,m;
ll F(int mid)
{
    ll sum=0;
    int s=0;
    while(s<n&&x[s]<mid)
    {
        sum+=(mid-x[s])*2LL;
        s+=m;
    }
    s=n-1;
    while(s>=0&&x[s]>mid)
    {
        sum+=(x[s]-mid)*2LL;
        s-=m;
    }
    return sum;
}
ll solve()
{
    int L=x[0],R=x[n-1];
    while(R-L>1)
    {
        int m1=L+(R-L+1)/3;
        int m2=R-(R-L+1)/3;
        if(F(m1)>F(m2)) L=m1;
        else R=m2;
    }
    return min(F(L),F(R));
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;++i)
        scanf("%d",&x[i]);
    ll ans=solve();
    printf("%I64d\n",ans);
    return 0;
}