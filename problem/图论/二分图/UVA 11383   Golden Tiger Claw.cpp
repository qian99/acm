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
const int maxn=500+10;
int w[maxn][maxn];
int lx[maxn],ly[maxn],link[maxn],slack[maxn];
bool S[maxn],T[maxn];
int n;
bool match(int u)
{
    S[u]=true;
    for(int i=1;i<=n;++i)
    {
        if(!T[i])
        {
            if(lx[u]+ly[i]==w[u][i])
            {
                T[i]=true;
                if(!link[i]||match(link[i]))
                {
                    link[i]=u;
                    return true;
                }
            }
            else
                slack[i]=min(slack[i],lx[u]+ly[i]-w[u][i]);
        }
    }
    return false;
}
void update()
{
    int d=inf;
    for(int i=1;i<=n;++i) if(!T[i])
      d=min(d,slack[i]);
    for(int i=1;i<=n;++i)
    {
        if(S[i]) lx[i]-=d;
        if(T[i]) ly[i]+=d;
    }
}
void KM()
{
    for(int i=1;i<=n;++i)
    {
        link[i]=lx[i]=ly[i]=0;
        for(int j=1;j<=n;++j)
          lx[i]=max(lx[i],w[i][j]);
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j) slack[j]=inf;
        for(;;)
        {
            for(int k=1;k<=n;++k) S[k]=T[k]=0;
            if(match(i)) break;
            else update();
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d",&n))
    {
        for(int i=1;i<=n;++i)
          for(int j=1;j<=n;++j)
             scanf("%d",&w[i][j]);
        KM();
        printf("%d",lx[1]);
        for(int i=2;i<=n;++i)
          printf(" %d",lx[i]);
        printf("\n%d",ly[1]);
        for(int i=2;i<=n;++i)
          printf(" %d",ly[i]);
        printf("\n");
        int sum=0;
        for(int i=1;i<=n;++i)
        {
            sum+=ly[i]+lx[i];
        }
        printf("%d\n",sum);

    }
    return 0;
}
