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
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    ll h,a,b,k;
    int tcase = 0;
    while(~scanf("%I64d%I64d%I64d%I64d",&h,&a,&b,&k))
    {
        if(h == 0 && a == 0 && b == 0 && k== 0) break;
        printf("Case #%d: ",++tcase);
        if(a >= h)
        {
            printf("YES\n");
            continue;
        }
        else if(a > b)
        {
            ll tp = h - (k-1)*(a-b);
            if(tp - a <= 0)
            {
                printf("YES\n");
                continue;
            }
            tp += (-a + b*2);
            if(tp < h)
            {
                printf("YES\n");
                continue;
            }
        }
        printf("NO\n");
    }
    return 0;
}