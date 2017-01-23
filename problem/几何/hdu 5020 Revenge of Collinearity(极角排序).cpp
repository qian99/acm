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
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 1000 + 10;
struct Point
{
    ll x,y;
    Point(ll x = 0,ll y = 0):x(x),y(y){}
    void read()
    {
        scanf("%I64d%I64d",&x,&y);
    }
    bool operator < (const Point & a) const
    {
        return (x == a.x && y < a.y) || (x < a.x);
    }
    Point operator - (const Point & a) const
    {
        return Point(x - a.x,y - a.y);
    }
}pt[maxn];
typedef Point Vector;
Vector vt[maxn];
inline double dcmp(double x)
{
    if(fabs(x) < eps) return 0;
    return x < 0 ? -1 : 1;
}
bool cmp(Point a,Point b)
{
    ll tmp = a.x*b.y - a.y*b.x;
    return tmp == 0 ?(a.x == b.x ? a.y < b.y : a.x < b.x ):tmp < 0;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n;
        scanf("%d",&n);
        for(int i = 0;i < n;++i)
            pt[i].read();
        sort(pt,pt + n);
        ll ans = 0;
        for(int i = 0;i < n;++i)
        {
            int tot = 0;
            for(int j = i+1;j < n;++j)
            {
                vt[tot] = pt[j] - pt[i];
//                vt[tot].convert();
                tot++;
            }
            sort(vt,vt + tot,cmp);
            int last = 0,now = 0;
            for(int k = 0;k < tot;++k)
            {
                if(vt[k].x*vt[last].y == vt[last].x*vt[k].y)
                    now++;
                else
                {
                    ans += now*(now-1)/2;
                    last = k;
                    now = 1;
                }
            }
            if(now)
                ans += now*(now-1)/2;
        }
        printf("%I64d\n",ans);
    }
    return 0;
}
