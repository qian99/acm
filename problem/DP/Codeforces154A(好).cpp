#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
const int maxn=100000+10;
char str[maxn];
bool rule[255][255];
int dp[255];

int main()
{
    //freopen("in.txt","r",stdin);
    while(~scanf("%s",str))
    {
        int n=strlen(str);
        int m;
        scanf("%d",&m);
        char a[3];
        memset(rule,true,sizeof(rule));
        for(int i=0;i<m;++i)
        {
            scanf("%s",a);
            rule[a[0]][a[1]]=false;
            rule[a[1]][a[0]]=false;
        }
        memset(dp,0,sizeof(dp));
        int maxlen=0;
        for(int i=0;i<n;++i)
        {
            if(rule[str[i]][str[i]])
                dp[str[i]]++;
            for(int j=0;j<26;++j)
            {
                if('a'+j==str[i]) continue;
                if(rule['a'+j][str[i]])
                {
                    dp[str[i]]=max(dp['a'+j]+1,dp[str[i]]);
                }
            }
        }
        for(int i=0;i<26;++i)
        {
            maxlen=max(maxlen,dp['a'+i]);
        }
        printf("%d\n",n-maxlen);
    }
    return 0;
}
