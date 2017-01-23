/*
* this code is made by qian99
* Problem: 1106
* Verdict: Accepted
* Submission Date: 2014-06-14 20:44:14
* Time: 16 MS
* Memory: 1900 KB
*/
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
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
typedef double type;
const double PI=acos(-1.0);
struct Point
{
    type x,y;
    Point(){}
    Point(type a,type b)
    {
        x=a;
        y=b;
    }
    void read()
    {
        scanf("%lf%lf",&x,&y);
    }
    void print()
    {
        printf("%.6lf %.6lf\n",x,y);
    }
 
};
typedef Point Vector;
Vector operator + (Vector A,Vector B)
{
    return Vector(A.x+B.x,A.y+B.y);
}
Vector operator - (Point A,Point B)
{
    return Vector(A.x-B.x,A.y-B.y);
}
Vector operator * (Vector A,type p)
{
    return Vector(A.x*p,A.y*p);
}
Vector operator / (Vector A,type p)
{
    return Vector(A.x/p,A.y/p);
}
bool operator < (const Point &a,const Point &b)
{
    return a.x<b.x || (a.x==b.x && a.y<b.y);
}
 
int dcmp(double x)
{
    if (fabs(x)<eps) return 0;
    else return x<0?-1:1;
}
bool operator == (const Point& a,const Point b)
{
    return dcmp(a.x-b.x)==0 && dcmp(a.y-b.y)==0;
}
//atan2(x,y) :向量(x,y)的极角，即从x轴正半轴旋转到该向量方向所需要的角度。
type Dot(Vector A,Vector B)
{
    return A.x*B.x+A.y*B.y;
}
type Cross(Vector A,Vector B)
{
    return A.x*B.y-A.y*B.x;
}
type Length(Vector A)
{
    return sqrt(Dot(A,A));
}
type Angle(Vector A,Vector B)
{
    return acos(Dot(A,B))/Length(A)/Length(B);
}
 
type Area2(Point A,Point B,Point C)
{
    return Cross(B-A,C-A);
}
Vector Rotate(Vector A,double rad)
{
    return Vector(A.x*cos(rad)-A.y*sin(rad),A.x*sin(rad)+A.y*cos(rad));
}
 
Vector Normal(Vector A)//单位法线,左转90度，长度归一
{
    double L=Length(A);
    return Vector(-A.y/L,A.x/L);
}
 
Point GetLineIntersection(Point P,Vector v,Point Q,Vector w)
{
    Vector u=P-Q;
    double t=Cross(w,u)/Cross(v,w);
    return P+v*t;
}
 
double DistanceToLine(Point P,Point A,Point B)
{
    Vector v1=B-A,v2=P-A;
    return fabs(Cross(v1,v2))/Length(v1);
}
double DistanceToSegment(Point P,Point A,Point B)
{
    if (A==B) return Length(P-A);
    Vector v1=B-A,v2=P-A,v3=P-B;
    if (dcmp(Dot(v1,v2))<0) return Length(v2);
    else if (dcmp(Dot(v1,v3))>0) return Length(v3);
    else return fabs(Cross(v1,v2))/Length(v1);
}
Point GetLineProjection(Point P,Point A,Point B)//P在AB上的投影
{
    Vector v=B-A;
    return A+v*(Dot(v,P-A)/Dot(v,v));
}
 
bool SegmentProperIntersection(Point a1,Point a2,Point b1,Point b2)
{
    double c1=Cross(a2-a1,b1-a1),c2=Cross(a2-a1,b2-a1),
    c3=Cross(b2-b1,a1-b1),c4=Cross(b2-b1,a2-b1);
    return dcmp(c1)*dcmp(c2)<0 && dcmp(c3)*dcmp(c4)<0;
}
 
bool OnSegment(Point p,Point a1,Point a2)
{
    return dcmp(Cross(a1-p,a2-p))==0 && dcmp(Dot(a1-p,a2-p))<0;
}
const int maxn=1000+10;
Point a[maxn],b[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    scanf("%d",&n);
    for(int i=0;i<n;++i)
        a[i].read();
    scanf("%d",&m);
    for(int i=0;i<m;++i)
        b[i].read();
    a[n]=a[0];b[m]=b[0];
    double minv=DistanceToSegment(a[0],b[0],b[1]);
    for(int i=0;i<n;++i)
    {
        double tmp;
        for(int j=0;j<m;++j)
        {
            tmp=DistanceToSegment(a[i],b[j],b[j+1]);
            minv=min(minv,tmp);
        }
    }
    for(int i=0;i<m;++i)
    {
        double tmp;
        for(int j=0;j<n;++j)
        {
            tmp=DistanceToSegment(b[i],a[j],a[j+1]);
            minv=min(minv,tmp);
        }
    }
    printf("%.4lf\n",minv);
    return 0;
}