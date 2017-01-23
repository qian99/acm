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
#include<bitset>
#include<set>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=1000000+1111;
int ch[maxn][26],dp[maxn],tot;
char str[maxn];
void Init()
{
    memset(ch[0],0,sizeof(ch[0]));
    tot=0;
    dp[0]=inf;
}
void Insert(int n)
{
    int u=0,c;
    for(int i=0;i<n;++i)
    {
        c=str[i]-'a';
        if(!ch[u][c])
        {
            ch[u][c]=++tot;
            memset(ch[tot],0,sizeof(ch[tot]));
            dp[tot]=n-i-1;
        }
        u=ch[u][c];
        dp[u]=min(dp[u],n-i-1);
    }
    dp[u]=0;
}
int Find(int n)
{
    int u=0,c;
    int minv=n;
    for(int i=1;i<=n;++i)
    {
        c=str[i-1]-'a';
        if(!ch[u][c]) return minv;
        u=ch[u][c];
        minv=min(minv,1+dp[u]+n-i);
    }
    return minv;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int m;
        scanf("%d",&m);
        scanf("%s",str);
        Init();
        int ans,len;
        len=strlen(str);
        Insert(len);
        while(m--)
        {
            scanf("%s",str);
            len=strlen(str);
            ans=Find(len);
            printf("%d\n",ans);
            Insert(len);
        }
    }
    return 0;
}
