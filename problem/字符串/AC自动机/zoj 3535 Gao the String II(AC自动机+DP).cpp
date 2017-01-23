#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=555;
const int csize=26;
int ch[maxn][csize],lastv[maxn],flag[maxn];
int next[maxn],cnt[maxn],size;
char str[maxn],astr[55][15];
int m,n,L,dp[55][55][maxn],conect[55][55][15],lena[55];
void Init()
{
    memset(ch[0],0,sizeof(ch[0]));
    memset(cnt,0,sizeof(cnt));
    memset(lastv,0,sizeof(lastv));
    memset(flag,0,sizeof(flag));
    memset(next,0,sizeof(next));
    size=0;
}
void Insert(const char *s)
{
    int u=0;
    for(int i=0;s[i];++i)
    {
        int c=s[i]-'a';
        if(!ch[u][c])
        {
            ch[u][c]=++size;
            memset(ch[size],0,sizeof(ch[size]));
        }
        u=ch[u][c];
    }
    flag[u]++;
}
void build()
{
    queue<int>q;
    for(int i=0;i<csize;++i)
        if(ch[0][i]) q.push(ch[0][i]);
    int r,u;
    while(!q.empty())
    {
        r=q.front();q.pop();
        for(int c=0;c<csize;++c)
        {
            u=ch[r][c];
            if(!u) {ch[r][c]=ch[next[r]][c];continue;}
            q.push(u);
            int j=next[r];
            while(j&&!ch[j][c]) j=next[j];
            next[u]=ch[j][c];
            lastv[u]=flag[next[u]]?next[u]:lastv[next[u]];
        }
    }
    for(int i=1;i<=size;++i)
    {
        u=i;
        if(flag[u]||lastv[u])
        {
            u=flag[u]?u:lastv[u];
            while(u)
            {
                cnt[i]+=flag[u];
                u=lastv[u];
            }
        }
    }
}
bool check(int x,int y,int z)
{
    int lenx=lena[x];
    if(z>lenx) return false;
    for(int i=0;i<z;++i)
    {
        if(astr[x][lenx-z+i]!=astr[y][i]) return false;
    }
    return true;
}
int solve()
{
    lena[0]=0;
    memset(conect,0,sizeof(conect));
    for(int i=1;i<=m;++i)
    {
        conect[0][i][0]=1,conect[0][i][1]=0;
        lena[i]=strlen(astr[i]);
    }
    for(int i=1;i<=m;++i)
        for(int j=1;j<=m;++j)
        {
            conect[i][j][0]=1;
            conect[i][j][1]=0;
            for(int k=1;k<lena[j];++k)
            {
                if(check(i,j,k)) {conect[i][j][0]++;conect[i][j][conect[i][j][0]]=k;}
            }
        }
    memset(dp,0xff,sizeof(dp));
    dp[0][0][0]=0;
    int ans=0,u,c,tmp;
    for(int i=0;i<=L;++i)
        for(int j=0;j<=m;++j)
            for(int k=0;k<=size;++k)
            {
                if(j==0&&i!=0) continue;
                if(dp[i][j][k]==-1) continue;
                if(dp[i][j][k]>ans) ans=dp[i][j][k];
                for(int x=1;x<=m;++x)
                    for(int y=1;y<=conect[j][x][0];++y)
                    {
                        u=k;tmp=0;
                        for(int z=conect[j][x][y];astr[x][z];++z)
                        {
                            c=astr[x][z]-'a';
                            u=ch[u][c];
                            tmp+=cnt[u];
                        }
                        int pos=i+lena[x]-conect[j][x][y];
                        if(pos>L) continue;
                        if(dp[pos][x][u]==-1) dp[pos][x][u]=dp[i][j][k]+tmp;
                        else dp[pos][x][u]=max(dp[pos][x][u],dp[i][j][k]+tmp);
                    }
            }
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d%d",&m,&n,&L))
    {
        Init();
        astr[0][0]='\0';
        for(int i=1;i<=m;++i)
            scanf("%s",astr[i]);
        for(int i=0;i<n;++i)
        {
            scanf("%s",str);
            Insert(str);
        }
        build();
        int ans=solve();
        printf("%d\n",ans);
    }
    return 0;
}
