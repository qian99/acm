/*
* this code is made by qian99
* Problem: 1071
* Verdict: Accepted
* Submission Date: 2014-05-09 22:17:18
* Time: 1476 MS
* Memory: 4800 KB
*/
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
const int maxn=200000+10;
int a[maxn],cnt[maxn];
ll sum[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        memset(cnt,0,sizeof(cnt));
        memset(sum,0,sizeof(sum));
        int maxv=0;
        for(int i=0;i<n;++i)
        {
            scanf("%d",&a[i]);
            maxv=max(maxv,a[i]);
            cnt[a[i]]++;
        }
        int N=0;
        sort(a,a+n);
        sum[0]=1;
        for(int i=1;i<n;++i)
        {
            if(a[i]==a[i-1]) sum[N]++;
            else
            {
                a[++N]=a[i];
                sum[N]=1;
            }
        }
        sum[N+1]=0;
        for(int i=N;i>=0;--i) sum[i]+=sum[i+1];
        ll ans=0,tmp;
        for(int i=0;i<N;++i)
        {
            tmp=0;
            for(int j=a[i]*2;j<=maxv;j+=a[i])
                tmp+=cnt[j];
            ans+=(sum[i+1]-tmp)*cnt[a[i]];
        }
//        cout<<ans<<endl;
        printf("%lld\n",ans);
    }
    return 0;
}
