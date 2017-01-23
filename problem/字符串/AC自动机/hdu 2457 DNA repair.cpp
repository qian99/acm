#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=1000+10;
int ch[maxn][4],next[maxn],flag[maxn],size;
void Init()
{
    memset(ch[0],0,sizeof(ch[0]));
    memset(next,0,sizeof(next));
    size=0;flag[0]=0;
}
int indx(char c)
{
    if(c=='A') return 0;
    if(c=='T') return 1;
    if(c=='C') return 2;
    return 3;
}
void Insert(const char *s)
{
    int u=0,n=strlen(s);
    for(int i=0;i<n;++i)
    {
        int c=indx(s[i]);
        if(!ch[u][c])
        {
            ch[u][c]=++size;
            memset(ch[size],0,sizeof(ch[size]));
            flag[size]=0;
        }
        u=ch[u][c];
    }
    flag[u]=1;
}
void build()
{
    queue<int>q;
    for(int c=0;c<4;++c)
        if(ch[0][c]) q.push(ch[0][c]);
    int r,u,v;
    while(!q.empty())
    {
        r=q.front();q.pop();
        for(int c=0;c<4;++c)
        {
            u=ch[r][c];
            if(!u) {ch[r][c]=ch[next[r]][c];continue;}
            q.push(u);
            v=next[r];
            while(v&&!ch[v][c]) v=next[v];
            next[u]=ch[v][c];
            flag[u]|=flag[next[u]];
        }
    }
}
char str[maxn];
int dp[maxn][maxn];
int solve()
{
    int n=strlen(str);
    memset(dp,0xff,sizeof(dp));
    dp[0][0]=0;
    int u;
    for(int i=0;i<n;++i)
        for(int j=0;j<=size;++j)
        {
            if(flag[j]||dp[i][j]==-1) continue;
            for(int c=0;c<4;++c)
            {
                u=ch[j][c];
                if(flag[u]) continue;
                if(dp[i+1][u]==-1) dp[i+1][u]=dp[i][j]+(c!=indx(str[i]));
                else dp[i+1][u]=min(dp[i+1][u],dp[i][j]+(c!=indx(str[i])));
            }
        }
    int ans=inf;
    for(int i=0;i<=size;++i)
        if(dp[n][i]!=-1) ans=min(ans,dp[n][i]);
    if(ans==inf) return -1;
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int tcase=0,n;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        Init();
        tcase++;
        for(int i=0;i<n;++i)
        {
            scanf("%s",str);
            Insert(str);
        }
        build();
        scanf("%s",str);
        printf("Case %d: %d\n",tcase,solve());
    }
    return 0;
}
