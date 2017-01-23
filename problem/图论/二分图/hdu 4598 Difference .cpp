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
const int maxn=300+10;
char g[maxn][maxn];
int color[maxn],n,cnt;
bool dfs(int u)
{
    cnt++;
    for(int i=0;i<n;++i)
    {
        if(i!=u&&g[u][i]=='1')
        {
            if(color[i]==color[u]) return false;
            if(color[i]) continue;
            color[i]=3-color[u];
            if(!dfs(i)) return false;
        }
    }
    return true;
}
void cal(int u)
{
    cnt++;
    color[u]=1;
    for(int i=0;i<n;++i)
    {
        if(!color[i]&&g[u][i]=='1')
            cal(i);
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        memset(color,0,sizeof(color));
        for(int i=0;i<n;++i)
            scanf("%s",g[i]);
        bool flag=true;
        cnt=1;
        int kk=0;
        while(cnt==1&&kk<n)
        {
            color[kk]=1;
            cnt=0;
            if(!dfs(kk)) flag=false;
            kk++;
        }
        for(int i=kk;i<n;++i)
        {
            if(color[i]) continue;
            cnt=0;
            cal(i);
            if(cnt!=1) flag=false;
        }
        if(flag) puts("Yes");
        else puts("No");
    }
    return 0;
}
