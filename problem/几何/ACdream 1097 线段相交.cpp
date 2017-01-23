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
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=550;
struct Point
{
    double x,y;
    Point(){}
    Point(double a,double b)
    {
        x=a;
        y=b;
    }
    void read()
    {
        scanf("%lf%lf",&x,&y);
    }
};
struct Seg
{
    Point p1,p2;
}seg[maxn];
Point px[maxn];
typedef Point Vector;
Vector operator + (Vector A,Vector B)
{
    return Vector(A.x+B.x,A.y+B.y);
}
Vector operator - (Point A,Point B)
{
    return Vector(A.x-B.x,A.y-B.y);
}
Vector operator * (Vector A,double p)
{
    return Vector(A.x*p,A.y*p);
}
Vector operator / (Vector A,double p)
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
double Dot(Vector A,Vector B)
{
    return A.x*B.x+A.y*B.y;
}
double Cross(Vector A,Vector B)
{
    return A.x*B.y-A.y*B.x;
}
double Length(Vector A)
{
    return sqrt(Dot(A,A));
}
double Angle(Vector A,Vector B)
{
    return acos(Dot(A,B))/Length(A)/Length(B);
}

double Area2(Point A,Point B,Point C)
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
bool OnSegment(Point p,Point a1,Point a2)
{
    if(p==a1||p==a2) return true;
    return dcmp(Cross(a1-p,a2-p))==0 && dcmp(Dot(a1-p,a2-p))<0;
}
int cal(Point p,Vector dir,int n)
{
    int cnt=0;
    Point pt;
    for(int i=0;i<n;++i)
    {
        Vector vd=seg[i].p2-seg[i].p1;
        if(dcmp(Cross(dir,vd))==0)
        {
            pt=seg[i].p1;
            if(dcmp(dir.x)==0)
            {
                cnt+=(pt.x==p.x);
                continue;
            }
            double k=(pt.x-p.x)/dir.x;
            if(dcmp(pt.y-(p.y+k*dir.y))==0) cnt++;
            continue;
        }
        pt=GetLineIntersection(p,dir,seg[i].p1,vd);
        if(OnSegment(pt,seg[i].p1,seg[i].p2)) cnt++;
    }
    return cnt;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n,tot=0;
        scanf("%d",&n);
        for(int i=0;i<n;++i)
        {
            seg[i].p1.read();
            seg[i].p2.read();
            px[tot++]=seg[i].p1;
            px[tot++]=seg[i].p2;
        }
        int ans=1;
        for(int i=0;i<tot;++i)
            for(int j=i+1;j<tot;++j)
            {
                if(px[i]==px[j]) continue;
                ans=max(ans,cal(px[i],px[i]-px[j],n));
            }
        printf("%d\n",ans);
    }
    return 0;
}
