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
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 55;
const int dirx[8] = {-1,-1,-1,0,0,1,1,1};
const int diry[8] = {-1,0,1,-1,1,-1,0,1};
char mat[2][maxn][maxn];
int lTimes[maxn][maxn],n,m,F,K;
inline bool check(int p,int x,int y)
{
    return x >= 1 && x <= n && y >= 1 && y<= m && mat[p][x][y] == '1';
}
inline char getNext(char st,int cnt)
{
    if(st == '1')
    {
        if(cnt < 2) return '0';
        if(cnt > 3) return '0';
        return '1';
    }
    return (cnt == 3) + '0';
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d%d",&n,&m,&F,&K);
        memset(lTimes ,0x3f,sizeof(lTimes));
        for(int i = 1;i <= n;++i)
            scanf("%s",mat[0][i]+1);
        int T,x,y;
        for(int i = 0;i < K;++i)
        {
            scanf("%d%d%d",&T,&x,&y);
            lTimes[x][y] = T;
        }
        for(int now = 1;now <= F;++now)
        {
            int p = now & 1;
            for(int i = 1;i <= n;++i)
                for(int j = 1;j <= m;++j)
                {
                    if(mat[p^1][i][j] == 'X')
                        mat[p][i][j] = 'X';
                    else
                    {
                        int cnt = 0;
                        for(int k = 0;k < 8;++k)
                        {
                            x = i + dirx[k];
                            y = j + diry[k];
                            if(check(p^1,x,y))
                                cnt++;
                        }
                        mat[p][i][j] = getNext(mat[p^1][i][j],cnt);
                        if(now >= lTimes[i][j])
                            mat[p][i][j] = 'X';
                    }
                }
        }
        for(int i = 1;i <= n;++i)
        {
            for(int j = 1;j <= m;++j)
                putchar(mat[F&1][i][j]);
            printf("\n");
        }
    }
    return 0;
}
