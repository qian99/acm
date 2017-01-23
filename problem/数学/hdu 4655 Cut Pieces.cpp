#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<vector>
#define inf 2139062143
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=1000000+10;
const int mod=1000000000+7;
ll num[maxn],res[maxn],lf[maxn],rf[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n;
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
           scanf("%I64d",&num[i]);
        sort(num+1,num+n+1);
        int m=0;
        for(int i=1;i<=n/2+1;++i)
        {
            res[++m]=num[i];
            res[++m]=num[n-i+1];
        }
        lf[0]=rf[n+1]=1;
        lf[1]=res[1];rf[n]=res[n];
        for(int i=2;i<=n;++i)
        {
            lf[i]=(lf[i-1]*res[i])%mod;
            rf[n-i+1]=(rf[n-i+2]*res[n-i+1])%mod;
        }
        ll mul=(lf[n]*n)%mod;
        ll zz=0,temp;
        for(int i=1;i<n;++i)
        {
            temp=min(res[i],res[i+1]);
            zz+=(((lf[i-1]*rf[i+2])%mod)*temp)%mod;
        }
        mul=((mul-zz)%mod+mod)%mod;
        printf("%I64d\n",mul);
    }
    return 0;
}
