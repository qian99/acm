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
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(cin>>n)
    {
        if(n>=0)
        {
            cout<<n<<endl;
        }
        else
        {
            n=-n;
            int a=n/10;
            int b=(n/100)*10+n%10;
            n=max(-a,-b);
            cout<<n<<endl;
        }
    }
    return 0;
}