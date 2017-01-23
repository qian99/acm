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
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 500 + 10;
const int maxm = 1000 + 10;
struct Edge
{
    int v,next;
    Edge(int v = 0,int next = 0):v(v),next(next){}
}edges[maxm<<1];
int head[maxn],degree[maxn],nEdge,n,m;
bool vis[maxn];
vector<pair<int,int> >ans;
void AddEdges(int u,int v)
{
    edges[++nEdge] = Edge(v,head[u]);
    head[u] = nEdge;
    edges[++nEdge] = Edge(u,head[v]);
    head[v] = nEdge;
}
int dfs(int u,int pre,int target)
{
    vis[u] = true;
    if(u == target) return 1;
    if(degree[u] >= 3) return 0;
    for(int k = head[u];k != -1;k = edges[k].next)
    {
        int v = edges[k].v;
        if(v == pre) continue;
        if(v == target) return 2;
        if(vis[v]) return 0;
        int res = dfs(v,u,target);
        if(res) return res + 1;
        return 0;
    }
    return 0;
}
int ischain(int u,int pre)
{
    vis[u] = true;
    if(degree[u] > 2) return 0;
    for(int k = head[u];k != -1;k = edges[k].next)
    {
        int v = edges[k].v;
        if(v == pre) continue;
        if(vis[v]) return 0;
        int res = ischain(v,u);
        if(res) return res + 1;
        return 0;
    }
    return 1;
}
void check0()
{
    for(int i = 1;i <= n;++i)
        if(degree[i] != 2) return ;
    memset(vis,0,sizeof(vis));
    int v = edges[head[1]].v;
    vis[1] = true;
    if(!dfs(v,1,1)) return ;
    for(int i = 1;i <= n;++i)
        if(!vis[i]) return;
    if(n >= 6 && (n - 6)%6 == 0)
        ans.push_back(make_pair(0,(n-6)/6));
}
void check1257()
{
    memset(vis,0,sizeof(vis));
    int root = -1;
    for(int i = 1;i <= n;++i)
        if(degree[i] == 1)
        {
            root = i;
            break;
        }
    if(!ischain(root,-1)) return ;
    for(int i = 1;i <= n;++i)
        if(!vis[i]) return ;
    if(n >= 3 && (n - 3)%2 == 0)
        ans.push_back(make_pair(1,(n-3)/2));
    if(n >= 6 && (n - 6)%5 == 0)
    {
        ans.push_back(make_pair(2,(n-6)/5));
        ans.push_back(make_pair(5,(n-6)/5));
    }
    if(n >= 4 && (n-4)%3 == 0)
        ans.push_back(make_pair(7,(n-4)/3));
}
void check34()
{
    int root = -1;
    for(int i = 1;i <= n;++i)
        if(degree[i] == 3)
        {
            if(root == -1) root = i;
            else return ;
        }
    memset(vis,0,sizeof(vis));
    vis[root] = true;
    int a[3],cnt = 0;
    for(int k = head[root];k != -1;k = edges[k].next)
    {
        a[cnt] = ischain(edges[k].v,root);
        if(a[cnt] == 0) return ;
        cnt++;
    }
    for(int i = 1;i <= n;++i)
        if(!vis[i]) return ;
    a[0]++;a[1]++;a[2]++;
    sort(a,a + 3);
    if(a[0] == a[1])
    {
        if(a[0] >= 2 && a[2] >= 3)
        {
            int x = a[0] - 2;
            int y = a[2] - 3;
            if(x*2 == y)
            {
                ans.push_back(make_pair(4,x));
            }
        }
    }
    if(a[1] == a[2])
    {
        if(a[0] >= 2 && a[1] >= 3)
        {
            int x = a[0] - 2;
            int y = a[1] - 3;
            if(x*2 == y)
            {
                ans.push_back(make_pair(3,x));
            }
        }
    }
}
void check69()
{
    memset(vis,0,sizeof(vis));
    int root = -1;
    for(int i = 1;i <= n;++i)
        if(degree[i] == 3)
        {
            if(root == -1) root = i;
            else return ;
        }
    vis[root] = true;
    int circle = 0,chain = 0,cv = -1;
    for(int k = head[root];k != -1;k = edges[k].next)
    {
        int v = edges[k].v;
        int x = ischain(v,root);
        if(x)
        {
            chain = x + 1;
            cv = v;
            break;
        }
    }
    if(cv == -1) return ;
    memset(vis,0,sizeof(vis));
    vis[root] = true;
    for(int k = head[root];k != -1;k = edges[k].next)
    {
        int v = edges[k].v;
        if(v == cv) ischain(v,root);
        else
        {
            if(vis[v]) continue;
            int x = dfs(v,root,root);
            if(!x) return ;
            circle = x;
        }
    }
    for(int i = 1;i <= n;++i)
        if(!vis[i]) return ;
    if(chain >= 3 && circle >= 4)
    {
        chain -= 3;
        circle -= 4;
        if(chain % 2 == 0 && chain*2 == circle)
        {
            ans.push_back(make_pair(6,chain/2));
            ans.push_back(make_pair(9,chain/2));
        }
    }
}
void check8()
{
    memset(vis,0,sizeof(vis));
    int a[2],cnt = 0;
    for(int i = 1;i <= n;++i)
    {
        if(degree[i] == 3)
        {
            if(cnt == 2) return ;
            a[cnt++] = i;
        }
        else if(degree[i] != 2)
            return ;
    }
    if(cnt != 2) return ;
    int b[3],root = a[0];
    vis[root] = true;
    cnt = 0;
    for(int k = head[root];k != -1;k = edges[k].next)
    {
        int v = edges[k].v;
        if(vis[v]) return ;
        int x = dfs(v,root,a[1]);
        if(!x) return ;
        b[cnt++] = x + 1;
        vis[a[1]] = false;
    }
    vis[a[1]] = true;
    sort(b,b + cnt);
    for(int i = 1;i <= n;++i)
        if(!vis[i]) return ;
    if(b[1] != b[2]) return ;
    if(b[1] >= 4 && b[2] >= 4 && b[0] >= 2)
    {
        int x = b[1] - 4;
        int y = b[0] - 2;
        if(y*3 == x)
        {
            ans.push_back(make_pair(8,y));
        }
    }
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t,tcase = 0;
    scanf("%d",&t);
    while(t--)
    {
        if(tcase) printf("\n");
        scanf("%d%d",&n,&m);
        memset(head,0xff,sizeof(head));
        nEdge = -1;
        memset(degree,0,sizeof(degree));
        int u,v;
        for(int i = 1;i <= m;++i)
        {
            scanf("%d%d",&u,&v);
            AddEdges(u,v);
            degree[u]++;degree[v]++;
        }
        ans.clear();
        check0();
        check1257();
        check34();
        check69();
        check8();
        sort(ans.begin(),ans.end());
        int tot = ans.size();
        printf("Case %d: %d\n",++tcase,tot);
        for(int i = 0;i < tot;++i)
            printf("%d %d\n",ans[i].first,ans[i].second);
    }
    return 0;
}

