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
struct Node
{
    int len;
    string str;
    bool operator < (const Node &a) const
    {
        return (len==a.len&&str>a.str)||(len<a.len);
    }
};
char str1[maxn];
char str2[maxn];
char res[maxn];
Node dp[maxn][maxn],ans;
void Lcs(int n)
{
    for(int i=0;i<=n;++i)
    {
        dp[i][0].len=dp[0][i].len=0;
        dp[i][0].str.clear();
        dp[0][i].str.clear();
    }
    ans.len=0;
    ans.str.clear();
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(str1[i-1]==str2[j-1])
            {
                dp[i][j].len=dp[i-1][j-1].len+1;
                dp[i][j].str=dp[i-1][j-1].str+str1[i-1];
            }
            else if(dp[i-1][j]<dp[i][j-1])
                dp[i][j]=dp[i][j-1];
            else
                dp[i][j]=dp[i-1][j];
            if(ans<dp[i][j])
              ans=dp[i][j];
        }
    }
    int len=ans.len/2,m=0;
    for(int i=0;i<len;++i)
      res[m++]=ans.str[i];
    if(ans.len&1) res[m++]=ans.str[len];
    for(int i=len-1;i>=0;--i)
      res[m++]=ans.str[i];
    res[m]='\0';
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%s",str1))
    {
        int n=strlen(str1);
        for(int i=0;i<n;++i)
          str2[i]=str1[n-i-1];
        Lcs(n);
        printf("%s\n",res);
    }
    return 0;
}
