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
const int maxn=200+10;
struct Point
{
    double x,y;
    Point (double x=0,double y=0) :x(x),y(y){}
};
typedef Point Vector;
Point pt[maxn];
int N,N1,N2;
int dcmp(double x)
{
    if(abs(x)<eps) return 0;
    return x>0?1:-1;
}
double ocmp(double x)
{
    if(abs(x)<eps) return 0;
    return x;
}
double Len(Point a,Point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
//x1=xcos(a)+ysin(a)
//y1=ycos(a)-xsin(a)
Vector rotate(Vector vc,double a)
{
    Vector res;
    res.x=vc.x*cos(a)+vc.y*sin(a);
    res.y=vc.y*cos(a)-vc.x*sin(a);
    return res;
}
Point getcp(Point p1,Point p2,double d,double &D)
{
    Point cp;
    int m=abs(N1-N2);
    double a=d*m,b;
    Point mid;
    mid.x=(p1.x+p2.x)/2.0;
    mid.y=(p1.y+p2.y)/2.0;
    double tmp=pi-a;
    if(dcmp(tmp)>=0) b=tmp/2.0;
    else b=(-tmp)/2.0;
    D=Len(p1,p2)/(2.0*cos(b));
    if((N%2==0)&&(m==N/2)) return mid;
    Vector vc=Vector(p2.x-p1.x,p2.y-p1.y);
    if(m>N/2) b=2.0*pi-b;
    vc=rotate(vc,b);
    cp.x=p1.x+vc.x*D/Len(p1,p2);
    cp.y=p1.y+vc.y*D/Len(p1,p2);
    return cp;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    Point p1,p2,cp;
    cin>>N>>N1>>N2;
    cin>>p1.x>>p1.y;
    cin>>p2.x>>p2.y;
    if(N1>N2) {swap(N1,N2);swap(p1,p2);}
    double d=2.0*pi/N,D;
    cp=getcp(p1,p2,d,D);
    int id=N1;
    pt[N1]=p1;
    Vector vc=Vector(p1.x-cp.x,p1.y-cp.y);
    Vector vt;
    for(int i=1;i<N;++i)
    {
        id++;
        if(id==N+1) id=1;
        vt=rotate(vc,d*i);
        pt[id].x=cp.x+vt.x;
        pt[id].y=cp.y+vt.y;
    }
    pt[N2]=p2;
    for(int i=1;i<=N;++i)
      printf("%.6lf %.6lf\n",ocmp(pt[i].x),ocmp(pt[i].y));
    return 0;
}
