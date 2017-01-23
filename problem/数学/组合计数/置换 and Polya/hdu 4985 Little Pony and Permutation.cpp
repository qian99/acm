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
const int maxn = 100000 + 10;
int a[maxn],b[maxn];
bool vis[maxn];
vector<int>g[maxn];
bool cmp(int x,int y)
{
    return g[x][0] < g[y][0];
}
void ptper(int x)
{
    putchar('(');
    int size = g[x].size();
    for(int i = 0;i < size;++i)
    {
        if(i) printf(" ");
        printf("%d",g[x][i]);
    }
    putchar(')');
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        for(int i = 1;i <= n;++i)
            scanf("%d",&a[i]);
        memset(vis,0,sizeof(vis));
        for(int i = 0;i <= n;++i) g[i].clear();
        int cnt = 0;
        for(int i = 1;i <= n;++i)
        {
            if(vis[i]) continue;
            int u = i;
            while(!vis[u])
            {
                g[cnt].push_back(u);
                vis[u] = true;
                u = a[u];
            }
            cnt++;
        }
        for(int i = 0;i < cnt;++i) b[i] = i;
        sort(b,b+cnt,cmp);
        for(int i = 0;i < cnt;++i)
            ptper(b[i]);
        puts("");
    }
    return 0;
}