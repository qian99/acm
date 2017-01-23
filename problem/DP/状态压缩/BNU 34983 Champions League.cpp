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
const int maxn=10000+10;
void CMP(ll a[2],ll b[2][2],ll v,int x,int y)
{
    if(b[0][0]==x&&b[0][1]==y) return ;
    if(b[1][0]==x&&b[1][1]==y) return ;
    if(a[0]<v)
    {
        a[1]=a[0];
        b[1][0]=b[0][0];
        b[1][1]=b[0][1];
        a[0]=v;
        b[0][0]=x;
        b[0][1]=y;
    }
    else if(a[1]<v)
    {
        a[1]=v;
        b[1][0]=x;
        b[1][1]=y;
    }
}
struct Group
{
    ll mat[5][5],val[25];
    ll mxval[3][2],mxid[3][2][2];
    void Init()
    {
        for(int i=1;i<=4;++i)
            for(int j=1;j<=4;++j)
            {
                scanf("%lld",&mat[i][j]);
                val[(i-1)*4+j-1]=mat[i][j];
            }
        sort(val,val+16);
        reverse(val,val+16);
        memset(mxval,0,sizeof(mxval));
        memset(mxid,0xff,sizeof(mxid));
        int t;
        for(int i=1;i<=4;++i)
            for(int j=1;j<=4;++j)
            {
                if(i==j) continue;
                if(i==1) t=j-2;
                if(j==1) t=i-2;
                for(int x=1;x<=4;++x)
                    for(int y=1;y<=4;++y)
                    {
                        if(x==i||x==j||x==y||y==i||y==j) continue;
                        if(x==1) t=y-2;
                        if(y==1) t=x-2;
                        CMP(mxval[t],mxid[t],mat[i][j],i,j);
                        CMP(mxval[t],mxid[t],mat[x][y],x,y);
                    }
            }
    }
}g[maxn];
bool cmp(Group a,Group b)
{
    for(int i=0;i<16;++i)
        if(a.val[i]!=b.val[i]) return a.val[i]>b.val[i];
    return true;
}
pair<int,int> xp[55][6];
bool vis[5];
int cnt,n;
ll dp[7][1<<6];
void dfs(int pos,pair<int,int> pii[6])
{
    if(pos==3)
    {
        for(int i=0;i<6;++i) xp[cnt][i]=pii[i];
        cnt++;
        return ;
    }
    for(int i=0;i<3;++i)
    {
        if(vis[i]) continue;
        vis[i]=true;
        pii[pos]=make_pair(i,0);
        pii[pos+3]=make_pair(i,1);
        dfs(pos+1,pii);
        pii[pos+3]=make_pair(i,0);
        pii[pos]=make_pair(i,1);
        dfs(pos+1,pii);
        vis[i]=false;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    pair<int,int> pii[6];
    memset(vis,0,sizeof(vis));
    cnt=0;
    dfs(0,pii);
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
            g[i].Init();
        sort(g+1,g+n+1,cmp);
        memset(dp,0xff,sizeof(dp));
        dp[0][0]=0;
        n=min(n,6);
        for(int i=1;i<=n;++i)
            for(int j=0;j<(1<<6);++j)
            {
                dp[i][j]=dp[i-1][j];
                for(int k=j&(j-1);k!=j;k=j&(k-1)) //
                {
                    if(dp[i-1][k]==-1) continue;
                    int msk=j^k;
                    for(int x=0;x<cnt;++x)
                    {
                        ll sum=0;
                        for(int y=0;y<6;++y)
                            if(msk&(1<<y))
                                sum+=g[i].mxval[xp[x][y].first][xp[x][y].second];
                        dp[i][j]=max(dp[i][j],dp[i-1][k]+sum);
                    }
                }
            }
        printf("Case #%d: %lld\n",++tcase,dp[n][(1<<6)-1]);
    }
    return 0;
}
