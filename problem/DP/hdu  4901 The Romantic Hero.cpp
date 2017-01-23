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
const int mod=1000000000+7;
int dpre[maxn][1025][2],dsuf[maxn][1025];
int a[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
            scanf("%d",&a[i]);
        memset(dpre,0,sizeof(dpre));
        memset(dsuf,0,sizeof(dsuf));
        dpre[1][a[1]][1]=1;
        for(int i=2;i<=n;++i)
        {
            dpre[i][a[i]][1]++;
            for(int j=0;j<1024;++j)
            {
                dpre[i][j^a[i]][1]+=(dpre[i-1][j][0]+dpre[i-1][j][1])%mod;
                if(dpre[i][j^a[i]][1]>=mod) dpre[i][j^a[i]][1]-=mod;
                dpre[i][j][0]+=(dpre[i-1][j][0]+dpre[i-1][j][1])%mod;
                if(dpre[i][j][0]>=mod) dpre[i][j][0]-=mod;
            }
        }
        dsuf[n][a[n]]=1;
        for(int i=n-1;i>=1;--i)
        {
            dsuf[i][a[i]]++;
            for(int j=0;j<1024;++j)
            {
                dsuf[i][j&a[i]]+=dsuf[i+1][j];
                if(dsuf[i][j&a[i]]>=mod) dsuf[i][j&a[i]]-=mod;
                dsuf[i][j]+=dsuf[i+1][j];
                if(dsuf[i][j]>=mod) dsuf[i][j]-=mod;
            }
        }
        ll ans=0;
        for(int i=1;i<n;++i)
        {
            for(int j=0;j<1024;++j)
            {
                ans+=(ll)dpre[i][j][1]*dsuf[i+1][j]%mod;
                if(ans>=mod) ans-=mod;
            }
        }
        printf("%I64d\n",ans);
    }
    return 0;
}