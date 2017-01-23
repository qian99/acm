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
const int maxn=300+10;
const int maxm=100000+10;
int a[maxm],dp[maxn][maxm];
vector<int>bnum[maxm];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,s,e,val;
    scanf("%d%d%d%d",&n,&m,&s,&e);
    for(int i=1;i<=n;++i)
        scanf("%d",&a[i]);
    for(int i=1;i<=m;++i)
    {
        scanf("%d",&val);
        bnum[val].push_back(i);
    }
    memset(dp,0x3f,sizeof(dp));
    vector<int>:: iterator it;
    int ans=0,tmp;
    for(int i=1;i<=300;++i)
    {
        int p=i==1?0:inf;
        for(int j=1;j<=n;++j)
        {
            it=upper_bound(bnum[a[j]].begin(),bnum[a[j]].end(),p);
            if(it!=bnum[a[j]].end())
            {
                //int z=*it;
                tmp=i*e+j+*it;
                if(tmp<=s)
                {
                    dp[i][j]=*it;
                    ans=i;
                }
            }
            p=min(p,dp[i-1][j]);
        }
    }
    printf("%d\n",ans);
    return 0;
}
