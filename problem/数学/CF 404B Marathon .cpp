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
const int maxn=1000000+10;
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    double a,d;
    int n;
    scanf("%lf%lf",&a,&d);
    scanf("%d",&n);
    ll A=(a+eps)*10000;
    ll D=(d+eps)*10000;
    for(int i=1;i<=n;++i)
    {
        ll tmp=(i*D)%(4*A);
        if(tmp<=A)
        {
            printf("%.5lf %.5lf\n",tmp/10000.0,0.0);
        }
        else if(tmp<=2*A)
        {
            tmp-=A;
            printf("%.5lf %.5lf\n",a,tmp/10000.0);
        }
        else if(tmp<=3*A)
        {
            tmp-=2*A;
            printf("%.5lf %.5lf\n",a-tmp/10000.0,a);
        }
        else
        {
            tmp-=3*A;
            printf("%.5lf %.5lf\n",0.0,a-tmp/10000.0);
        }
    }
    return 0;
}