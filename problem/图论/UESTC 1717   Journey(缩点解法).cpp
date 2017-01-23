#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<map>
#include<queue>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
const int maxn=100000+10;
int du[maxn],tidai[maxn],way1[maxn],way2[maxn];
bool vis[maxn],treeleaf[maxn];
int n;
struct Dir
{
    int t,len;
};
vector<Dir>g[maxn];
int len1,len2;
void dfs(int u,int f,int c)
{
    int s=g[u].size();
    int v;
    for(int i=0;i<s;++i)
    {
        v=g[u][i].t;
        if(treeleaf[v]&&v!=f)
        {
            tidai[v]=c;
            dfs(v,u,c);
        }
    }
}
void dfs2(int u,int f,int s,int e,int step)
{
    int sn=g[u].size();
    int v;
    for(int i=0;i<sn;++i)
    {
        v=g[u][i].t;
        if(v!=f&&!treeleaf[v])
        {
            if(f==-1&&v==e) continue;
            if(v==s)
            {
                break;
            }
            step+=g[u][i].len;
            way1[v]=step;
            dfs2(v,u,s,e,step);
            step-=g[u][i].len;
        }
    }
}
void dfs3(int u,int f,int s,int e,int step)
{
    int sn=g[u].size();
    int v;
    for(int i=0;i<sn;++i)
    {
        v=g[u][i].t;
        if(v!=f&&!treeleaf[v])
        {
            if(f==-1&&v!=e) continue;
            if(v==s)
            {
                way2[n+1]=step+g[u][i].len;
                break;
            }
            step+=g[u][i].len;
            way2[v]=step;
            dfs3(v,u,s,e,step);
            step-=g[u][i].len;
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,qt,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        scanf("%d%d",&n,&qt);
        int a,b,c;
        Dir temp;
        for(int i=0;i<=n;++i)
           g[i].clear();
        memset(du,0,sizeof(du));
        memset(treeleaf,0,sizeof(treeleaf));
        int x,y;
        for(int i=1;i<=n;++i)
        {
            scanf("%d%d%d",&a,&b,&c);
            temp.t=b;temp.len=c;
            g[a].push_back(temp);
            temp.t=a;temp.len=c;
            g[b].push_back(temp);
            du[a]++;
            du[b]++;
            if(i==n)
            {
                x=a;
                y=b;
            }
        }
        queue<int>q;
        for(int i=1;i<=n;++i)
        {
            if(du[i]==1)
            {
                q.push(i);
                treeleaf[i]=true;
            }
        }
        int u,s,v;
        while(!q.empty())
        {
            u=q.front();
            q.pop();
            s=g[u].size();
            for(int i=0;i<s;++i)
            {
                v=g[u][i].t;
                du[v]--;
                if(du[v]==1)
                {
                    treeleaf[v]=true;
                    q.push(v);
                }
            }
        }
        for(int i=1;i<=n;++i)
        {
            if(!treeleaf[i])
            {
                tidai[i]=i;
                dfs(i,-1,i);
            }
        }
        way1[x]=0;
        way2[x]=0;
        len1=len2=-1;
        dfs2(x,-1,x,y,0);
        dfs3(x,-1,x,y,0);
        int ans1=0,ans2=0;
        printf("Case #%d:\n",tcase);
        for(int i=0;i<qt;++i)
        {
            scanf("%d%d",&a,&b);
            a=tidai[a];
            b=tidai[b];
            ans1=0;ans2=0;
            ans1=abs(way1[a]-way1[b]);
            ans2=abs(way2[a]-way2[b]);
            ans2=min(ans2,way2[n+1]-ans2);
            if(ans1>ans2) ans1=ans1-ans2;
            else ans1=0;
            printf("%d\n",ans1);
        }
    }
    return 0;
}
