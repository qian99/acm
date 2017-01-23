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
    int a,b;
    while(cin>>a>>b)
    {
        if(a>b) swap(a,b);
        if(a==0&&b==0) cout<<0<<endl;
        else if((int)((b-a)*(sqrt(5.0)+1)/2)==a)
           cout<<0<<endl;
        else cout<<1<<endl;
    }
    return 0;
}
