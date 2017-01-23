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
    int n;
    while(cin>>n)
    {
        ll sum=0;
        ll tmp=n*n;
        for(int i=1;i<n;++i)
        {
            sum+=tmp;
            if(i==n-1) break;
            tmp-=2;
        }
        sum+=(tmp/2);
        if(n==1) sum=1;
        cout<<sum<<endl;
    }
    return 0;
}

