#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<set>
#include<cmath>
#include<vector>
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 400 + 10;
int g[maxn][maxn],n,m;
char ver[maxn],hor[maxn];
inline bool check(int x,int y)
{
    return x >= 0 && x < n && y >= 0 && y < m;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    scanf("%d%d",&n,&m);
    scanf("%s",hor);
    scanf("%s",ver);
    memset(g,0x3f,sizeof(g));
    for(int i = 0;i < n*m;++i) g[i][i] = 0;
    int dx,dy;
    for(int i = 0;i < n;++i)
    {
        for(int j = 0;j < m;++j)
        {
            if(hor[i] == '<')
            {
                dx = i;
                dy = j - 1;
                if(check(dx,dy))
                    g[i*m + j][dx*m + dy] = 1;
            }
            else
            {
                dx = i;
                dy = j + 1;
                if(check(dx,dy))
                    g[i*m + j][dx*m + dy] = 1;
            }
            if(ver[j] == '^')
            {
                dx = i - 1;
                dy = j;
                if(check(dx,dy))
                    g[i*m + j][dx*m + dy] = 1;
            }
            else
            {
                dx = i + 1;
                dy = j;
                if(check(dx,dy))
                    g[i*m + j][dx*m + dy] = 1;
            }
        }
    }
    int N = n*m;
    for(int k = 0;k < N;++k)
        for(int i = 0;i < N;++i)
            for(int j = 0;j < N;++j)
                g[i][j] = min(g[i][j],g[i][k] + g[k][j]);
    bool flag = true;
    for(int i = 0;i < N && flag;++i)
        for(int j = 0;j < N && flag;++j)
            if(g[i][j] == inf) flag = false;
    if(flag) puts("YES");
    else puts("NO");
    return 0;
}