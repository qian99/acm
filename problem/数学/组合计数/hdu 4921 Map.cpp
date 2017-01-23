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
const int maxn=10000+10;
int son[maxn],degree[maxn],val[maxn];
int path[10][maxn],len[10],cnt[1<<10];
void Init()
{
    memset(cnt,0,sizeof(cnt));
    for(int i = 0;i < (1<<10) ;++i)
    {
        int x = i;
        while(x)
        {
            cnt[i]++;
            x &= (x-1);
        }
    }
}
void dfs(int u,int N)
{
    path[N][len[N]++] = u;
    if(son[u] != -1) dfs(son[u],N);
}
double solve(int n)
{
    int m=0;
    for(int i = 0;i < n;++i)
        m=max(m,len[i]);
    double ans=0;
    for(int i = 0;i < m;++i)
    {
        double x=0;
        for(int j = 0;j < n ;++j)
            if(len[j] > i) x += 1;
        for(int j = 0;j < (1<<n);++j)
        {
            double tmp = 1,sum = 0;
            for(int k = 0;k < n;++k)
            {
                if(j & (1<<k))
                {
                    if(len[k] < i+1)
                    {
                        tmp = 0;
                        break;
                    }
                    sum += val[path[k][i]];
                    tmp *= (len[k] - i);
                }
                else
                {
                    tmp *= min(i + 1,len[k] + 1);
                }
            }
            if(cnt[j] > 1) ans += cnt[j]*tmp*sum/x;
            ans += sum*tmp;
        }
    }
    double d = 1;
    for(int i = 0;i < n;++i)
        d *= (len[i] + 1);
    return ans/(d-1);
}
int main()
{
//    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    Init();
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n,m,u,v;
        scanf("%d%d",&n,&m);
        memset(degree,0,sizeof(degree));
        memset(son,0xff,sizeof(son));
        for(int i = 0;i < n;++i)
            scanf("%d",&val[i]);
        for(int i = 0;i < m;++i)
        {
            scanf("%d%d",&u,&v);
            son[u]=v;
            degree[v]++;
        }
        int N=0;
        for(int i = 0;i < n;++i)
            if(degree[i] == 0)
            {
                len[N]=0;
                dfs(i,N);
                N++;
            }
        double ans = solve(N);
        printf("%.3lf\n",ans);
    }
    return 0;
}
