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
const int maxn=100000+10;
struct Point
{
    double x,y,z;
    Point(){}
    Point(double x,double y,double z):x(x),y(y),z(z){};
    void read(){scanf("%lf%lf%lf",&x,&y,&z);}
}pt[maxn],vt[maxn];
struct Node
{
    double st,et;
    bool operator<(const Node &a) const
    {
        return st<a.st;
    }
}node[maxn];
int cnt;
inline void cal(int i,double r)
{
    double a=vt[i].x*vt[i].x+vt[i].y*vt[i].y+vt[i].z*vt[i].z;
    double b=2*(pt[i].x*vt[i].x+pt[i].y*vt[i].y+pt[i].z*vt[i].z);
    double c=(pt[i].x*pt[i].x+pt[i].y*pt[i].y+pt[i].z*pt[i].z)-r*r;
    double tmp=b*b-4*a*c;
    if(tmp<0) return ;
    node[cnt].st=(-b-sqrt(tmp))/2/a;
    node[cnt].et=(-b+sqrt(tmp))/2/a;
    if(node[cnt].st>node[cnt].et) swap(node[cnt].st,node[cnt].et);
    if(node[cnt].et<0) return ;
    if(node[cnt].st<0) node[cnt].st=0;
    cnt++;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        int n;
        double r;
        scanf("%d%lf",&n,&r);
        cnt=0;
        for(int i=0;i<n;++i)
        {
            pt[i].read();
            vt[i].read();
            cal(i,r);
        }
        printf("Case %d: ",tcase);
        if (cnt==0)
        {
            puts("0 0");
        }
        else
        {
            sort(node,node+cnt);
            double minv=node[0].et;
            int ans=0;
            for(int i=1;i<cnt;++i)
            {
                if (node[i].st-minv>eps)
                {
                    ans++;
                    minv=node[i].et;
                }
                minv=min(minv,node[i].et);
            }
            printf("%d %d\n",cnt,ans+1);
        }

    }
    return 0;
}
