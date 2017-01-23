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
const int maxn=1000+10;
ll num[maxn];
ll cal(ll x)
{
    ll sum=0;
    while(x)
    {
        sum+=(x%10);
        x/=10;
    }
    if(sum<10) return sum;
    return cal(sum);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        if(n==0) continue;
        for(int i=0;i<n;++i)
          cin>>num[i];
        ll last=1,res=0;
        for(int i=0;i<n;++i)
        {
            last=cal(last*num[i]);
            res+=last;
        }
        cout<<cal(res)<<endl;
    }
    return 0;
}
