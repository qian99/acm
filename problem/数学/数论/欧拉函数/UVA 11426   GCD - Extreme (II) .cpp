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
const int maxn=4000000+10;
int phi[maxn];
ll sum[maxn];
void phi_table()
{
    for(int i=0;i<maxn;++i) phi[i]=i;
    for(int i=2;i<maxn;++i)
    {
        if(phi[i]==i)
        {
            for(int j=i;j<maxn;j+=i)
                phi[j]=phi[j]-phi[j]/i;
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    phi_table();
    memset(sum,0,sizeof(sum));
    for(int i=1;i<maxn;++i)
        for(int j=i*2;j<maxn;j+=i)
            sum[j]+=(ll)i*phi[j/i];
    for(int i=1;i<maxn;++i) sum[i]+=sum[i-1];
    int n;
    while(cin>>n)
    {
        if(n==0) break;
        cout<<sum[n]<<endl;
    }
    return 0;
}
