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
const int maxn=100000+10;
struct Node
{
    ll E,T;
    bool operator <(const Node & a) const
    {
        return E*a.T<a.E*T;//E*T+(a.E+E)*a.T<a.E*a.T+(E+a.E)*T;
    }
}node[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        for(int i=0;i<n;++i)
            scanf("%I64d",&node[i].E);
        for(int i=0;i<n;++i)
            scanf("%I64d",&node[i].T);
        sort(node,node+n);
        ll ans=0,sum=0;
        for(int i=0;i<n;++i)
            ans=ans+(sum+=node[i].E)*node[i].T;
        printf("%I64d\n",ans);
    }
    return 0;
}
