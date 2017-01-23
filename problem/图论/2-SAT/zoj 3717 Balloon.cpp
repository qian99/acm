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
const int maxn=200+10;
const int maxm=1000000+10;
int dcmp(double x) {return (x>eps)-(x<-eps);}
struct Point
{
    double x, y, z;
    Point(double x=0, double y=0, double z=0):x(x),y(y),z(z){}
};
inline double Dis(const Point& a, const Point& b) { return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z));}
inline bool check(const Point& a, const Point& b, double r) {if(dcmp(Dis(a,b)-2*r)>=0) return true; return false;}
struct Edge
{
    int v,next;
};
struct TwoSat
{
    Edge edges[maxm];
    int head[maxn<<1],nEdge,n,m;
    int S[maxn<<1],c;
    bool mark[maxn<<2];
    void Init(int n)
    {
        this->n=n;
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        memset(mark,0,sizeof(mark));
    }
    void AddEdge(int u,int v)
    {
        nEdge++;
        edges[nEdge].v=v;
        edges[nEdge].next=head[u];
        head[u]=nEdge;
    }
    void add_clause(int x,int xval,int y,int yval)
    {
        x=x*2+xval;
        y=y*2+yval;
        AddEdge(x^1,y);
        AddEdge(y^1,x);
    }
    bool dfs(int u)
    {
        if(mark[u^1]) return false;
        if(mark[u]) return true;
        S[c++]=u;
        mark[u]=true;
        for(int k=head[u];k!=-1;k=edges[k].next)
            if(!dfs(edges[k].v)) return false;
        return true;
    }
    bool solve()
    {
        for(int i=0;i<n*2;i+=2)
        {
            if(!mark[i]&&!mark[i+1])
            {
                c=0;
                if(!dfs(i))
                {
                    while(c>0) mark[S[--c]]=false;
                    if(!dfs(i+1)) return false;
                }
            }
        }
        return true;
    }
}twosat;
Point pt[maxn<<1];
int n;
bool test(double r)
{
    twosat.Init(n);
    for(int i=0;i<n;++i)
      for(int j=i+1;j<n;++j)
      {
          if(!check(pt[i*2],pt[j*2],r))
            twosat.add_clause(i,0,j,0);
          if(!check(pt[i*2],pt[j*2+1],r))
            twosat.add_clause(i,0,j,1);
          if(!check(pt[i*2+1],pt[j*2],r))
            twosat.add_clause(i,1,j,0);
          if(!check(pt[i*2+1],pt[j*2+1],r))
            twosat.add_clause(i,1,j,1);
      }
    return twosat.solve();
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d",&n))
    {
        for(int i=0;i<n;++i)
        {
            scanf("%lf%lf%lf",&pt[i*2].x,&pt[i*2].y,&pt[i*2].z);
            scanf("%lf%lf%lf",&pt[i*2+1].x,&pt[i*2+1].y,&pt[i*2+1].z);
        }
        double L=0,R=1e6;
        double m;
        while(dcmp(R-L)>0)
        {
            m=(L+R)/2;
            if(test(m))
              L=m;
            else R=m;
        }
        printf("%.8lf\n",L);
    }
    return 0;
}
