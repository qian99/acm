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
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=3000+10;
struct Edge
{
    int u,v;
    double w;
    bool operator <(const Edge &a) const
    {
        return w<a.w;
    }
};
struct Point
{
    int x,y;
};
Edge edges[maxn];
double a[55][55];
Point p[55];
double Len(Point a,Point b)
{
    return sqrt((double)(a.x-b.x)*(a.x-b.x)+(double)(a.y-b.y)*(a.y-b.y));
}
int parents[55];
int Find(int x)
{
    return x==parents[x]?x:parents[x]=Find(parents[x]);
}
bool Uion(int x,int y)
{
    int a=Find(x);
    int b=Find(y);
    if(b!=a)
    {
        parents[b]=a;
        return true;
    }
    return false;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        int ax,ay;
        double ans=0;
        scanf("%d%d",&ax,&ay);
        if(ax>ay) swap(ax,ay);
        for(int i=0;i<=n;++i) parents[i]=i;
        for(int i=1;i<=n;++i)
           scanf("%d%d",&p[i].x,&p[i].y);
        int m=0;
        for(int i=1;i<=n;++i)
          for(int j=i+1;j<=n;++j)
          {
              edges[m].u=i;edges[m].v=j;
              edges[m].w=Len(p[i],p[j]);
              if(i==ax&&j==ay)
              {
                  Uion(i,j);
                  ans=edges[m].w;
              }
              m++;
          }
        sort(edges+1,edges+m+1);
        for(int i=1;i<=m;++i)
        {
            if(Uion(edges[i].u,edges[i].v))
              ans+=edges[i].w;
        }
        printf("%.2lf\n",ans);
    }
    return 0;
}
