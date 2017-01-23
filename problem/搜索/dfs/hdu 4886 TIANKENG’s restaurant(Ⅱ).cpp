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
const int maxn=1000000+10;
const int mval=9;
int flag[5400000];
int ans;
char str[maxn];
int cal(int s,int len)
{
    int res=0;
    for(int i=s;i<=s+len-1;++i)
    {
        res=res*mval+(str[i]-'A'+1);
    }
    return res;
}
void ptstr(int x)
{
    int len=0;
    while(x)
    {
        str[len++]=x%mval+'A'-1;
        x/=mval;
    }
    for(int i=len-1;i>=0;--i)
        putchar(str[i]);
    puts("");
}
void dfs(int x,int now,int lim)
{
    if(x==lim)
    {
        if(!flag[now])
        {
            if(ans==-1) ans=now;
            else ans=min(ans,now);
        }
        return ;
    }
    for(int i=1;i<=8;++i)
        dfs(x+1,now*mval+i,lim);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%s",str);
        memset(flag,0,sizeof(flag));
        int n=strlen(str);
        for(int i=1;i<=7;++i)
        {
            for(int j=0;j<=n-i;++j)
            {
                flag[cal(j,i)]=1;
            }
            ans=-1;
            dfs(0,0,i);
            if(ans!=-1) break;
        }
        ptstr(ans);
    }
    return 0;
}