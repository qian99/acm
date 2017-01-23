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
const int maxn=2000+10;
const int maxl=200+10;
const int mod=1000000009;
int ch[maxn][2],next[maxn],flag[maxn],size;
int num[maxl],dp[maxl][maxn];
char str[maxn];
void Init()
{
    ch[0][0]=ch[0][1]=0;
    memset(next,0,sizeof(next));
    flag[0]=size=0;
    memset(dp,0xff,sizeof(dp));
}
void Insert(const char *s)
{
    int u=0,n=strlen(s);
    for(int i=0;i<n;++i)
    {
        int c=s[i]-'0';
        if(!ch[u][c])
        {
            ch[u][c]=++size;
            ch[size][0]=ch[size][1]=0;
            flag[size]=0;
        }
        u=ch[u][c];
    }
    flag[u]=1;
}
void build()
{
    queue<int>q;
    if(ch[0][0]) q.push(ch[0][0]);
    if(ch[0][1]) q.push(ch[0][1]);
    int r,u,v;
    while(!q.empty())
    {
        r=q.front();q.pop();
        for(int c=0;c<2;++c)
        {
            u=ch[r][c];
            if(!u) {ch[r][c]=ch[next[r]][c];continue;}
            q.push(u);
            v=next[r];
            while(v&&!ch[v][c]) v=next[v];
            next[u]=ch[v][c];
            flag[u]|=flag[next[u]];
        }
    }
}
int f(int pos,int st,bool zero,bool limit)
{
    if(pos==-1) return 1;
    if(!limit&&dp[pos][st]!=-1)
        return dp[pos][st];
    int ans=0,u,i=0,last;
    if(pos>0&&zero)
    {
        ans=(ans+f(pos-1,0,true,limit&&num[pos]==0))%mod;
        i=1;
    }
    last=limit?num[pos]:9;
    for(;i<=last;++i)
    {
        u=st;
        for(int j=3;j>=0;--j)
        {
            u=ch[u][(i&(1<<j))!=0];
            if(flag[u]) {u=-1;break;}
        }
        if(u!=-1)
            ans=(ans+f(pos-1,u,false,limit&&i==last))%mod;
    }
    if(!limit&&!zero) dp[pos][st]=ans;
    return ans;
}
int cal(bool d)
{
    memset(num,0,sizeof(num));
    int len=strlen(str);
    for(int i=0;i<len;++i)
        num[i]=str[len-i-1]-'0';
    if(d)
    {
        num[0]--;
        int i=0;
        while(num[i]<0)
        {
            num[i++]=9;
            num[i]--;
        }
        if(!num[len-1]&&len!=1) len--;
    }
    return f(len-1,0,true,true);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n;
    scanf("%d",&t);
    while(t--)
    {
        Init();
        scanf("%d",&n);
        for(int i=0;i<n;++i)
        {
            scanf("%s",str);
            Insert(str);
        }
        build();
        int res=0;
        scanf("%s",str);
        res-=cal(true);
        scanf("%s",str);
        res+=cal(false);
        res=(res%mod+mod)%mod;
        printf("%d\n",res);
    }
    return 0;
}
