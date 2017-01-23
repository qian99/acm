#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
const int maxn=1000+10;
int up[maxn][maxn],zz[maxn];
char ac[maxn][maxn];
int m,n;
bool cmp(int a,int b)
{
    return a>b;
}
int sovle()
{
    int ans=0;
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            up[i][j]=(ac[i][j]=='1')?up[i-1][j]+1:0;
            zz[j]=up[i][j];
        }
        sort(zz+1,zz+n+1,cmp);
        for(int j=1;j<=n;++j)
        {
            if(zz[j]==0) break;
            ans=max(ans,zz[j]*j);
        }
    }
    return ans;
}
int main()
{
    while(~scanf("%d%d",&m,&n))
    {
        for(int i=0;i<=n;++i)
          up[0][i]=0;
        memset(zz,0,sizeof(zz));
        for(int i=1;i<=m;++i)
        {
            scanf("%s",ac[i]+1);
        }
        int ans=sovle();
        printf("%d\n",ans);
    }
    return 0;
}
