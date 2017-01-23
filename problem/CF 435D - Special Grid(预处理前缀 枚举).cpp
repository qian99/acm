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
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=400+10;
int ups[maxn][maxn],lf[maxn][maxn];
int zx[maxn][maxn],yx[maxn][maxn],n,m;
char a[maxn][maxn];
void Init()
{
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
        {
            ups[i][j]=ups[i-1][j]+a[i][j]-'0';
            lf[i][j]=lf[i][j-1]+a[i][j]-'0';
            zx[i][j]=zx[i-1][j-1]+a[i][j]-'0';
        }
        for(int j=m;j>=1;--j)
            yx[i][j]=yx[i-1][j+1]+a[i][j]-'0';
    }

}
inline bool check(int x,int y)
{
    return x>=1&&x<=n&&y>=1&&y<=m;
}
int solve()
{
    int sum=0,x,x2,y,y2;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
        {
            for(int k=1;k<=min(n,m);++k)
            {
                x=i-k;y=j-k;
                if(check(x,y))
                if(!(lf[i][j]-lf[i][y-1]||ups[i][j]-ups[x-1][j]||yx[i][y]-yx[x-1][j+1]))
                    sum++;
                x=i-k;y=j+k;
                if(check(x,y))
                if(!(lf[i][y]-lf[i][j-1]||ups[i][j]-ups[x-1][j]||zx[i][y]-zx[x-1][j-1]))
                    sum++;
                x=i+k;y=j+k;
                if(check(x,y))
                if(!(lf[i][y]-lf[i][j-1]||ups[x][j]-ups[i-1][j]||yx[x][j]-yx[i-1][y+1]))
                    sum++;
                x=i+k;y=j-k;
                if(check(x,y))
                if(!(lf[i][j]-lf[i][y-1]||ups[x][j]-ups[i-1][j]||zx[x][j]-zx[i-1][y-1]))
                    sum++;
                x=i-k;y=j-k;y2=j+k;
                if(check(x,y)&&check(x,y2))
                if(!(lf[x][y2]-lf[x][y-1]||zx[i][j]-zx[x-1][y-1]||yx[i][j]-yx[x-1][y2+1]))
                    sum++;
                x=i-k;x2=i+k;y=j+k;
                if(check(x,y)&&check(x2,y))
                if(!(ups[x2][y]-ups[x-1][y]||yx[i][j]-yx[x-1][y+1]||zx[x2][y]-zx[i-1][j-1]))
                    sum++;
                x=i+k;y=j-k;y2=j+k;
                if(check(x,y)&&check(x,y2))
                if(!(lf[x][y2]-lf[x][y-1]||yx[x][y]-yx[i-1][j+1]||zx[x][y2]-zx[i-1][j-1]))
                    sum++;
                x=i-k;x2=i+k;y=j-k;
                if(check(x,y)&&check(x2,y))
                if(!(ups[x2][y]-ups[x-1][y]||zx[i][j]-zx[x-1][y-1]||yx[x2][y]-yx[i-1][j+1]))
                    sum++;
            }
        }
    return sum;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
        scanf("%s",(a[i]+1));
    Init();
    int ans=solve();
    printf("%d\n",ans);
    return 0;
}
