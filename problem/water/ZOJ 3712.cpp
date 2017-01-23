#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)

using namespace std;
typedef long long ll;
const int maxn=10000+10;
ll calpoint(int s,int t,int point)
{
    ll res=0;
    for(int i=s;i<t;++i)
    {
        res+=(ll)point*(i*2+1);
    }
    return res;
}

int main()
{
    //freopen("in.txt","w",stdin);
    //freopen("out.txt","r",stdout);
    int t;
    cin>>t;
    int a,b,c;
    while(cin>>a>>b>>c)
    {
        ll maxsum=0,minsum=0;
        maxsum+=calpoint(0,c,50);
        maxsum+=calpoint(c,b+c,100);
        maxsum+=calpoint(b+c,a+b+c,300);
        minsum+=calpoint(0,a,300);
        minsum+=calpoint(a,b+a,100);
        minsum+=calpoint(b+a,a+b+c,50);
        cout<<minsum<<" "<<maxsum<<endl;
    }
    return 0;
}
