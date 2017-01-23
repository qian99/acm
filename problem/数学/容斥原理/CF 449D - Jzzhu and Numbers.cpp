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
const int maxn=1<<20;
const int mod=1000000000+7;
ll p[maxn],cnt[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    p[0]=1;
    for(int i=1;i<maxn;++i) p[i]=(p[i-1]<<1)%mod;
    int n,tmp;
    scanf("%d",&n);
    for(int i=0;i<n;++i)
    {
        scanf("%d",&tmp);
        cnt[tmp]++;
    }
    int tot=1<<20;
    for(int i=0;i<20;++i)
        for(int j=0;j<tot;++j)
            if(j&(1<<i))
                cnt[j^(1<<i)]+=cnt[j];
    ll ans=p[n];
    for(int i=1;i<tot;++i)
    {
        int x=0;
        for(int j=0;j<20;++j)
            if(i&(1<<j)) x^=1;
        if(x) ans-=p[cnt[i]];
        else ans+=p[cnt[i]];
        ans%=mod;
    }
    ans=(ans+mod)%mod;
    printf("%I64d\n",ans);
    return 0;
}
