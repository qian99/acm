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
const int maxn = 100+10;
struct Point
{
    double x, y;
    Point(double x=0, double y=0):x(x),y(y){}
};
typedef Point Vector;
Vector operator + (Vector A, Vector B){return Vector(A.x+B.x, A.y+B.y);}
Vector operator - (Vector A, Vector B){return Vector(A.x-B.x, A.y-B.y);}
Vector operator * (Vector A, double p){return Vector(A.x*p, A.y*p);}
Vector operator / (Vector A, double p){return Vector(A.x/p, A.y/p);}
bool operator < (Point a, Point b)
{
    return a.x<b.x ||(a.x == b.x && a.y < b.y);
}
int dcmp(double x)
{
    if(fabs(x)<eps) return 0; else return x < 0 ? -1 : 1;
}
double Dot(Vector A, Vector B) {return A.x*B.x + A.y*B.y;}
double Length(Vector A) {return sqrt(Dot(A,A));}
bool operator == (Point a, Point b)
{
    return dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) == 0;
}
int Cross(Vector A, Vector B) {return A.x*B.y - A.y*B.x;}
int ConvexHull(Point* p, int n, Point* ch)
{
    sort(p, p+n);
    n = unique(p, p+n) - p; //ШЅжи
    int m = 0;
    for(int i = 0 ; i < n ; ++ i)
    {
        while(m > 1 && Cross(ch[m-1]-ch[m-2], p[i] - ch[m-2]) < 0) m--;
        ch[m++] = p[i];
    }
    int k = m;
    for(int i = n-2 ; i >= 0 ; -- i)
    {
        while(m > k && Cross(ch[m-1]-ch[m-2], p[i] - ch[m-2]) < 0) m--;
        ch[m++] = p[i];
    }
    if(n > 1) m--;
    return m;
}
Point pt[maxn<<1],p[maxn<<1];
int main()
{
//    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase = 0;
    scanf("%d",&t);
    while(t--)
    {
        int n,D;
        scanf("%d%d",&n,&D);
        for(int i = 0;i < n;++i)
            scanf("%lf%lf",&pt[i].x,&pt[i].y);
        int m = ConvexHull(pt,n,p);
        double sum = 0;
        for(int i = 1;i < m;++i)
            sum += Length(p[i] - p[i-1]);
        sum += Length(p[m-1] - p[0]);
        printf("Case #%d: %.4lf\n",++tcase,sum/(pi*D));
    }
    return 0;
}
