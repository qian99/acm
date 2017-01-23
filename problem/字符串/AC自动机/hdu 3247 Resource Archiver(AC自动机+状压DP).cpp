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
const int maxn=100000+10;
int ch[maxn][2],next[maxn],flag[maxn],sourcess[maxn],size;
void Insert(const char *s,int type)
{
    int u=0,n=strlen(s);
    for(int i=0;i<n;++i)
    {
        int c=s[i]-'0';
        if(!ch[u][c])
        {
            ch[u][c]=++size;
            memset(ch[size],0,sizeof(ch[size]));
            flag[size]=sourcess[size]=0;
        }
        u=ch[u][c];
    }
    if(type>=0) sourcess[u]=(1<<type);
    else flag[u]=1;
}
void build()
{
    queue<int>q;
    for(int c=0;c<2;++c)
        if(ch[0][c]) q.push(ch[0][c]);
    int r,u,v;
    while(!q.empty())
    {
        r=q.front();q.pop();
        for(int c=0;c<2;++c)
        {
            u=ch[r][c];
            if(!u) {ch[r][c]=ch[next[r]][c];continue;}
            q.push(u);
            v=next[r];
            if(v&&!ch[v][c]) v=next[v];
            next[u]=ch[v][c];
            sourcess[u]|=sourcess[next[u]];
            flag[u]|=flag[next[u]];
        }
    }
}
int dp[1<<10][20],dis[20][20],cnt,n,m;
int d[maxn],pos[20];
void Init()
{
    memset(ch[0],0,sizeof(ch[0]));
    memset(next,0,sizeof(next));
    flag[0]=sourcess[0]=size=0;
    cnt=1;pos[0]=0;
}
void bfs(int s)
{
    memset(d,0xff,sizeof(d));
    d[pos[s]]=0;
    queue<int>q;
    q.push(pos[s]);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int c=0;c<2;++c)
        {
            int v=ch[u][c];
            if(d[v]<0&&!flag[v])
            {
                d[v]=d[u]+1;
                q.push(v);
            }
        }
    }
    for(int i=0;i<cnt;++i)
        dis[s][i]=d[pos[i]];
}
int solve()
{
    memset(dp,0xff,sizeof(dp));
    dp[0][0]=0;
    int total=1<<n;
    for(int i=0;i<total;++i)
    {
        for(int j=0;j<cnt;++j)
        {
            if(dp[i][j]<0) continue;
            for(int k=0;k<cnt;++k)
            {
                if(dis[j][k]<0) continue;
                if(dp[i|sourcess[pos[k]]][k]==-1)
                    dp[i|sourcess[pos[k]]][k]=dp[i][j]+dis[j][k];
                else
                    dp[i|sourcess[pos[k]]][k]=min(dp[i|sourcess[pos[k]]][k],dp[i][j]+dis[j][k]);
            }
        }
    }
    int ans=inf;
    for(int i=0;i<cnt;++i)
        if(dp[total-1][i]!=-1) ans=min(ans,dp[total-1][i]);
    return ans;
}
char str[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&n,&m))
    {
        if(n==0&&m==0) break;
        Init();
        for(int i=0;i<n;++i)
        {
            scanf("%s",str);
            Insert(str,i);
        }
        for(int i=0;i<m;++i)
        {
            scanf("%s",str);
            Insert(str,-1);
        }
        build();
        for(int i=1;i<=size;++i)
            if(sourcess[i]) pos[cnt++]=i;
        for(int i=0;i<cnt;++i)
            bfs(i);
        printf("%d\n",solve());
    }
    return 0;
}
