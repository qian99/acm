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
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 1000000+10;
ll m[maxn],sum[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,A,B;
    while(~scanf("%d%d%d",&n,&A,&B))
    {
        for(int i = 1;i <= n;++i)
            scanf("%I64d",&sum[i]);
        sum[n+1] = 0;
        for(int i = n;i >= 1;--i)
            sum[i] += sum[i+1];
        ll premx = 0;
        for(int i = n; i >= 1;--i)
        {
            m[i] = sum[i] + premx;
            premx = min(premx,max(-sum[i],A+B-sum[1]-m[i]+1));
        }
        if(A >= m[1]) printf("ALICE\n");
        else printf("BOB\n");
    }
    return 0;
}
