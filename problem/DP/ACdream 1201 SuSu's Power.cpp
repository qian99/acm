#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<assert.h>
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
const int maxn = 100 + 10;
const int maxm = 50 + 10;
int dpmax[maxn][maxm][2];
int dpmin[maxn][maxm][2];
char str[maxn];
inline void Update1(int &x,int y)
{
    if(x == inf) x = y;
    else x = max(x,y);
}
inline void Update2(int & x,int y)
{
    if(x == inf) x = y;
    else x = min(x,y);
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,m,tcase = 0;
    while(~scanf("%d",&n))
    {
        scanf("%s",str + 1);
        scanf("%d",&m);
        memset(dpmax,0x3f,sizeof(dpmax));
        memset(dpmin,0x3f,sizeof(dpmin));
        dpmax[0][0][0] = 0;
        dpmin[0][0][0] = 0;
        int op;
        for(int i = 0;i < n;++i)
        {
            for(int j = 0;j <= m;++j)
            {
                for(int k = 0;k + j <= m;++k)
                {
                    int p = j & 1;
                    op = (str[i+1] - 'A')^p;
                    if(op == 0)
                    {
                        if(dpmax[i][k][0] != inf)
                            Update1(dpmax[i+1][j+k][0],dpmax[i][k][0] + 1);
                        if(dpmax[i][k][1] != inf)
                            Update1(dpmax[i+1][j+k][1],dpmax[i][k][1] - 1);
                        if(dpmin[i][k][0] != inf)
                            Update2(dpmin[i+1][j+k][0],dpmin[i][k][0] + 1);
                        if(dpmin[i][k][1] != inf)
                            Update2(dpmin[i+1][j+k][1],dpmin[i][k][1] - 1);
                    }
                    else
                    {
                        if(dpmax[i][k][0] != inf)
                            Update1(dpmax[i+1][j+k][1],dpmax[i][k][0]);
                        if(dpmax[i][k][1] != inf)
                            Update1(dpmax[i+1][j+k][0],dpmax[i][k][1]);
                        if(dpmin[i][k][0] != inf)
                            Update2(dpmin[i+1][j+k][1],dpmin[i][k][0]);
                        if(dpmin[i][k][1] != inf)
                            Update2(dpmin[i+1][j+k][0],dpmin[i][k][1]);
                    }
                }
            }
        }
        int ans = 0;
        if(dpmax[n][m][0] != inf) ans = max(abs(dpmax[n][m][0]),ans);
        if(dpmax[n][m][1] != inf) ans = max(abs(dpmax[n][m][1]),ans);
        if(dpmin[n][m][0] != inf) ans = max(abs(dpmin[n][m][0]),ans);
        if(dpmin[n][m][1] != inf) ans = max(abs(dpmin[n][m][1]),ans);
        printf("Case #%d: %d\n",++tcase,ans);
    }
    return 0;
}
