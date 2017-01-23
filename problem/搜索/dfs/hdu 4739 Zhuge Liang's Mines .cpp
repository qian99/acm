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
using namespace std;
struct Point
{
    int x,y;
    bool operator ==(const Point &a) const
    {
        return a.x==x&&a.y==y;
    }
};
struct Square
{
    int a,b,c,d;
};
Point points[30];
bool vis[30],flag[30];
Square sq[30];
int n,m,ans;
int tmp[5];
bool cmp(int a,int b)
{
    return (points[a].y==points[b].y&&points[a].x<points[b].x)||(points[a].y<points[b].y);
}
double Len(Point a,Point b)
{
    return sqrt((double)(a.y-b.y)*(a.y-b.y)+(double)(a.x-b.x)*(a.x-b.x));
}
bool check(int a,int b,int c,int d)
{
    tmp[0]=a;tmp[1]=b;tmp[2]=c;tmp[3]=d;
    for(int i=0;i<4;++i)
      for(int j=i+1;j<4;++j)
        if(points[tmp[i]]==points[tmp[j]]) return false;
    sort(tmp,tmp+4,cmp);
    if(points[tmp[0]].y!=points[tmp[1]].y) return false;
    if(points[tmp[2]].y!=points[tmp[3]].y) return false;
    if(points[tmp[0]].x!=points[tmp[2]].x) return false;
    if(points[tmp[1]].x!=points[tmp[3]].x) return false;
    double t1,t2,t3,t4,t5,t6;
    t1=Len(points[tmp[0]],points[tmp[1]]);
    t2=Len(points[tmp[2]],points[tmp[3]]);
    t3=Len(points[tmp[0]],points[tmp[2]]);
    t4=Len(points[tmp[1]],points[tmp[3]]);
    t5=Len(points[tmp[0]],points[tmp[3]]);
    t6=Len(points[tmp[1]],points[tmp[2]]);
    if(t1!=t2||t1!=t3||t1!=t4||t2!=t3||t2!=t4) return false;
    if(t3!=t4||t5!=t6) return false;
    return true;
}
bool isnsel(int p)
{
    return !flag[sq[p].a]&&!flag[sq[p].b]&&!flag[sq[p].c]&&!flag[sq[p].d];
}
void chs(int p,bool f)
{
    flag[sq[p].a]=f;flag[sq[p].b]=f;
    flag[sq[p].c]=f;flag[sq[p].d]=f;
}
void dfs(int sel)
{
    if(sel>ans) ans=sel;
    for(int i=0;i<m;++i)
    {
        if(!vis[i]&&isnsel(i))
        {
            chs(i,true);
            vis[i]=true;
            dfs(sel+4);
            chs(i,false);
            vis[i]=false;
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d",&n))
    {
        if(n==-1) break;
        for(int i=0;i<n;++i)
          scanf("%d%d",&points[i].x,&points[i].y);
        m=0;
        for(int i=0;i<n;++i)
          for(int j=i+1;j<n;++j)
            for(int k=j+1;k<n;++k)
              for(int l=k+1;l<n;++l)
              {
                  if(check(i,j,k,l))
                  {
                      sq[m].a=i;sq[m].b=j;
                      sq[m].c=k;sq[m].d=l;
                      m++;
                  }
              }
        memset(vis,0,sizeof(vis));
        memset(flag,0,sizeof(flag));
        ans=0;
        dfs(0);
        printf("%d\n",ans);
    }
    return 0;
}
