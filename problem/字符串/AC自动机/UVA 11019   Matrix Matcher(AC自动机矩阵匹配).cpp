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
const int maxn=10000+10;
const int maxm=1000+10;
int ch[maxn][26],next[maxn],lastv[maxn],val[maxn],size=0;
int match[maxm][maxm],n,m,x,y;
char T[maxm][maxm],P[110][110];
vector<int>vt[maxn];
void Init()
{
    vt[0].clear();
    memset(ch[0],0,sizeof(ch[0]));
    memset(next,0,sizeof(next));
    lastv[0]=val[0]=size=0;
    memset(match,0,sizeof(match));
}
void Insert(const char *s,int v)
{
    int u=0;
    for(int i=0;i<y;++i)
    {
        int c=s[i]-'a';
        if(!ch[u][c])
        {
            ch[u][c]=++size;
            memset(ch[size],0,sizeof(ch[size]));
            lastv[size]=val[size]=0;
            vt[size].clear();
        }
        u=ch[u][c];
    }
    val[u]++;
    vt[u].push_back(v);
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
int solve()
{
    int u,c,v;
    for(int i=0;i<n;++i)
    {
        u=0;
        for(int j=0;j<m;++j)
        {
            c=T[i][j]-'a';
            u=ch[u][c];
            if(val[u]||lastv[u])
            {
                v=val[u]?u:lastv[u];
                while(v)
                {
                    for(int k=0;k<val[v];++k)
                        if(i-vt[v][k]+1>=0&&j-y+1>=0)
                        match[i-vt[v][k]+1][j-y+1]++;
                    v=lastv[v];
                }
            }
        }
    }
    int ans=0;
    for(int i=0;i<n;++i)
        for(int j=0;j<m;++j)
            if(match[i][j]==x) ans++;
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        Init();
        scanf("%d%d",&n,&m);
        for(int i=0;i<n;++i)
            scanf("%s",T[i]);
        scanf("%d%d",&x,&y);
        for(int i=1;i<=x;++i)
        {
            scanf("%s",P[i]);
            Insert(P[i],i);
        }
        build();
        printf("%d\n",solve());
    }
    return 0;
}
