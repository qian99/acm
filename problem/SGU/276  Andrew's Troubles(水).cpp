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
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int S,P,ans=0;
    cin>>S>>P;
    P-=S;
    if(P<=0) ans=0;
    else if(P<300) ans=1;
    else if(P<900) ans=2;
    else if(P<1800) ans=3;
    else ans=4;
    cout<<ans<<endl;
    return 0;
}
