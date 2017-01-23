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
const int maxn=50;
struct Point
{
    double x,y;
    Point(){}
    Point(double xx,double yy):x(xx),y(yy) {}
    bool operator <(const Point &a) const
    {
        return (x==a.x&&y<a.y)||(x<a.x);
    }
}pt[maxn];
Point p[maxn],ch[maxn];
typedef Point Vector;
Vector operator + (Vector A, Vector B){return Vector(A.x+B.x, A.y+B.y);}
Vector operator - (Vector A, Vector B){return Vector(A.x-B.x, A.y-B.y);}
Vector operator * (Vector A, double p){return Vector(A.x*p, A.y*p);}
Vector operator / (Vector A, double p){return Vector(A.x/p, A.y/p);}
double Cross(Vector A, Vector B) {return A.x*B.y - A.y*B.x;}
bool check(int i1,int i2,int i3,int i4)
{
    p[0]=pt[i1];p[1]=pt[i2];p[2]=pt[i3];p[3]=pt[i4];
    sort(p,p+4);
    int m = 0;int n=4;
    for(int i = 0 ; i < n ; ++ i)
    {
        while(m > 1 && Cross(ch[m-1]-ch[m-2], p[i] - ch[m-2]) <= 0) m--;
        ch[m++] = p[i];
    }
    int k = m;
    for(int i = n-2 ; i >= 0 ; -- i)
    {
        while(m > k && Cross(ch[m-1]-ch[m-2], p[i] - ch[m-2]) <= 0) m--;
        ch[m++] = p[i];
    }
    if(n > 1) m--;
    return m==4;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(int i=0;i<n;++i)
            scanf("%lf%lf",&pt[i].x,&pt[i].y);
        int cnt=0;
        for(int i=0;i<n;++i)
            for(int j=i+1;j<n;++j)
                for(int k=j+1;k<n;++k)
                    for(int z=k+1;z<n;++z)
                        if(check(i,j,k,z)) cnt++;
        printf("Case %d: %d\n",++tcase,cnt);
    }
    return 0;
}
