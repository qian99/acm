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
    int A,B,C,a,b,c;
    cin>>A>>B>>C;
    cin>>a>>b>>c;
    int ans=min(A/a,B/b);
    ans=min(ans,C/c);
    cout<<ans<<endl;
    return 0;
}
