#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<set>
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
    int t;
    ll pos,len,n,x;
    cin>>t;
    while(t--)
    {
        cin>>n;
        pos=1;len=1;
        while(n>len)
        {
            n-=len;
            x=++pos;
            while(x) {len++;x/=10;}
        }
        for(ll i=1;i<=pos;++i)
        {
            x=i;len=0;
            while(x) {len++;x/=10;}
            if(n>len) n-=len;
            else
            {
                x=i;
                for(int j=0;j<len-n;++j)
                    x/=10;
                cout<<(x%10)<<endl;
                break;
            }
        }
    }
    return 0;
}
