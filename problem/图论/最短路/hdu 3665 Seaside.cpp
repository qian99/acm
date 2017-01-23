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
int dis[15][15];
int havesea[15];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        for(int i=0;i<n;++i)
          for(int j=0;j<n;++j)
            dis[i][j]=(i==j)?0:inf;
        int m,p,a,b;
        for(int i=0;i<n;++i)
        {
            scanf("%d%d",&m,&p);
            havesea[i]=p;
            for(int j=0;j<m;++j)
            {
                scanf("%d%d",&a,&b);
                dis[i][a]=min(dis[i][a],b);
                dis[a][i]=dis[i][a];
            }
        }
        for(int k=0;k<n;++k)
          for(int i=0;i<n;++i)
            for(int j=0;j<n;++j)
              if(dis[i][k]+dis[k][j]<dis[i][j])
                dis[i][j]=dis[i][k]+dis[k][j];
        int ans=inf;
        for(int i=0;i<n;++i)
        {
            if(havesea[i])
              ans=min(ans,dis[0][i]);
        }
        printf("%d\n",ans);

    }
    return 0;
}
