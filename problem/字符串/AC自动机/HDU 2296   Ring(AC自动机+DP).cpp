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
const int maxn=1500;
int ch[maxn][26],next[maxn],lastv[maxn],val[maxn],size;
void Init()
{
    memset(ch[0],0,sizeof(ch[0]));
    memset(next,0,sizeof(next));
    memset(lastv,0,sizeof(lastv));
    size=val[0]=0;
}
void Insert(const char *s,int v)
{
    int u=0,n=strlen(s);
    for(int i=0;i<n;++i)
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
int dp[55][maxn],h[maxn];
string pa[55][maxn];
int w[maxn],maxval,n,m;
char str[110];
void solve()
{
    memset(w,0,sizeof(w));
    for(int i=0;i<=size;++i)
    {
        if(val[i]||lastv[i])
        {
            int u=val[i]?i:lastv[i];
            while(u)
            {
                w[i]+=h[val[u]];
                u=lastv[u];
            }
        }
    }
    for(int i=0;i<=n;++i)
        for(int j=0;j<=size;++j)
            pa[i][j].clear();
    memset(dp,0xff,sizeof(dp));
    maxval=0;
    int pos=0,st=0;
    dp[0][0]=0;
    for(int i=0;i<n;++i)
        for(int j=0;j<=size;++j)
        {
            if(dp[i][j]==-1) continue;
            for(int c=0;c<26;++c)
            {
                int u=ch[j][c];
                if(dp[i][j]+w[u]>dp[i+1][u])
                {
                    dp[i+1][u]=dp[i][j]+w[u];
                    pa[i+1][u]=pa[i][j]+(char)(c+'a');
                }
                else if(dp[i][j]+w[u]==dp[i+1][u]&&(pa[i][j]+(char)(c+'a'))<pa[i+1][u])
                    pa[i+1][u]=pa[i][j]+(char)(c+'a');
                if(dp[i+1][u]>maxval)
                {
                    maxval=dp[i+1][u];
                    //cout<<pa[i+1][u]<<endl;
                    pos=i+1,st=u;
                }
                else if(dp[i+1][u]==maxval)
                {
                    int la=pa[i+1][u].length();
                    int lb=pa[pos][st].length();
                    if(la<lb)
                        pos=i+1,st=u;
                    else if(la==lb&&pa[i+1][u]<pa[pos][st])
                        pos=i+1,st=u;
                }
            }
        }
    cout<<pa[pos][st]<<endl;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        Init();
        for(int i=1;i<=m;++i)
        {
            scanf("%s",str);
            Insert(str,i);
        }
        for(int i=1;i<=m;++i)
            scanf("%d",&h[i]);
        build();
        solve();
    }
    return 0;
}
