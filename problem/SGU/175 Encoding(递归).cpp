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
int f(int n,int p)
{
    if(n==1) return 1;
    int k=n/2;
    if(p>k) return f(n-k,(n-k)-(p-k)+1);
    return n-k+f(k,k-p+1);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,q;
    cin>>n>>q;
    cout<<f(n,q)<<endl;
    return 0;
}
