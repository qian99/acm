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
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,k;
    double w;
    while(~scanf("%d%lf%d",&n,&w,&k))
    {
        n=n+2;
        double ans=(n-n/k)*w;
        ans/=2.0;
        ans+=eps;
        printf("%.2lf\n",ans);
    }
    return 0;
}
