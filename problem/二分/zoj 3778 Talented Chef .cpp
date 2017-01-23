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
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ll n,m;
    int t;
    cin>>t;
    while(t--)
    {
        cin>>n>>m;
        ll tmp,sum=0,L=0,R,mid;
        for(int i=0;i<n;++i)
        {
            cin>>tmp;
            sum+=tmp;
            L=max(L,tmp);
        }
        R=sum*m;
        while(L<R)
        {
            mid=(L+R)>>1;
            if(mid*m<sum)
                L=mid+1;
            else R=mid;
        }
        cout<<L<<endl;
    }
    return 0;
}

