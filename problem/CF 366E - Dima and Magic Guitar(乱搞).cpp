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
int a[maxn][maxn],b[maxn];
int maxa[10][4],mina[10][4],maxpt[10][4][2],minpt[10][4][2];
int dir[4][2];
void Update(int x,int i,int j)
{
    int tmp ;
    for(int k = 0;k < 4;++k)
    {
        tmp = abs(i - dir[k][0]) + abs(j - dir[k][1]);
        if(tmp > maxa[x][k])
        {
            maxa[x][k] = tmp;
            maxpt[x][k][0] = i;
            maxpt[x][k][1] = j;
        }
        if(tmp < mina[x][k])
        {
            mina[x][k] = tmp;
            minpt[x][k][0] = i;
            minpt[x][k][1] = j;
        }
    }
}
int Query(int x,int y)
{
    int res = 0;
    for(int i = 0;i < 4;++i)
    {
        res = max(res,maxa[x][i] - mina[y][i]);
        res = max(res,maxa[y][i] - mina[x][i]);
    }
    return res;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,m,k,s;
    scanf("%d%d%d%d",&n,&m,&k,&s);
    dir[0][0] = dir[0][1] = 1;
    dir[1][0] = 1; dir[1][1] = m;
    dir[2][0] = n; dir[2][1] = 1;
    dir[3][0] = n; dir[3][1] = m;
    memset(maxa,0xff,sizeof(maxa));
    memset(mina,0x3f,sizeof(mina));
    for(int i = 1;i <= n;++i)
        for(int j = 1;j <= m;++j)
        {
            scanf("%d",&a[i][j]);
            Update(a[i][j],i,j);
        }
    for(int i = 0;i < s;++i)
        scanf("%d",&b[i]);
    int ans = 0;
    for(int i = 1;i < s;++i)
        ans = max(ans,Query(b[i-1],b[i]));
    printf("%d\n",ans);
    return 0;
}
