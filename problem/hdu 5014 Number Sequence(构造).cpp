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
const int maxn = 100000 + 10;
int a[maxn],ans[maxn];
void cal(int n)
{
    if(n < 0) return ;
    int m = 0;
    for(int i = 0;i < 20;++i)
    {
        if(n & (1<<i))
            m = i + 1;
    }
    int msk = (1<<m) - 1;
    int low = n^msk;
    for(int i = low;i <= n;++i)
        ans[i] = i^msk;
    cal(low - 1);
}
int main()
{
//    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        for(int i = 0;i <= n;++i)
            scanf("%d",&a[i]);
        cal(n);
        ll sum = 0;
        for(int i = 0;i <= n;++i)
            sum += ans[i]^i;
        printf("%I64d\n",sum);
        for(int i = 0;i <= n;++i)
        {
            if(i) printf(" ");
            printf("%d",ans[a[i]]);
        }
        puts("");
    }
    return 0;
}
