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
#include<bitset>
#include<set>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100+10;
double p[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;++i)
        scanf("%lf",&p[i]);
    sort(p,p+n);
    double now=0,last=1;
    for(int i=n-1;i>=0&&last>now;--i)
    {
        now=now+p[i]*(last-now);
        last*=(1-p[i]);
    }
    printf("%.10lf\n",now);
    return 0;
}
