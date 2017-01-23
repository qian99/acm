#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
ll solve(int R,int Y,int B)
{
    int sum=0;
    if(R>=2) R-=2,sum+=2;
    else sum+=R,R=0;
    if(Y>=2) Y-=2,sum+=2;
    else sum+=Y,Y=0;
    if(B>=2) B-=2,sum+=2;
    else sum+=B,B=0;
    ll ans=0;
    for(int i=0;i<sum;++i)
      ans+=i;
    ans+=(ll)sum*(R+Y+B);
    return ans;
}

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int R,Y,B;
    while(cin>>R>>Y>>B)
    {
        ll ans=solve(R,Y,B);
        cout<<ans<<endl;
    }
    return 0;
}
