#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<set>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=2000+10;
const int maxm=100+10;
int val[maxn][maxm],sum[maxn][maxm],neg[maxn],cnt[maxn][maxm][2];
int n,m,b,g;
void Init(int n,int m)
{
    memset(neg,0,sizeof(neg));
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
        {
            sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+val[i][j];
            cnt[i][j][0]+=cnt[i-1][j][0]+cnt[i][j-1][0]-cnt[i-1][j-1][0];
            cnt[i][j][1]+=cnt[i-1][j][1]+cnt[i][j-1][1]-cnt[i-1][j-1][1];
        }
}
int cal(int sx,int sy,int ex,int ey)
{
    int res=sum[ex][ey]-sum[ex][sy-1]-sum[sx-1][ey]+sum[sx-1][sy-1];
    int tmp1=cnt[ex][ey][0]-cnt[ex][sy-1][0]-cnt[sx-1][ey][0]+cnt[sx-1][sy-1][0];
    int tmp2=cnt[ex][ey][1]-cnt[ex][sy-1][1]-cnt[sx-1][ey][1]+cnt[sx-1][sy-1][1];
    if(tmp1<g||tmp2<b) return -1;
    return res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d%d%d",&m,&n,&b,&g))
    {
        int tmp;
        for(int i=1;i<=m;++i)
            for(int j=1;j<=n;++j)
            {
                scanf("%d%d",&val[j][i],&tmp);
                cnt[j][i][0]=(tmp==1)?0:1;
                cnt[j][i][1]=(tmp==1)?1:0;
            }
        Init(n,m);
        int ans=-1,maxv;
        for(int i=1;i<=n;++i)
            for(int j=1;j<=m;++j)
            {
                if(val[i][j]<0) neg[j]=i;
                else
                {
                    maxv=cal(neg[j]+1,j,i,j);
                    tmp=neg[j]+1;
                    for(int k=j-1;k>=1;--k)
                    {
                        tmp=max(tmp,neg[k]+1);
                        if(tmp>i) break;
                        maxv=max(maxv,cal(tmp,k,i,j));
                    }
                    ans=max(ans,maxv);
                }
            }
        if(ans<0) printf("No solution!\n");
        else printf("%d\n",ans);
    }
    return 0;
}
