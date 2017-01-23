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
const int maxn=300+10;
struct Point
{
    double x,y;
    Point (){};
    Point (double xx,double yy) {x=xx;y=yy;}
    bool operator <(const Point &a) const
    {
        return (x==a.x&&y<a.y)||(x<a.x);
    }
};
typedef Point Vector;
double Cross(Vector A,Vector B) {return A.x*B.y-A.y*B.x;}
Vector operator -(Point a,Point b) {return Vector(a.x-b.x,a.y-b.y);}
Point p[maxn<<1],pt[maxn];
int dcmp(double x)
{
    if(fabs(x)<eps) return 0;
    return x>0?1:-1;
}
bool ConvexHull(int n)
{
    sort(pt,pt+n);
    int m=0;
    for(int i=0;i<n;++i)
    {
        while(m>1&&dcmp(Cross(p[m-1]-p[m-2],pt[i]-p[m-2]))<=0) m--;
        p[m++]=pt[i];
    }
    int k=m;
    for(int i=n-2;i>=0;i--)
    {
        while(m>k&&dcmp(Cross(p[m-1]-p[m-2],pt[i]-p[m-2]))<=0) m--;
        p[m++]=pt[i];
    }
    if(n>1) m--;
    return m==n;
}
int dp[maxn][maxn],w[maxn][maxn],n,mod;
inline int cal(int i,int j)
{
    return (abs((int)p[i].x+(int)p[j].x)*abs((int)p[i].y+(int)p[j].y))%mod;
}
int f(int l,int r)
{
    if(r-l<=2) return 0;
    if(dp[l][r]>=0) return dp[l][r];
    int & ans=dp[l][r];
    ans=inf;
    for(int i=l+1;i<r;++i)
        ans=min(ans,f(l,i)+f(i,r)+w[l][i]+w[i][r]);
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&n,&mod))
    {
        for(int i=0;i<n;++i)
            scanf("%lf%lf",&pt[i].x,&pt[i].y);
        if(!ConvexHull(n))
            printf("I can't cut.\n");
        else
        {
            memset(dp,0xff,sizeof(dp));
            for(int i=0;i<n;++i)
                for(int j=i+2;j<n;++j)
                    w[i][j]=w[j][i]=cal(i,j);
            printf("%d\n",f(0,n-1));
        }
    }
    return 0;
}
