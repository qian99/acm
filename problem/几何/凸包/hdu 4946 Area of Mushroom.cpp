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
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn =500 + 10;
struct Point
{
    int x, y;
    Point(int x=0, int y=0):x(x),y(y){}
};
typedef Point Vector;
Vector operator + (Vector A, Vector B){return Vector(A.x+B.x, A.y+B.y);}
Vector operator - (Vector A, Vector B){return Vector(A.x-B.x, A.y-B.y);}
Vector operator * (Vector A, int p){return Vector(A.x*p, A.y*p);}
Vector operator / (Vector A, int p){return Vector(A.x/p, A.y/p);}
bool operator < (Point a, Point b)
{
    return a.x<b.x ||(a.x == b.x && a.y < b.y);
}
int dcmp(double x)
{
    if(fabs(x)<eps) return 0; else return x < 0 ? -1 : 1;
}
bool operator == (Point a, Point b)
{
    return a.x == b.x && a.y == b.y;
    //return dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) == 0;
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
int ans[maxn],S[maxn];
pair<int,Point>pnode[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,tcase = 0;
    while(~scanf("%d",&n))
    {
        if(n == 0) break;
        int x, y ,v ,vmax = 0;
        for(int i = 0; i < n;++i)
        {
            scanf("%d%d%d",&x,&y,&v);
            pnode[i] = make_pair(v,Point(x,y));
            vmax = max(v,vmax);
        }
        printf("Case #%d: ",++tcase);
        memset(ans,0,sizeof(ans));
        if(vmax)
        {
            int m = 0;
            for(int i = 0;i < n;++i)
                if(pnode[i].first == vmax)
                    p[m++] = pnode[i].second;
            m = ConvexHull(p,m,pt);
            for(int i = 0;i < m;++i)
            {
                int cnt = 0;
                for(int j = 0; j < n;++j)
                {
                    if(pnode[j].first == vmax && pt[i] == pnode[j].second)
                        S[cnt++] = j;
                }
                if(cnt == 1) ans[S[0]] = 1;
                else
                {
                    for(int k = 0;k < cnt;++k)
                        ans[S[k]] = 0;
                }
            }
        }
        for(int i = 0;i < n;++i)
            printf("%d",ans[i]);
        printf("\n");
    }
    return 0;
}
