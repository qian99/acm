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
const int maxn=150+10;
const int mod=10000;
int ch[150][55],next[150],flag[150],size;
int indx[1000],N,M,P;
char str[maxn];
void Init()
{
    memset(flag,0,sizeof(flag));
    memset(ch[0],0,sizeof(ch[0]));
    memset(next,0,sizeof(next));
    size=0;flag[0]=0;
}
void Insert(char *s)
{
    int u=0,n=strlen(s);
    for(int i=0;i<n;++i)
    {
        int c=indx[(int)s[i]];
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
    for(int i=0;i<N;++i)
        if(ch[0][i]) q.push(ch[0][i]);
    int r,u,v;
    while(!q.empty())
    {
        r=q.front();q.pop();
        for(int c=0;c<N;++c)
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
struct BigInt
{
    int num[maxn],len;
    void Clear()
    {
        memset(num,0,sizeof(num));
        len=1;
    }
    void printnum()
    {
        printf("%d",num[len-1]);
        for(int i=len-2;i>=0;--i)
            printf("%04d",num[i]);
        printf("\n");
    }
}dp[55][maxn];
BigInt add(BigInt  a,BigInt  b)
{
    int n=max(a.len,b.len);
    BigInt c;
    c.Clear();
    for(int i=0;i<n;++i)
    {
        c.num[i]+=a.num[i]+b.num[i];
        c.num[i+1]+=c.num[i]/mod;
        c.num[i]%=mod;
    }
    c.len=n;
    if(c.num[c.len]) c.len++;
    return c;
}
void solve()
{
    for(int j=0;j<=M;++j)
    for(int i=0;i<=size;++i) dp[j][i].Clear();
    dp[0][0].num[0]=1;
    for(int i=1;i<=M;++i)
    {
        for(int j=0;j<=size;++j)
        {
            if(flag[j]) continue;
            for(int c=0;c<N;++c)
            {
                if(flag[ch[j][c]]) continue;
                dp[i][ch[j][c]]=add(dp[i][ch[j][c]],dp[i-1][j]);
            }
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d%d%d",&N,&M,&P);
    Init();
    getchar();
    gets(str);
    for(int i=0;i<N;++i)
        indx[(int)str[i]]=i;
    for(int i=0;i<P;++i)
    {
        gets(str);
        Insert(str);
    }
    build();
    solve();
    BigInt ans;
    ans.Clear();
    for(int i=0;i<=size;++i)
        if(!flag[i]) ans=add(ans,dp[M][i]);
    ans.printnum();
    return 0;
}
