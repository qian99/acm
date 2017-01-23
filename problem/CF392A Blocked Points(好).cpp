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
    ll n;
    cin>>n;
    if(n==0)
        cout<<1<<endl;
    else
    {
        ll i,j=n,ans=0;
        for(i=1;i<=n;++i)
        {
            while(i*i+(j-1)*(j-1)>n*n&&(i-1)*(i-1)+j*j>n*n) j--;
            while(i*i+(j-1)*(j-1)<=n*n||(i-1)*(i-1)+j*j<=n*n)
            {
                ans++;
                if(i*i+(j-1)*(j-1)<=n*n) break;
                j--;
            }
        }
        cout<<ans*4<<endl;
    }
    return 0;
}
