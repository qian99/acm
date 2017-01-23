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
const int maxn=100+10;
const int mod=20090717;
int ch[maxn][26],next[maxn],lastv[maxn],val[maxn],size;
int n,m,k;
void Init()
{
    memset(ch[0],0,sizeof(ch[0]));
    memset(next,0,sizeof(next));
    memset(lastv,0,sizeof(lastv));
    size=0;val[0]=0;
}
void Insert(const char *s,int v)
{
    int u=0,len=strlen(s);
    for(int i=0;i<len;++i)
    {
        int c=s[i]-'a';
        if(!ch[u][c])
        {
            ch[u][c]=++size;
            memset(ch[size],0,sizeof(ch[size]));
            val[size]=0;
        }
        u=ch[u][c];
    }
    val[u]=v;
}
void build()
{
    queue<int>q;
    for(int c=0;c<26;++c)
        if(ch[0][c]) q.push(ch[0][c]);
    int r,u,v;
    while(!q.empty())
    {
        r=q.front();q.pop();
        for(int c=0;c<26;++c)
        {
            u=ch[r][c];
            if(!u) {ch[r][c]=ch[next[r]][c];continue;}
            q.push(u);
            v=next[r];
            while(v&&!ch[v][c]) v=next[v];
            next[u]=ch[v][c];
            lastv[u]=val[next[u]]?next[u]:lastv[next[u]];
        }
    }
}
int p[1<<10],dp[30][maxn][1<<10],num[maxn];
int solve()
{
    int total=1<<m;
    int u,x;
    memset(p,0,sizeof(p));
    for(int i=0;i<total;++i)
    {
        x=i;
        while(x)
        {
            p[i]++;
            x&=(x-1);
        }
    }
    memset(num,0,sizeof(num));
    for(int j=0;j<=size;++j)
        if(val[j]||lastv[j])
        {
            u=val[j]?j:lastv[j];
            x=0;
            while(u)
            {
                x|=(1<<(val[u]-1));
                u=lastv[u];
            }
            num[j]=x;
        }
    for(int i=0;i<=n;++i)
        for(int j=0;j<=size;++j)
            for(int t=0;t<total;++t)
                dp[i][j][t]=0;
    dp[0][0][0]=1;
    for(int i=0;i<n;++i)
        for(int j=0;j<=size;++j)
            for(int t=0;t<total;++t)
            {
                if(!dp[i][j][t]) continue;
                for(int c=0;c<26;++c)
                {
                    u=ch[j][c];
                    dp[i+1][u][t|num[u]]=(dp[i+1][u][t|num[u]]+dp[i][j][t])%mod;
                }
            }
    int ans=0;
    for(int i=0;i<=size;++i)
        for(int j=0;j<total;++j)
            if(p[j]>=k) ans=(ans+dp[n][i][j])%mod;
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    char str[20];
    while(~scanf("%d%d%d",&n,&m,&k))
    {
        if(n==0&&m==0&&k==0) break;
        Init();
        for(int i=1;i<=m;++i)
        {
            scanf("%s",str);
            Insert(str,i);
        }
        build();
        int ans=solve();
        printf("%d\n",ans);
    }
    return 0;
}
