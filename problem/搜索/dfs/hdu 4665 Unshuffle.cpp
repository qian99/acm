#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<vector>
#define inf 2139062143
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=2000+10;
int num[maxn],vis[maxn];
int n;
bool dfs(int s,int t,int cur)
{
    if(cur==n/2) return true;
    for(int i=s;i<n;++i)
    {
        if(vis[i]==-1)
        {
            vis[i]=0;
            int j=max(i+1,t+1);
            for(;j<n;++j)
            {
                if(vis[j]==-1&&num[i]==num[j])
                {
                    vis[j]=1;
                    if(dfs(i+1,j,cur+1)) return true;
                    vis[j]=-1;
                }
            }
            vis[i]=-1;
            break;
        }
    }
    return false;
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
        for(int i=0;i<n;++i)
           scanf("%d",&num[i]);
        memset(vis,0xff,sizeof(vis));
        dfs(0,0,0);
        for(int i=0;i<n;++i)
           printf("%d",vis[i]);
        printf("\n");
    }
    return 0;
}
