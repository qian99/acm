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
char str[maxn];
int next[maxn],dp[maxn];
bool flag[maxn];
void getFail(int n)
{
    next[0]=next[1]=0;
    for(int i=1;i<n;++i)
    {
        int j=next[i];
        while(j&&str[j]!=str[i]) j=next[j];
        next[i+1]=str[j]==str[i]?j+1:0;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%s",str);
    int n=strlen(str),cnt=0;
    getFail(n);
    memset(flag,0,sizeof(flag));
    for(int i=0;i<=n;++i) dp[i]=1;
    for(int i=n;i>=0;--i) dp[next[i]]+=dp[i];
    for(int i=n;i;i=next[i]) flag[i]=true,cnt++;
    printf("%d\n",cnt);
    for(int i=1;i<=n;++i)
        if(flag[i]) printf("%d %d\n",i,dp[i]);
    return 0;
}
