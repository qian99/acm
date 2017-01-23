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
const int maxn=10000+10;
int num[maxn],n,m,k;
int f(int x,int p)
{
    int b=x,res=1;
    while(p)
    {
        if(p&1) res=(res*b)%k;
        b=(b*b)%k;
        p>>=1;
    }
    return res%k;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(cin>>n>>m>>k)
    {
        int cnt=0;
        int x;
        for(int i=0;i<n;++i)
        {
            cin>>x;
            if(f(x,m)==0) cnt++;
        }
        cout<<cnt<<endl;
    }
    return 0;
}
