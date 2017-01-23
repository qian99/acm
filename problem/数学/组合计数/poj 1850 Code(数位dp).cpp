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
const int maxn=26;
ll dp[15][30];
int num[15];
char str[15];
ll f(int pos,int st,bool limit)
{
    if(pos==-1) return st!=0;
    if(!limit&&dp[pos][st]!=-1) return dp[pos][st];
    ll ans=0;
    int last=limit?num[pos]:maxn;
    for(int i=st+1;i<=last;++i)
        ans+=f(pos-1,i,limit&&i==last);
    if(!limit) dp[pos][st]=ans;
    return ans;
}
ll cal(const char *s)
{
    memset(dp,0xff,sizeof(dp));
    int len=strlen(s);
    char c=str[0];
    for(int i=1;i<len;++i)
        if(str[i]<=c) return 0;
        else c=str[i];
    for(int i=0;i<len;++i)
        num[i]=(s[len-i-1]-'a')+1;
    ll res=0;
    for(int i=0;i<len-1;++i)
        res+=f(i,0,false);
    return f(len-1,0,true)+res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%s",str))
    {
        ll ans=cal(str);
        cout<<ans<<endl;
    }
    return 0;
}
