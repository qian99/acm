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
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=200+10;
int k[maxn];
bool vis[maxn];
int n;
struct Floor
{
    int pos,step;
};
int bfs(int s,int t)
{
    memset(vis,0,sizeof(vis));
    queue<Floor>q;
    q.push((Floor){s,0});
    while(!q.empty())
    {
        Floor now=q.front();q.pop();
        if(now.pos==t) return now.step;
        if(vis[now.pos]) continue ;
        vis[now.pos]=true;
        int x=now.pos+k[now.pos];
        if(x>=1&&x<=n&&!vis[x])
          q.push((Floor){x,now.step+1});
        x=now.pos-k[now.pos];
        if(x>=1&&x<=n&&!vis[x])
          q.push((Floor){x,now.step+1});
    }
    return -1;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int s,t;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        scanf("%d%d",&s,&t);
        for(int i=1;i<=n;++i)
           scanf("%d",&k[i]);
        int ans=bfs(s,t);
        printf("%d\n",ans);
    }
    return 0;
}
