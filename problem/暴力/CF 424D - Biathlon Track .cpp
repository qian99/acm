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
const int maxn = 300+10;
int t1[maxn][maxn],t2[maxn][maxn],t3[maxn][maxn],t4[maxn][maxn];
int a[maxn][maxn],tp,tu,td,t,ans;
int pt[4],n,m;
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    scanf("%d%d%d",&n,&m,&t);
    scanf("%d%d%d",&tp,&tu,&td);
    for(int i = 1;i <= n;++i)
        for(int j = 1;j <= m;++j)
            scanf("%d",&a[i][j]);
    for(int i = 1;i <= n;++i)
    {
        for(int j = 2;j <= m;++j)
        {
            if(a[i][j] > a[i][j-1])
            {
                t1[i][j] = tu + t1[i][j-1];
                t3[i][j] = td + t3[i][j-1];
            }
            else if(a[i][j] == a[i][j-1])
            {
                t1[i][j] = tp + t1[i][j-1];
                t3[i][j] = tp + t3[i][j-1];
            }
            else
            {
                t1[i][j] = td + t1[i][j-1];
                t3[i][j] = tu + t3[i][j-1];
            }
        }
    }
    for(int i = 2;i <= n;++i)
    {
        for(int j = 1;j <= m;++j)
        {
            if(a[i][j] > a[i-1][j])
            {
                t2[i][j] = tu + t2[i-1][j];
                t4[i][j] = td + t4[i-1][j];
            }
            else if(a[i][j] == a[i-1][j])
            {
                t2[i][j] = tp + t2[i-1][j];
                t4[i][j] = tp + t4[i-1][j];
            }
            else
            {
                t2[i][j] = td + t2[i-1][j];
                t4[i][j] = tu + t4[i-1][j];
            }
        }
    }
    ans = inf;
    for(int x1 = 1;x1 <= n && ans;++x1)
        for(int x2 = x1 + 2;x2 <= n && ans;++x2)
            for(int y1 = 1;y1 <= m && ans;++y1)
                for(int y2 = y1 + 2;y2 <= m && ans;++y2)
                {
                    int val = t1[x1][y2] - t1[x1][y1]+
                              t2[x2][y2] - t2[x1][y2]+
                              t3[x2][y2] - t3[x2][y1]+
                              t4[x2][y1] - t4[x1][y1];
                    if(abs(t-val) < ans)
                    {
                        ans = abs(t-val);
                        pt[0] = x1;
                        pt[1] = y1;
                        pt[2] = x2;
                        pt[3] = y2;
                    }
                }
    printf("%d %d %d %d\n",pt[0],pt[1],pt[2],pt[3]);
    return 0;
}
