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
int num[maxn],dp[maxm],pa[maxm];
int ans[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    scanf("%d%d",&n,&m);
    memset(dp,0xff,sizeof(dp));
    memset(pa,0xff,sizeof(pa));
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&num[i]);
        num[i]%=m;
    }
    int tmp,tmp2;
    for(int i=1;i<=n;++i)
    {
        tmp=num[i];
        if(dp[tmp]==-1) {dp[tmp]=-2;pa[tmp]=i;}
        for(int j=0;j<m;++j)
        {
            if(dp[j]!=-1&&pa[j]!=i)
            {
                tmp2=(tmp*j)%m;
                if(dp[tmp2]==-1) {dp[tmp2]=j; pa[tmp2]=i;}
            }
        }
    }
    int maxv=0;
    for(int i=m-1;i>0;--i)
        if(dp[i]!=-1) {maxv=i;break;}
    if(maxv==0)
    {
        printf("1\n");
    }
    else
    {
        printf("%d\n",maxv);
        int p=maxv;
        int cnt=0;
        while(dp[p]!=-2)
        {
            ans[cnt++]=pa[p];
            p=dp[p];
        }
        ans[cnt++]=pa[p];
        sort(ans,ans+cnt);
        for(int i=0;i<cnt;++i)
            printf("%d ",ans[i]);
        printf("\n");
    }
    return 0;
}

