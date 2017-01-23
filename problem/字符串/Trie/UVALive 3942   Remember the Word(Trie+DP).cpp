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
const int maxn=300000+10;
const int maxm=100+10;
const int maxnode=400000+10;
const int mod=20071027;
int ch[maxnode][26],val[maxnode],size;
char str[maxn],ss[maxm];
int dp[maxn];
void Init()
{
    memset(ch[0],0,sizeof(ch[0]));
    val[0]=0;size=0;
}
void insert(char *s)
{
    int u=0,n=strlen(s);
    for(int i=0;i<n;++i)
    {
        int c=s[i]-'a';
        if(!ch[u][c])
        {
            ch[u][c]=++size;
            memset(ch[size],0,sizeof(ch[size]));
            val[size]=0;
        }
        u=ch[u][c];
    }
    val[u]=n;
}
void find(int x,int n)
{
    int u=0;
    for(int i=x;i<n;++i)
    {
        int c=str[i]-'a';
        if(!ch[u][c]) break;
        if(val[ch[u][c]])
            dp[x]=(dp[x]+dp[i+1])%mod;
        u=ch[u][c];
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int tcase=0;
    while(~scanf("%s",str))
    {
        tcase++;
        int m,n=strlen(str);
        scanf("%d",&m);
        Init();
        for(int i=0;i<m;++i)
        {
            scanf("%s",ss);
            insert(ss);
        }
        memset(dp,0,sizeof(dp));
        dp[n]=1;
        for(int i=n-1;i>=0;--i)
            find(i,n);
        printf("Case %d: %d\n",tcase,dp[0]);
    }
    return 0;
}

