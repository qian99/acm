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
    int n,k,A,C;
    cin>>n>>k;
    A=C=1;
    if(k<=n)
    {
        for(int i=0;i<k;i++) A*=(n-i);
        for(int i=1;i<=k;++i) C*=i;
        C=A/C;
        cout<<A*C<<endl;
    }
    else cout<<"0"<<endl;
    return 0;
}
