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
const int maxn = 1000+10;
int mat[maxn][maxn],n,k,d;
void solve(int days,int L,int R)
{
    if(days > d) return ;
    int cnt = (R-L+1)/k + ((R-L+1)%k != 0);
    int block = (R-L+1)/cnt + ((R-L+1)%cnt != 0);
    int now = L,x;
    for(int i = 1;i <= block;++i)
    {
        x = now;
        for(int j = 1;j <= cnt;++j)
        {
            mat[days][now++] = i;
            if(now > n) break;
        }
        solve(days + 1,x,now - 1);
    }
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    scanf("%d%d%d",&n,&k,&d);
    int tot = 1;
    for(int i = 1;i <= d;++i)
    {
        tot *= k;
        if(tot >= n) break;
        if(i == d)
        {
            printf("-1\n");
            return 0;
        }
    }
    if(k >= n)
    {
        for(int i = 1;i <= d;++i)
        {
            for(int j = 1;j <= n; ++j)
                printf("%d ",j);
            printf("\n");
        }
        return 0;
    }
    solve(1,1,n);
    for(int i = 1;i <= d;++i)
    {
        for(int j = 1;j <= n;++j)
            printf("%d ",mat[i][j]);
        printf("\n");
    }
    return 0;
}
