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
const int maxn=200+10;
const double g=9.8;
double H,L1,R1,L2,R2;
double speed[maxn];
int n;
inline int dcmp(double x)
{
    if(fabs(x)<eps) return 0;
    return x<0?-1:1;
}
inline int check(double x)
{
    if(dcmp(x-L2)>=0&&dcmp(x-R2)<=0) return -1;
    return dcmp(x-L1)>=0&&dcmp(x-R1)<=0;
}
int cal(double d)
{
    double vx,vy,t,x;
    int cnt=0;
    for(int i=0;i<n;++i)
    {
        vx=speed[i]*cos(d);
        vy=speed[i]*sin(d);
        t=(2*vy+sqrt(4*vy*vy+8*g*H))/g/2.0;
        x=vx*t;
        int tmp=check(x);
        if(tmp==-1) return 0;
        cnt+=tmp;
    }
    return cnt;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("hack.out","w",stdout);
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        scanf("%lf%lf%lf%lf%lf",&H,&L1,&R1,&L2,&R2);
        for(int i=0;i<n;++i)
            scanf("%lf",&speed[i]);
        int ans=0;
        double add=pi/1000;
        for(double d=0;d<=pi/2.0;d+=add)
        {
            ans=max(ans,cal(d));
            ans=max(ans,cal(-d));
        }
        printf("%d\n",ans);
    }
    return 0;
}
