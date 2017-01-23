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
const int maxn=10000+10;
struct Point
{
    int x,y;
    Point(int x=0, int y=0):x(x),y(y){}
};
struct Edge
{
    Point a,b;
    void read()
    {
        scanf("%d%d%d%d",&a.x,&a.y,&b.x,&b.y);
    }
};
Edge edges[maxn];
map<pair<int,int>,int>mp;
Point pt[maxn];
int n,pp;
int dcmp(double x)
{
    if(fabs(x)<eps) return 0; else return x < 0 ? -1 : 1;
}
double Cross(Point A, Point B) {return A.x*B.y - A.y*B.x;}
Point operator - (Point A, Point B){return Point(A.x-B.x, A.y-B.y);}
bool SegmentProperIntersection(Point a1, Point a2, Point b1, Point b2)
{
    double c1 = Cross(a2-a1,b1-a1), c2 = Cross(a2-a1,b2-a1),
           c3 = Cross(b2-b1,a1-b1), c4 = Cross(b2-b1,a2-b1);
    return dcmp(c1)*dcmp(c2)<0 && dcmp(c3)*dcmp(c4)<0;
}
bool ins(Edge e,Point s)
{
    if(e.a.x==e.b.x&&s.x==e.a.x)
      return e.a.y>e.b.y?(s.y>=e.b.y&&s.y<=e.a.y):(s.y>=e.a.y&&s.y<=e.b.y);
    if(e.a.y==e.b.y&&s.y==e.a.y)
      return e.a.x>e.b.x?(s.x>=e.b.x&&s.x<=e.a.x):(s.x>=e.a.x&&s.x<=e.b.x);
    return false;
}
bool check(Point a,Point s,Point c)
{
    if(a.x<=s.x||a.y<=s.y) return 0;
    if(a.y-s.y==a.x-s.x)
    {
        if(mp[make_pair(a.x,a.y)])
        {
            Point d=pt[mp[make_pair(a.x,a.y)]];
            if(c.y>s.y) return d.x<s.x?1:0;
            if(c.y<s.y) return d.x>s.x?1:0;
            if(c.x>s.x) return d.y<s.y?1:0;
            return d.y>s.y?1:0;
        }
        else
        {
            mp[make_pair(a.x,a.y)]=pp;
            pt[pp++]=c;
            return 1;
        }
    }
    return 0;
}
int solve(Point s)
{
    Edge ee;
    ee.a=s;ee.b=s;
    ee.b.x+=40000;
    ee.b.y+=40000;
    int cnt=0,pnt=0;
    for(int i=0;i<n;++i)
    {
        if(ins(edges[i],s)) return 0;
        if(SegmentProperIntersection(ee.a,ee.b,edges[i].a,edges[i].b))
           cnt++;
        pnt+=check(edges[i].a,s,edges[i].b);
        pnt+=check(edges[i].b,s,edges[i].a);
    }
    cnt=cnt-pnt;
    if(cnt&1) return 1;
    return -1;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d",&n);
    mp.clear();
    for(int i=0;i<n;++i)
    {
        edges[i].read();
    }
    Point s;
    scanf("%d%d",&s.x,&s.y);
    pp=1;
    int ans=solve(s);
    if(ans==1) printf("INSIDE\n");
    else if(ans==0) printf("BORDER\n");
    else printf("OUTSIDE\n");
    return 0;
}
