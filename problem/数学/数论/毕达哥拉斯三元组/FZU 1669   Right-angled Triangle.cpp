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
int gcd(int a,int b) {return b==0?a:gcd(b,a%b);}
int solve(int n)
{
    int cnt=0;
    int m=sqrt((double)n);
    for(int i=1;i<=m;++i)
    {
        for(int j=i+1;j<=m;j+=2)
        {
            if(i*i+j*j>n) break;
            if(gcd(i,j)!=1) continue;
            int x=j*j-i*i,y=2*i*j,z=i*i+j*j;
            cnt+=n/(x+y+z);
        }
    }
    return cnt;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(cin>>n)
    {
        int ans=solve(n);
        cout<<ans<<endl;
    }
    return 0;
}
