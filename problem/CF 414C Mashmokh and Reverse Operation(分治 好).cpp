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
const int maxn=1<<21;
ll num[maxn],tmp[maxn];
ll dp[22],dp2[22],eq[22];
ll MergeSort(int s,int t,int deep,ll &ev)
{
    if(s==t) return ev=dp[deep]=0;
    ll sum=0,tot=0,tp;
    int m=(s+t)>>1;
    sum+=MergeSort(s,m,deep-1,tp);
    tot+=tp;
    sum+=MergeSort(m+1,t,deep-1,tp);
    tot+=tp;
    int i,k=m+1;
    for(i=s;i<=m;++i)
    {
        while(k<t&&num[i]>num[k]) k++;
        sum+=(k-(m+1))+(num[i]>num[k]?1:0);
    }
    k=m+1;
    int pre=k;
    for(i=s;i<=m;++i)
    {
        while(k<t&&num[i]>num[k]) pre=++k;
        while(k<t&&num[k+1]==num[pre]) k++;
        if(num[i]==num[k]) tot+=(k-pre+1);
    }
    i=0;
    int l=s,r=m+1;
    while(l<=m&&r<=t)
    {
        if(num[l]<num[r]) tmp[i++]=num[l++];
        else tmp[i++]=num[r++];
    }
    while(l<=m) tmp[i++]=num[l++];
    while(r<=m) tmp[i++]=num[r++];
    for(int j=0;j<i;++j) num[s+j]=tmp[j];
    dp[deep]+=sum;
    eq[deep]+=tot;
    ev=tot;
    return sum;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    memset(dp,0,sizeof(dp));
    memset(eq,0,sizeof(eq));
    ll n,N;
    scanf("%I64d",&n);
    N=1<<n;
    for(int i=1;i<=N;++i)
        scanf("%I64d",&num[i]);
    MergeSort(1,N,n,eq[n]);
    ll m,d;
    ll tp;
    scanf("%I64d",&m);
    while(m--)
    {
        scanf("%I64d",&d);
        if(d!=0)
        {
            for(int i=1;i<=n;++i)
                dp2[i]=dp[i];
            for(int i=1;i<=d;++i)
            {
                tp=(1<<i);
                dp[i]=tp*(tp-1)/2*(N/tp)-dp2[i]-eq[i];
            }
            for(int i=d+1;i<=n;++i)
            {
                tp=dp2[i]-dp2[i-1];
                dp[i]=dp[i-1]+tp;
            }
        }
        printf("%I64d\n",dp[n]);
    }
    return 0;
}
