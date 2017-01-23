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
    int n;
    scanf("%d",&n);
    int now = 0,h,x;
    ll cost = 0,energy = 0;
    for(int i = 1;i <= n;++i)
    {
        scanf("%d",&h);
        if((now - h) + energy < 0)
        {
            x = h - energy;
            cost += (x - now);
            energy += (x - h);
            now = h;
        }
        else
        {
            energy += (now - h);
            now = h;
        }
    }
    printf("%I64d\n",cost);
    return 0;
}