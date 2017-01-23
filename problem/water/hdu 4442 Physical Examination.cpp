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
const int maxn=100000+10;
const ll mod=365*24*60*60;
struct Node
{
    int a,b;
    bool operator < (const Node &x) const
    {
        return (double)b/a>(double)x.b/x.a;
    }
};
Node node[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    int n;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        ll sum=0;
        for(int i=0;i<n;++i)
            scanf("%d%d",&node[i].a,&node[i].b);
        sort(node,node+n);
        for(int i=0;i<n;++i)
        {
            sum+=sum*node[i].b+node[i].a;
            sum%=mod;
        }
        printf("%I64d\n",sum);
    }
    return 0;
}
