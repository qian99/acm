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
const int mod=100000007;
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ll S;
    while(~scanf("%lld",&S))
    {
        if(S==0) break;
        int cnt=0;
        ll i=1,tmp,tmp2,ans;
        while(true)
        {
            tmp=i*i*6;
            if(tmp>=S) break;
            tmp2=(S-tmp)/7;
            if((S-tmp)%7==0&&tmp2%i==0)
            {
                ans=tmp2/i;
                cnt++;
                ans%=mod;
                ans=ans*ans%mod;
                ans=ans*2%mod;
                printf("Possible Missing Soldiers = %lld\n",ans);
            }
            i++;
        }
        if(!cnt) printf("No Solution Possible\n");
        printf("\n");
    }
    return 0;
}
