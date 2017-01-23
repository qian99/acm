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
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=1000+10;
const int maxm=10000+10;
bool vis[maxn];
int n,m;
struct Edge
{
    int v,next;
};
Edge edges[maxm<<1];
int head[maxn],nEdge;
void AddEdge(int u,int v)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
struct Node
{
    int p,len;
};
int bfs(int s)
{
    memset(vis,0,sizeof(vis));
    vis[s]=true;
    int cnt=1;
    Node tmp,no;
    tmp.p=s;tmp.len=0;
    queue<Node>q;
    q.push(tmp);
    int maxlen=0;
    while(!q.empty())
    {
        tmp=q.front();q.pop();
        maxlen=max(maxlen,tmp.len);
        int u=tmp.p;
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            int v=edges[k].v;
            if(!vis[v])
            {
                cnt++;
                vis[v]=true;
                no.p=v;no.len=tmp.len+1;
                q.push(no);
            }
        }
    }
    if(cnt!=n) return inf;
    return maxlen;
}
int solve()
{
    int res=0;
    for(int i=1;i<=n;++i)
    {
        int tmp=bfs(i);
        if(tmp>6) return -1;
        res=max(res,tmp);
    }
    return res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    map<string,int>mp;
    while(cin>>n)
    {
        if(n==0) break;
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        string str1,str2;
        for(int i=1;i<=n;++i)
        {
            cin>>str1;
            mp[str1]=i;
        }
        cin>>m;
        int u,v;
        for(int i=0;i<m;++i)
        {
            cin>>str1>>str2;
            u=mp[str1];v=mp[str2];
            AddEdge(u,v);
            AddEdge(v,u);
        }
        int ans=solve();
        cout<<ans<<endl;
    }
    return 0;
}
