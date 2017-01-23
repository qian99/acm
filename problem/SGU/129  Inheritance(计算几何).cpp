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
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=400+10;
struct Point
{
    double x,y;
    Point () {};
    Point (double xx,double yy) {x=xx;y=yy;}
    bool operator < (const Point &a) const
    {
        return (x==a.x&&y<a.y)||(x<a.x);
    }
}p[maxn];
typedef Point Vector;
Vector operator - (Point a,Point b) {return Vector(a.x-b.x,a.y-b.y);}
double Cross(Vector a,Vector b)
{
    return a.x*b.y-a.y*b.x;
}
double Dot(Vector a,Vector b)
{
    return a.x*b.x+a.y*b.y;
}
int dcmp(double x)
{
    if(fabs(x)<eps) return 0;
    return x>0?1:-1;
}
bool operator ==(Point a,Point b) {return dcmp(a.x-b.x)==0&&dcmp(a.y-b.y)==0;}
double Len(Point a,Point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
Point sp[maxn];
int ConvexHull(int n)
{
    int m=0;
    sort(p,p+n);
    for(int i=0;i<n;++i)
    {
        while(m>1&&Cross(sp[m-1]-sp[m-2],p[i]-sp[m-2])<=0) m--;
        sp[m++]=p[i];
    }
    int k=m;
    for(int i=n-2;i>=0;--i)
    {
        while(m>k&&Cross(sp[m-1]-sp[m-2],p[i]-sp[m-2])<=0) m--;
        sp[m++]=p[i];
    }
    if(n>1) m--;
    return m;
}
bool isInSeg(Point S,Point E,Point pp)
{
    return (dcmp(Cross(S-pp,E-pp))==0)&&(dcmp(Dot(S-pp,E-pp))<0);
}
int isInpoly(Point pp,int n)
{
    for(int i=0;i<n;++i)
    {
        if(dcmp(sp[i].x-pp.x)==0&&dcmp(sp[i].y-pp.y)==0) return i;
        if(isInSeg(sp[i],sp[i+1],pp)) return i;
        double d=Cross(sp[i+1]-sp[i],pp-sp[i]);
        int v=dcmp(d);
        if(v<0) return -2;
    }
    return -1;
}
bool isSegIntersect(Point a1,Point a2,Point b1,Point b2)
{
    double c1=Cross(a2-a1,b1-a1),c2=Cross(a2-a1,b2-a1),
            c3=Cross(b2-b1,a1-b1),c4=Cross(b2-b1,a2-b1);
    return dcmp(c1)*dcmp(c2)<0&&dcmp(c3)*dcmp(c4)<0;
}
Point getSegPoint(Point p0,Point p1,Point p2,Point p3)
{
    if(dcmp(p2.y-p3.y)==0) {swap(p0,p2);swap(p1,p3);}
    if(dcmp(p1.x-p0.x)==0) {swap(p0,p2);swap(p1,p3);}
    int d1=dcmp(p1.y-p0.y);
    int d2=dcmp(p3.x-p2.x);
    if(d1==0&&d2==0) return Point(p2.x,p0.y);
    if(d1==0) return Point(p2.x+(p0.y-p2.y)/(p3.y-p2.y)*(p3.x-p2.x),p0.y);
    if(d2==0) return Point(p2.x,p0.y+(p2.x-p0.x)/(p1.x-p0.x)*(p1.y-p0.y));
    double a=p1.x-p0.x;
    double b=p3.x-p2.x;
    double c=p1.y-p0.y;
    double d=p3.y-p2.y;
    double t=((p2.y-p0.y)-c/a*(p2.x-p0.x))/(b*c/a-d);
    double k=((p2.x-p0.x)+t*b)/a;
    return Point(p0.x+k*a,p0.y+k*c);
}
double solve(int n,int M)
{
    Point p0,p1,p2,p3;
    Point cp[5];
    int m;bool flag;
    scanf("%lf%lf%lf%lf",&p0.x,&p0.y,&p1.x,&p1.y);
    int va=isInpoly(p0,M),vb=isInpoly(p1,M);
    if(va==-1)
    {
        if(vb>=-1) return Len(p0,p1);
        for(int i=0;i<M;++i)
        {
            if(isInSeg(p0,p1,sp[i])) return Len(p0,sp[i]);
            if(isSegIntersect(p0,p1,sp[i],sp[i+1]))
            {
                Point tmp=getSegPoint(p0,p1,sp[i],sp[i+1]);
                return Len(tmp,p0);
            }
        }
    }
    else if(va==-2)
    {
        if(vb>=0)
        {
            if(sp[vb]==p1)
            {
                if(Cross(sp[vb+1]-p1,p1-p0)==0||Cross(sp[(vb-1+M)%M]-p1,p1-p0)==0)
                    return 0;
            }
            else if(Cross(sp[vb+1]-p1,p1-p0)==0) return 0;
            flag=(sp[vb]==p1);
            for(int i=0;i<M;++i)
            {
                if(sp[i]==p1) continue;
                if(isInSeg(p0,p1,sp[i]))
                {
                    if(flag&&i!=((vb+1)%M)&&i!=((vb-1+M)%M))  return Len(p1,sp[i]);
                    if(!flag&&i!=((vb+1)%M)) return Len(p1,sp[i]);
                }
                if(isSegIntersect(p0,p1,sp[i],sp[i+1]))
                {
                    Point tmp=getSegPoint(p0,p1,sp[i],sp[i+1]);
                    return Len(tmp,p1);
                }
            }
            return 0;
        }
        m=0;
        for(int i=0;i<M;++i)
        {
            if(isInSeg(p0,p1,sp[i]))
            {
                if(isInSeg(p0,p1,sp[i+1])) return 0;
                cp[m++]=sp[i];continue;
            }
            if(isSegIntersect(p0,p1,sp[i],sp[i+1]))
            {
                Point tmp=getSegPoint(p0,p1,sp[i],sp[i+1]);
                cp[m++]=tmp;
            }
        }
        if(m==0) return 0;
        if(vb==-2&&m==1) return 0;
        if(m==1) return Len(p1,cp[0]);
        return Len(cp[0],cp[1]);
    }
    if(vb==-1) return Len(p0,p1);
    if(p0==sp[va])
    {
        if(Cross(sp[va+1]-p0,p1-p0)==0||Cross(sp[(va-1+M)%M]-p0,p1-p0)==0)
            return 0;
    }
    else if(Cross(sp[va+1]-p0,p1-p0)==0)
        return 0;
    if(vb>=0) return Len(p0,p1);
    flag=(p0==sp[va]);
    for(int i=0;i<M;++i)
    {
        if(sp[i]==p0) continue;
        if(isInSeg(p0,p1,sp[i]))
        {
            if(flag&&i!=((va+1)%M)&&i!=((va-1+M)%M))  return Len(p0,sp[i]);
            if(!flag&&i!=((va+1)%M)) return Len(p0,sp[i]);
        }
        if(isSegIntersect(p0,p1,sp[i],sp[i+1]))
        {
            Point tmp=getSegPoint(p0,p1,sp[i],sp[i+1]);
            return Len(p0,tmp);
        }
    }
    return 0;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    scanf("%d",&n);
    for(int i=0;i<n;++i)
      scanf("%lf%lf",&p[i].x,&p[i].y);
    int M=ConvexHull(n);
    scanf("%d",&m);
    while(m--)
    {
        double ans=solve(n,M);
        printf("%.2lf\n",ans);
    }
    return 0;
}

