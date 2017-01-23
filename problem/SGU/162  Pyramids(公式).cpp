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
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    double a,b,c,d,e,f,D,E,F,V,tmp;
    scanf("%lf%lf%lf%lf%lf%lf",&f,&e,&a,&d,&b,&c);
    D=b*b+c*c-d*d;
    E=a*a+c*c-e*e;
    F=a*a+b*b-f*f;
    tmp=4*a*a*b*b*c*c-a*a*D*D-b*b*E*E-c*c*F*F+D*E*F;
    V=1.0/12*sqrt(tmp);
    printf("%.4lf\n",V);
    return 0;
}

