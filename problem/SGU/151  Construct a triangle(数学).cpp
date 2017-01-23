#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
double c,b,m;
double dcmp(double x)
{
    if(fabs(x)<eps) return 0;
    return x>0?1:-1;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%lf%lf%lf",&c,&b,&m);
    double x=(4*m*m-c*c-b*b)/(2*c);
    double y=b*b-x*x;
    if(dcmp(y)<0)
    {
        printf("Mission impossible\n");
    }
    else
    {
        if(dcmp(x)==0) x=0;
        if(dcmp(y)==0) y=0;
        y=sqrt(y);
        printf("%.5lf %.5lf\n",0.0,0.0);
        printf("%.5lf %.5lf\n",c,0.0);
        printf("%.5lf %.5lf\n",x,y);
    }
    return 0;
}

