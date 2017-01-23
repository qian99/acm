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
const int maxn=55;
const int N=1<<8;
int pos[10],tt[10][2],chicket[maxn];
int d[maxn][N][N],a[maxn][maxn];
int n,m,K;
void Init()
{
    memset(chicket,0,sizeof(chicket));
    memset(a,0x3f,sizeof(a));
    memset(d,0x3f,sizeof(d));
    memset(pos,0,sizeof(pos));
    memset(tt,0,sizeof(tt));
    for(int i=0;i<maxn;++i) a[i][i]=0;
}
int solve()
{
    for(int k=1;k<=n;++k)
      for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
          a[i][j]=min(a[i][j],a[i][k]+a[k][j]);
    int total=1<<K;
    int ans=inf;
    d[1][0][0]=0;
    for(int i=0;i<total;++i)
     for(int j=0;j<total;++j)
      for(int k=1;k<=n;++k)
      {
          int now=d[k][i][j];
          if(now==inf) continue;
          if(j==total-1) ans=min(ans,now+a[k][1]);
          for(int z=0;z<K;++z)
          {
              if((j&(1<<z))==0)
              {
                  int &nxt=d[pos[z]][i|chicket[pos[z]]][j|(1<<z)];
                  int tmp=i&(1<<z);
                  tmp=(tmp!=0)?tt[z][1]:tt[z][0];
                  nxt=min(nxt,now+a[k][pos[z]]+tmp);
              }
          }
          for(int z=1;z<=n;++z)
          {
              int &nxt=d[z][i|chicket[z]][j];
              nxt=min(nxt,now+a[k][z]);
          }
      }
    return ans;
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
        Init();
        scanf("%d%d%d",&n,&m,&K);
        int u,v,w;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            a[u][v]=a[v][u]=w;
        }
        for(int i=0;i<K;++i)
        {
            scanf("%d%d%d",&pos[i],&tt[i][0],&tt[i][1]);
            int z,x;
            scanf("%d",&z);
            for(int j=0;j<z;++j)
            {
                scanf("%d",&x);
                chicket[x]|=(1<<i);
            }
        }
        int ans=solve();
        printf("Case #%d: %d\n",tcase,ans);
    }
    return 0;
}
