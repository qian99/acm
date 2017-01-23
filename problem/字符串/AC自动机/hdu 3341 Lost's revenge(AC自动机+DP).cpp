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
const int maxn=500+10;
const int maxm=10000+10;
int ch[maxn][4],next[maxn],lastv[maxn],val[maxn],size;
void Init()
{
    memset(ch[0],0,sizeof(ch[0]));
    memset(next,0,sizeof(next));
    memset(lastv,0,sizeof(lastv));
    size=val[0]=0;
}
int indx(char c)
{
    if(c=='A') return 0;
    if(c=='C') return 1;
    if(c=='G') return 2;
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
            val[size]=0;
        }
        u=ch[u][c];
    }
    val[u]++;
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
            lastv[u]=val[next[u]]?next[u]:lastv[next[u]];
        }
    }
}
char str[55];
int dp[2][maxn][maxm],st[2][maxm][4];
int id[41][41][41][41],tot1,tot2;
int counts[maxn],tmp[4];
int solve()
{
    int n=strlen(str);
    memset(dp,0xff,sizeof(dp));
    memset(st,0,sizeof(st));
    memset(id,0,sizeof(id));
    memset(tmp,0,sizeof(tmp));
    memset(counts,0,sizeof(counts));
    tot1=tot2=0;
    int u;
    for(int i=0;i<=size;++i)
    {
        if(val[i]||lastv[i])
        {
            u=val[i]?i:lastv[i];
            while(u)
            {
                counts[i]+=val[u];
                u=lastv[u];
            }
        }
    }
    for(int i=0;i<n;++i)
        tmp[indx(str[i])]++;
    id[tmp[0]][tmp[1]][tmp[2]][tmp[3]]=++tot2;
    st[0][tot2][0]=tmp[0];st[0][tot2][1]=tmp[1];
    st[0][tot2][2]=tmp[2];st[0][tot2][3]=tmp[3];
    dp[0][0][1]=0;
    int i,j,k,c,h,now;
    for(i=0;i<n;++i)
    {
        h=i&1;
        for(j=1;j<=tot1;++j)
        {
            st[h^1][j][0]=st[h^1][j][1]=0;
            st[h^1][j][2]=st[h^1][j][3]=0;
            for(k=0;k<=size;++k) dp[h^1][k][j]=-1;
        }
        tot1=tot2;tot2=0;
        for(j=0;j<=size;++j)
            for(k=1;k<=tot1;++k)
            {
                if(dp[h][j][k]==-1) continue;
                for(c=0;c<4;++c)
                    tmp[c]=st[h][k][c];
                for(c=0;c<4;++c)
                {
                    if(tmp[c]==0) continue;
                    tmp[c]--;
                    u=ch[j][c];
                    now=id[tmp[0]][tmp[1]][tmp[2]][tmp[3]];
                    if(now==0)
                    {
                        now=id[tmp[0]][tmp[1]][tmp[2]][tmp[3]]=++tot2;
                        st[h^1][tot2][0]=tmp[0];st[h^1][tot2][1]=tmp[1];
                        st[h^1][tot2][2]=tmp[2];st[h^1][tot2][3]=tmp[3];
                    }
                    dp[h^1][u][now]=max(dp[h^1][u][now],dp[h][j][k]+counts[u]);
                    tmp[c]++;
                }
            }
    }
    int ans=0;
    h=n&1;
    for(i=0;i<=size;++i)
        for(j=1;j<=tot2;++j)
            ans=max(ans,dp[h][i][j]);
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
        tcase++;
        Init();
        for(int i=0;i<n;++i)
        {
            scanf("%s",str);
            Insert(str);
        }
        build();
        scanf("%s",str);
        int ans=solve();
        printf("Case %d: %d\n",tcase,ans);
    }
    return 0;
}
