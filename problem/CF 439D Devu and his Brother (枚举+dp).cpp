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
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100000+10;
int a[maxn],b[maxn],c[maxn<<1];
ll dp1[maxn<<1],dp2[maxn<<1],cnt[maxn<<1];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,tot=0;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        c[tot++]=a[i];
    }
    for(int i=1;i<=m;++i)
    {
        scanf("%d",&b[i]);
        c[tot++]=b[i];
    }
    sort(a+1,a+n+1);
    sort(b+1,b+m+1);
    sort(c,c+tot);
    tot=unique(c,c+tot)-c;
    ll last=1;
    memset(cnt,0,sizeof(cnt));
    dp1[0]=dp2[tot-1]=0;
    while(last<=n&&a[last]<c[0]) dp1[0]+=c[0]-a[last++],cnt[0]++;
    for(int i=1;i<tot;++i)
    {
        dp1[i]=dp1[i-1];
        dp1[i]+=(c[i]-c[i-1])*cnt[i-1];
        cnt[i]+=cnt[i-1];
        while(last<=n&&a[last]<c[i]) dp1[i]+=c[i]-a[last++],cnt[i]++;
    }
    memset(cnt,0,sizeof(cnt));
    last=m;
    while(last>=1&&b[last]>c[tot-1]) dp2[tot-1]+=b[last--]-c[tot-1],cnt[tot-1]++;
    for(int i=tot-2;i>=0;--i)
    {
        dp2[i]=dp2[i+1];
        dp2[i]+=(c[i+1]-c[i])*cnt[i+1];
        cnt[i]+=cnt[i+1];
        while(last>=1&&b[last]>c[i]) dp2[i]+=b[last--]-c[i],cnt[i]++;
    }
    ll ans=dp1[0]+dp2[0];
    for(int i=0;i<tot;++i)
        ans=min(ans,dp1[i]+dp2[i]);
//    if(a[1]>=b[m]) ans=0;
    printf("%I64d\n",ans);
    return 0;
}