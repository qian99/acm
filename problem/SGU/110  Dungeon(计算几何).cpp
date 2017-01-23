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
const int maxn=55;
struct Point
{
    double x,y,z;
    Point (){};
    Point (double xx,double yy,double zz) {x=xx;y=yy;z=zz;}
    void readit()
    {
        scanf("%lf%lf%lf",&x,&y,&z);
    }
};
struct Sphere
{
    Point center;
    double r;
    void readit()
    {
        center.readit();
        scanf("%lf",&r);
    }
}spheres[maxn];
typedef Point Vector;
int n,lastv;
Vector operator +(Vector a,Vector b) {return Vector(a.x+b.x,a.y+b.y,a.z+b.z);}
Vector operator -(Vector a,Vector b) {return Vector(a.x-b.x,a.y-b.y,a.z-b.z);}
Vector operator *(Vector a,Vector b) {return Vector(a.x*b.x,a.y*b.y,a.z*b.z);}
Vector operator /(Vector a,double d) {return Vector(a.x/d,a.y/d,a.z/d);}
int dcmp(double a)
{
    if(fabs(a)<eps) return 0;
    return a>0?1:-1;
}
double Len(Point a,Point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z));
}
double Len(Vector a){return sqrt(a.x*a.x+a.y*a.y+a.z*a.z);}
int Solve(Point & S, Point & E)
{
    double a,b,c,A1,A2;
    Point vp,p,tmp,p1,p2;
    double minlen=1e10,len1,len2;
    int pos=-1;
    for(int i=1;i<=n;++i)
    {
        if(i==lastv) continue;
        tmp=spheres[i].center;
        vp=Point(E.x-S.x,E.y-S.y,E.z-S.z);
        a=vp.x*vp.x+vp.y*vp.y+vp.z*vp.z;
        b=2*((S.x-tmp.x)*vp.x+(S.y-tmp.y)*vp.y+(S.z-tmp.z)*vp.z);
        c=((S.x-tmp.x)*(S.x-tmp.x)+(S.y-tmp.y)*(S.y-tmp.y)+(S.z-tmp.z)*(S.z-tmp.z)-spheres[i].r*spheres[i].r);
        if(dcmp(b*b-4*a*c)<0) continue;
        A1=((-1.0*b)+sqrt(b*b-4*a*c))/(2*a);
        A2=((-1.0*b)-sqrt(b*b-4*a*c))/(2*a);
        if(A1<0&&A2<0) continue;
        p1=Point(S.x+A1*vp.x,S.y+A1*vp.y,S.z+A1*vp.z);
        p2=Point(S.x+A2*vp.x,S.y+A2*vp.y,S.z+A2*vp.z);
        len1=Len(S,p1);
        len2=Len(S,p2);
        if(A2>=0&&dcmp(len1-len2)>0)
        {
            len1=len2;
            p1=p2;
        }
        if(dcmp(minlen-len1)>0)
        {
            minlen=len1;
            p=p1;
            pos=i;
        }
    }
    if(pos<0) return -1;
    lastv=pos;
    tmp=spheres[pos].center;
    Vector A=Vector(p.x-S.x,p.y-S.y,p.z-S.z);
    Vector B=Vector(tmp.x-p.x,tmp.y-p.y,tmp.z-p.z);
    double val=A.x*B.x+A.y*B.y+A.z*B.z;
    val/=(Len(B)*Len(B));
    Vector C=Vector(B.x*val,B.y*val,B.z*val);
    C=Vector(C.x*2,C.y*2,C.z*2);
    C=A-C;
    E=p+C;
    S=p;
    return pos;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    Point S,E;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        spheres[i].readit();
    S.readit();
    E.readit();
    int ans;
    lastv=-1;
    for(int i=0;;i++)
    {
        ans=Solve(S,E);
        if(ans<0) break;
        if(i==10) {printf("etc.");break;}
        printf("%d ",ans);
    }
    printf("\n");
    return 0;
}

