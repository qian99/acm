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
int num[20],cnt,n;
int val[20];
ll cal(int msk)
{
    cnt=0;
    for(int i=0;i<n;++i)
        if(msk&(1<<i)) num[cnt++]=val[i];
    ll res=0;
    sort(num,num+cnt);
    int i=0;
    while(num[i]==0&&i<cnt) i++;
    if(i==cnt) return 1LL<<50;
    res=num[i];
    for(int j=0;j<i;++j) res*=10;
    i++;
    while(i<cnt) {res*=10;res+=num[i];i++;}
    return res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        for(int i=0;i<n;++i)
            scanf("%d",&val[i]);
        ll ans=Inf,a,b;
        for(int i=1;i<(1<<n);++i)
        {
            a=cal(i);
            b=cal(~i);
            if(a+b<ans) ans=a+b;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
