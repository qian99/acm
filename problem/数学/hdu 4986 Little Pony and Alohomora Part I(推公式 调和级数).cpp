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
const double y = 0.57721566490153286060651209;
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        double ans = 0;
        if(n <= 50000)
        {
            for(int i = 1;i <= n;++i)
                ans += 1.0/i;
            printf("%.4lf\n",ans);
            continue;
        }
        ans = log(n) + y;
        printf("%.4lf\n",ans);
    }
    return 0;
}