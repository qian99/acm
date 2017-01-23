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
const int maxn=100000+10;
const int maxm=100+10;
int p[8],sx[maxn][6],sy[maxn][6];
int dp[maxm][150],op[maxm][2],id[150][6];
int Cantor(int a[])
{
    int res=0,tmp;
    for(int i=1;i<=5;++i)
    {
        tmp=a[i]-1;
        for(int j=1;j<i;++j) if(a[j]<a[i]) tmp--;
        res+=tmp*p[5-i];
    }
    return res+1;
}
void Init()
{
    p[0]=1;
    for(int i=1;i<=5;++i) p[i]=p[i-1]*i;
    int a[6],cnt=0;
    for(int i=1;i<=5;++i) a[i]=i;
    do
    {
        cnt++;
        for(int i=1;i<=5;++i) id[cnt][i]=a[i];
    }while(next_permutation(a+1,a+6));
}
void cal(int a[],int b[],int c[])
{
    for(int i=1;i<=5;++i)
        c[i]=b[a[i]];
}
void cal2(int a[],int b[])
{
    for(int i=1;i<=5;++i)
        b[a[i]]=i;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    Init();
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        for(int i=1;i<=5;++i)
            sx[0][i]=sy[n+1][i]=i;
        int a[6],b[6];
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=5;++j)
                scanf("%d",&sy[i][j]);
            cal(sx[i-1],sy[i],sx[i]);
        }
        for(int i=n;i>=1;--i)
        {
            for(int j=1;j<=5;++j)
                a[j]=sy[i][j];
            cal(sy[i+1],a,sy[i]);
        }
        for(int i=1;i<=m;++i)
            scanf("%d%d",&op[i][0],&op[i][1]);
        for(int i=1;i<=5;++i)
            scanf("%d",&a[i]);
        memset(dp,0x3f,sizeof(dp));
        int x,s,t;
        x=Cantor(a);
        dp[0][x]=0;
        for(int i=0;i<m;++i)
            for(int j=1;j<=120;++j)
            {
                if(dp[i][j]==inf) continue;
                dp[i+1][j]=min(dp[i][j],dp[i+1][j]);
                s=op[i+1][0];t=op[i+1][1];
                if(s<t)
                {
                    cal2(sx[s-1],b);
                    cal(b,sx[t],a);
                    cal(id[j],a,b);
                    x=Cantor(b);
                    dp[i+1][x]=min(dp[i+1][x],dp[i][j]+t-s+1);
                }
                else
                {
                    cal2(sy[s+1],b);
                    cal(b,sy[t],a);
                    cal(id[j],a,b);
                    x=Cantor(b);
                    dp[i+1][x]=min(dp[i+1][x],dp[i][j]+s-t+1);
                }
            }
        int ans=dp[m][1];
        if(ans==inf) ans=-1;
        printf("%d\n",ans);
    }
    return 0;
}
