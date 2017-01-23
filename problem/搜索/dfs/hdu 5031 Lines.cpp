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
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 55;
int a[maxn][maxn],n,m,ans,sum;
int gcd(int a,int b) { return b == 0 ? a : gcd(b,a%b);}
int gval[maxn<<2][maxn<<2];
map<double,bool>mp;
inline void getnext(int &x ,int & y)
{
    y++;
    if(y == m)
    {
        x++;
        y = 0;
    }
}
void dfs(int x,int y,int now)
{
    if(now >= ans) return ;
    if(sum == 0)
    {
        ans = now;
        return ;
    }
    int i,j,flag = 1;
    for(i = x;i < n && flag;i += flag)
        for(j = (i == x) ? y : 0;j < m && flag;j += flag)
            if(a[i][j]) {flag = 0;break;}
    x = i;y = j;
    if(flag) return ;
    int dx,dy,cnt = 0;
    if(y == 0)
    {
        for(j = 0;j < m;++j) if(!a[x][j]) break;
        if(j == m)
        {
            for(j = 0;j < m;++j) a[x][j]--;
            sum -= m;
            dfs(x,y,now + 1);
            sum += m;
            for(j = 0;j < m;++j) a[x][j]++;
        }
    }
    if(x == 0)
    {
        for(i = 0;i < n;++i) if(!a[i][y]) break;
        if(i == n)
        {
            for(i = 0;i < n;++i) a[i][y]--;
            sum -= n;
            dfs(x,y,now + 1);
            sum += n;
            for(i = 0;i < n;++i) a[i][y]++;
        }
    }
    mp.clear();
    for(i = 1;i < n;++i)
        for(j = -m;j < m;++j)
        {
            if(i == 0 || j == 0) continue;
            if(i + x >= n || j + y <0 || j +y >= m || !a[i + x][j + y]) continue;
            if(gval[i + maxn][j + maxn] != 1 && gval[i + maxn][j + maxn] != -1) continue;
            if(!mp[(double)j/i])
                mp[(double)j/i] = 1;
            else break;
            dx = x - i;dy = y - j;
            if(dx >= 0 && dx < n && dy >= 0 && dy < m) continue;
            dx = x;dy = y;
            cnt = 0;
            while(dx >= 0 && dx < n && dy >= 0 && dy < m && a[dx][dy])
            {
                cnt++;
                dx += i;
                dy += j;
            }
            if(dx >= 0 && dx < n && dy >= 0 && dy < m) continue;
            if(cnt < 3) continue;
            dx = x;dy = y;
            while(dx >= 0 && dx < n && dy >= 0 && dy < m)
            {
                a[dx][dy]--;
                dx += i;
                dy += j;
            }
            sum -= cnt;
            dfs(x,y,now + 1);
            sum += cnt;
            dx = x; dy = y;
            while(dx >= 0 && dx < n && dy >= 0 && dy < m)
            {
                a[dx][dy]++;
                dx += i;
                dy += j;
            }
        }
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    for(int i = 0;i <= maxn*2;++i)
        for(int j = 0;j <= maxn*2;++j)
            gval[i][j] = gcd(i - maxn,j - maxn);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        n++;m++;
        sum = 0;
        for(int i = 0;i < n;++i)
            for(int j = 0;j < m;++j)
            {
                scanf("%d",&a[i][j]);
                sum += a[i][j];
            }
        ans = min(14,sum/3);
        dfs(0,0,0);
        printf("%d\n",ans);
    }
    return 0;
}
