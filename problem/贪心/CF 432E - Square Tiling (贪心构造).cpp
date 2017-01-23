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
char mat[maxn][maxn];
int n,m;
void solve()
{
    memset(mat,0,sizeof(mat));
    char c,ct;
    int x,y;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
        {
            if(mat[i][j]!=0) continue;
            for(c='A';c<='Z';++c)
                if(mat[i-1][j]!=c&&mat[i][j-1]!=c&&mat[i][j+1]!=c) break;
            mat[i][j]=c;
            for(y=j+1;y<=m&&i+(y-j+1)-1<=n&&mat[i][y]==0;++y)
            {
                for(ct='A';ct<='Z';++ct)
                    if(mat[i-1][y]!=ct) break;
                if(c!=ct)
                {
                    y--;
                    break;
                }
                else mat[i][y]=c;
            }
            if(y>m||mat[i][y]!=c) y--;
            int len=y-j+1;
            for(x=i;x<i+len;++x)
                for(y=j;y<j+len;++y)
                    mat[x][y]=c;
        }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d%d",&n,&m);
    solve();
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
            putchar(mat[i][j]);
        printf("\n");
    }
    return 0;
}
