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
const int maxn=1<<18;
ll dp[maxn][100];
int num[20],cnt[20];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    memset(dp,0,sizeof(dp));
    memset(cnt,0,sizeof(cnt));
    ll val;
    int n=0,m;
    cin>>val>>m;
    while(val)
    {
        num[n++]=val%10;
        cnt[num[n-1]]++;
        val/=10;
    }
    dp[0][0]=1;
    for(int i=0;i<(1<<n);++i)
    {
        for(int j=0;j<n;++j)
        {
            if(i==0&&num[j]==0) continue;
            if(i&(1<<j)) continue;
            for(int k=0;k<m;++k)
                dp[i|(1<<j)][(k*10+num[j])%m]+=dp[i][k];
        }
    }
    ll r=1;
    for(int i=0;i<10;++i)
    {
        for(int j=2;j<=cnt[i];++j)
            r*=j;
    }
    cout<<dp[(1<<n)-1][0]/r<<endl;
    return 0;
}
