#include <iostream>
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
typedef long long LL;
const int maxn=100+10;
const double oo=1e40;
double w[maxn][maxn];
double lx[maxn],ly[maxn],slack[maxn];
int lefts[maxn];
bool S[maxn],T[maxn];
int n;
struct Point
{
    double x,y;
};
Point pl[maxn],pr[maxn];
bool match(int u)
{
    S[u]=true;
    for(int v=1;v<=n;++v)
    {
        double tmp=lx[u]+ly[v]-w[u][v];
        if(!T[v])
        {
            if(fabs(tmp)<eps)
            {
                T[v]=true;
                if(!lefts[v]||match(lefts[v]))
                {
                    lefts[v]=u;
                    return true;
                }
            }
            else slack[v]=min(slack[v],tmp);
        }
    }
    return false;
}
void update()
{
    double d=oo;
    for(int i=1;i<=n;++i) if(!T[i])
          d=min(d,slack[i]);
    for(int i=1;i<=n;++i)
    {
        if(S[i]) lx[i]-=d;
        if(T[i]) ly[i]+=d;
        //slack[i]-=d;
    }
}
void KM()
{
    for(int i=1;i<=n;++i)
    {
        lx[i]=oo;
        lefts[i]=0;
        ly[i]=0;
        for(int j=1;j<=n;++j)
          lx[i]=max(lx[i],w[i][j]);
    }
    for(int i=1;i<=n;++i)
    {
        for(int k=1;k<=n;++k) slack[k]=oo;
        for(;;)
        {
            for(int j=1;j<=n;++j) S[j]=T[j]=0;
            if(match(i))
              break;
            else
              update();
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    bool first=true;
    while(~scanf("%d",&n))
    {
        if(!first) printf("\n");
        first=false;
        for(int i=1;i<=n;++i)
          scanf("%lf%lf",&pl[i].x,&pl[i].y);
        for(int i=1;i<=n;++i)
          scanf("%lf%lf",&pr[i].x,&pr[i].y);
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                w[i][j]=-sqrt((pr[i].y-pl[j].y)*(pr[i].y-pl[j].y)+(pr[i].x-pl[j].x)*(pr[i].x-pl[j].x));
        KM();
        for(int i=1;i<=n;++i)
          printf("%d\n",lefts[i]);
    }
    return 0;
}

