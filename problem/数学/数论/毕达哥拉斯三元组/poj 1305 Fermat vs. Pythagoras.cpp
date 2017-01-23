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
const int maxn=1000000+10;
bool flag[maxn];
int gcd(int a,int b) {return b?gcd(b,a%b):a;}
void solve(int n)
{
    memset(flag,0,sizeof(flag));
    int m=sqrt((double)n);
    int cnt=0;
    for(int i=1;i<=m;++i)
    {
        for(int j=i+1;j<=m;j+=2)
        {
            if(i*i+j*j>n) break;
            if(gcd(i,j)!=1) continue;
            int x=j*j-i*i,y=2*i*j,z=i*i+j*j;
            cnt++;
            for(int k=1;z*k<=n;k++)
                flag[x*k]=flag[y*k]=flag[z*k]=true;
        }
    }
    cout<<cnt<<" ";
    cnt=0;
    for(int i=1;i<=n;++i)
        if(!flag[i]) cnt++;
    cout<<cnt<<endl;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(cin>>n)
    {
        solve(n);
    }
    return 0;
}
