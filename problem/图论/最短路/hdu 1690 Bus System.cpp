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
const int maxn=100+10;
ll d[maxn][maxn],num[maxn];
ll L1,L2,L3,L4,C1,C2,C3,C4;
ll getLen(ll x)
{
    if(x<=L1) return C1;
    else if(x<=L2) return C2;
    else if(x<=L3) return C3;
    else if(x<=L4) return C4;
    return Inf;
}
ll ab(ll x)
{
    return x<0?-x:x;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    int n,m;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        scanf("%I64d%I64d%I64d%I64d",&L1,&L2,&L3,&L4);
        scanf("%I64d%I64d%I64d%I64d",&C1,&C2,&C3,&C4);
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i)
          scanf("%I64d",&num[i]);
        for(int i=1;i<=n;++i)
          for(int j=1;j<=n;++j)
          {
              if(i==j)
              {
                  d[i][j]=0;
                  continue;
              }
              ll tmp=ab(num[i]-num[j]);
              d[i][j]=getLen(tmp);
          }
        for(int k=1;k<=n;++k)
          for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
              d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
        printf("Case %d:\n",tcase);
        int u,v;
        while(m--)
        {
            scanf("%d%d",&u,&v);
            if(d[u][v]==Inf)
              printf("Station %d and station %d are not attainable.\n",u,v);
            else
              printf("The minimum cost between station %d and station %d is %I64d.\n",u,v,d[u][v]);
        }
    }
    return 0;
}
