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
const int maxn = 2000 + 10;
int mat[maxn][maxn];
ll sum1[maxn][maxn],sum2[maxn][maxn],sum3[maxn][maxn],sum4[maxn][maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n;
    scanf("%d",&n);
    for(int i = 1;i <= n;++i)
    {
        for(int j = 1;j <= n;++j)
            scanf("%d",&mat[i][j]);
    }
    for(int i = 1;i <= n;++i)
        for(int j = 1;j <= n;++j)
            sum1[i][j] = sum1[i-1][j-1] + mat[i][j];
    for(int i = n;i >= 1;--i)
        for(int j = n; j >= 1;--j)
            sum2[i][j] = sum2[i+1][j+1] + mat[i][j];
    for(int i = 1;i <= n;++i)
        for(int j = n;j >= 1;--j)
            sum3[i][j] = sum3[i-1][j+1] + mat[i][j];
    for(int i = n; i >= 1; --i)
        for(int j = 1;j <= n;++j)
            sum4[i][j] = sum4[i+1][j-1] + mat[i][j];
    ll maxsum1 = -1,maxsum2 = -1,tmp;
    int px1,px2,py1,py2;
    for(int i = 1;i <= n;++i)
    {
        for(int j = 1;j <= n;++j)
        {
            tmp = sum1[i][j] + sum2[i+1][j+1] + sum3[i-1][j+1] + sum4[i+1][j-1];
            if((i+j)&1)
            {
                if(tmp > maxsum1)
                {
                    maxsum1 = tmp;
                    px1 = i;
                    py1 = j;
                }
            }
            else
            {
                if(tmp > maxsum2)
                {
                    maxsum2 = tmp;
                    px2 = i;
                    py2 = j;
                }
            }
        }
    }
    printf("%I64d\n",maxsum1 + maxsum2);
    printf("%d %d %d %d\n",px1,py1,px2,py2);
    return 0;
}