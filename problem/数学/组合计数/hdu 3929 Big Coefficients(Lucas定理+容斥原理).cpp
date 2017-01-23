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
const int maxn=20;
ll a[maxn],ans;
int n;
int cal(ll x)
{
    int cnt=0;
    while(x)
    {
        x=x&(x-1);
        cnt++;
    }
    return cnt;
}
void dfs(int p,ll msk,ll v)
{
    ans+=(1LL<<cal(msk))*v;
    for(int i=p+1;i<n;++i)
        dfs(i,msk&a[i],-2*v);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(int i=0;i<n;++i)
            scanf("%I64d",&a[i]);
        ans=0;
        for(int i=0;i<n;++i)
            dfs(i,a[i],1);
        printf("Case #%d: %I64d\n",++tcase,ans);
    }
    return 0;
}
