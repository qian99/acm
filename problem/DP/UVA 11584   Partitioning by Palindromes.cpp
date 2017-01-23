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
const int maxn=1000+10;
char str[maxn];
bool ispal[maxn][maxn];
int dp[maxn];
void getpal(int n)
{
    memset(ispal,0,sizeof(ispal));
    for(int i=0;i<n;++i) ispal[i][i]=true;
    int a,b;
    for(int i=1;i<n;++i)
    {
        for(int j=0;j+i<n;++j)
        {
            a=j+1;b=j+i-1;
            if(a>b&&str[j]==str[i+j]) ispal[j][i+j]=true;
            if(ispal[a][b]&&str[j]==str[i+j])
              ispal[j][i+j]=true;
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    while(~scanf("%d",&t))
    {
        scanf("%s",str);
        int n=strlen(str);
        getpal(n);
        memset(dp,0,sizeof(dp));
        dp[0]=0;
        dp[1]=1;
        for(int i=1;i<n;++i)
        {
            dp[i+1]=dp[i]+1;
            for(int j=0;j<i;++j)
            {
                if(ispal[j][i])
                  dp[i+1]=min(dp[i+1],dp[j]+1);
            }
        }
        printf("%d\n",dp[n]);
    }
    return 0;
}
