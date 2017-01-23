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
const int maxn=2000+10;
double p[110],dp[maxn][110];
bool vis[maxn][110];
int ch[maxn][63],val[maxn],next[maxn],size,n;
int idx(char c)
{
    if(c>='0'&&c<='9') return c-'0';
    if(c>='a'&&c<='z') return c-'a'+10;
    return c-'A'+10+26;
}
void Init()
{
    memset(vis,0,sizeof(vis));
    memset(ch[0],0,sizeof(ch[0]));
    memset(next,0,sizeof(next));
    memset(val,0,sizeof(val));
    memset(p,0,sizeof(p));
    size=0;
}
void insert(const char *s)
{
    int u=0,len=strlen(s);
    for(int i=0;i<len;++i)
    {
        int c=idx(s[i]);
        if(!ch[u][c])
        {
            ch[u][c]=++size;
            memset(ch[size],0,sizeof(ch[size]));
            val[size]=0;
        }
        u=ch[u][c];
    }
    val[u]=1;
}
void build()
{
    queue<int>q;
    for(int i=0;i<62;++i)
    {
        if(ch[0][i]) q.push(ch[0][i]);
    }
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int i=0;i<62;++i)
        {
            int v=ch[u][i];
            if(!v) {ch[u][i]=ch[next[u]][i];continue;}
            q.push(v);
            int j=next[u];
            while(j&&!ch[j][i]) j=next[j];
            next[v]=ch[j][i];
            val[v]|=val[next[v]];
        }
    }
}
double f(int u,int L)
{
    if(L==0) return 1.0;
    if(vis[u][L]) return dp[u][L];
    vis[u][L]=true;
    dp[u][L]=0;
    for(int i=0;i<62;++i)
    {
        if(!val[ch[u][i]])
            dp[u][L]+=p[i]*f(ch[u][i],L-1);
    }
    return dp[u][L];
}
char str[110];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        Init();
        int K;
        scanf("%d",&K);
        for(int i=0;i<K;++i)
        {
            scanf("%s",str);
            insert(str);
        }
        scanf("%d",&n);
        char c[3];
        for(int i=0;i<n;++i)
        {
            scanf("%s",c);
            scanf("%lf",&p[idx(c[0])]);
        }
        build();
        int L;
        scanf("%d",&L);
        double ans=f(0,L);
        printf("Case #%d: %lf\n",tcase,ans);
    }
    return 0;
}

