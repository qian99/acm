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
int dcmp(double x)
{
    if(fabs(x)<eps) return 0;
    return x>0?1:-1;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    //y=x-z;
    double X,Y,Z;
    double ans,ax,ay;
    cin>>X>>Y>>Z;
    Z/=60.0;
    ay=Y-Z;
    ax=X+Z;
    if(dcmp(ay-X)>=0&&dcmp(Y-ay)>=0)//ay>=X&&ay<=Y)
    {
        ans=(Y-ax)*(ay-X);
        ans=1-ans/((Y-X)*(Y-X));
    }
    else ans=1;
    printf("%.7lf\n",ans);
    return 0;
}
