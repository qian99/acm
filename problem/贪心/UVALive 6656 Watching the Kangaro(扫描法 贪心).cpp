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
const int maxn = 300000 + 10;
struct Node
{
    int x,type,id;
    Node(int x = 0,int type = 0,int id = 0):x(x),type(type),id(id){}
    bool operator < (const Node & a) const
    {
        return x < a.x;
    }
}node[maxn];
int L[maxn],R[maxn],Q[maxn];
int ans[maxn],n,m;
bool flag[maxn];
priority_queue<Node>q;
bool cmp1(Node a,Node b)
{
    if(a.x == b.x) return a.type < b.type;
    return a.x < b.x;
}
bool cmp2(Node a,Node b)
{
    if(a.x == b.x) return a.type < b.type;
    return a.x > b.x;
}
void solve()
{
    int tot = 0;
    for(int i = 1;i <= n;++i)
    {
        node[++tot] = Node(L[i],-1,i);
        node[++tot] = Node(L[i] + (R[i] - L[i])/2,1,i);
    }
    for(int i = 1;i <= m;++i)
        node[++tot] = Node(Q[i],0,i);
    sort(node + 1,node + tot + 1,cmp1);
    for(int i = 1;i <= m;++i)
        ans[i] = -inf;
    memset(flag,0,sizeof(flag));
    Node ntmp;
    while(!q.empty()) q.pop();
    for(int i = 1;i <= tot;++i)
    {
        if(node[i].type != 0)
        {
            if(node[i].type == -1)
            {
                flag[node[i].id] = true;
                q.push(Node(-node[i].x,0,node[i].id));
            }
            else
            {
                flag[node[i].id] = false;
            }
        }
        else
        {
           while(!q.empty())
           {
               ntmp = q.top();
               if(!flag[ntmp.id])
               {
                   q.pop();
                   continue;
               }
               ans[node[i].id] = (node[i].x + ntmp.x);
               break;
           }
        }
    }
    tot = 0;
    for(int i = 1;i <= n;++i)
    {
        node[++tot] = Node(R[i] - (R[i] - L[i])/2,1,i);
        node[++tot] = Node(R[i],-1,i);
    }
    for(int i = 1;i <= m;++i)
        node[++tot] = Node(Q[i],0,i);
    sort(node + 1,node + tot + 1,cmp2);
    while(!q.empty()) q.pop();
    for(int i = 1;i <= tot;++i)
    {
        if(node[i].type != 0)
        {
            if(node[i].type == -1)
            {
                flag[node[i].id] = true;
                q.push(Node(node[i].x,0,node[i].id));
            }
            else
            {
                flag[node[i].id] = false;
            }
        }
        else
        {
            while(!q.empty())
            {
                ntmp = q.top();
                if(!flag[ntmp.id])
                {
                    q.pop();
                    continue;
                }
                ans[node[i].id] = max(ans[node[i].id],ntmp.x - node[i].x);
                break;
            }
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

        scanf("%d%d",&n,&m);
        for(int i = 1;i <= n;++i)
            scanf("%d%d",&L[i],&R[i]);
        for(int i = 1;i <= m;++i)
            scanf("%d",&Q[i]);
        solve();
        printf("Case %d:\n",++tcase);
        for(int i = 1;i <= m;++i)
            if(ans[i] == -inf) puts("0");
            else printf("%d\n",ans[i]);
    }
    return 0;
}

