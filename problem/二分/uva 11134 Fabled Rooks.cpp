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
const int maxn=5000+10;
struct Node
{
    int l,r,id;
    Node(){}
    Node(int l,int r,int id):l(l),r(r),id(id){}
    bool operator <(const Node &a) const
    {
        return r>a.r;
    }
}x[maxn],y[maxn];
int ans[maxn][2],n;
bool cmp(Node a,Node b)
{
    return a.l<b.l;
}
bool solve(Node a[],int type)
{
    sort(a,a+n,cmp);
    priority_queue<Node>q;
    int j=0;
    for(int i=1;i<=n;++i)
    {
        while(a[j].l<=i&&j<n) {q.push(a[j]);j++;}
        if(q.empty()) return false;
        Node nd=q.top();q.pop();
        ans[nd.id][type]=i;
        if(!q.empty()&&q.top().r<=i) return false;
    }
    return true;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        for(int i=0;i<n;++i)
        {
            scanf("%d%d%d%d",&x[i].l,&y[i].l,&x[i].r,&y[i].r);
            x[i].id=y[i].id=i;
        }
        if(solve(x,0)&&solve(y,1))
        {
            for(int i=0;i<n;++i)
                printf("%d %d\n",ans[i][0],ans[i][1]);
        }
        else printf("IMPOSSIBLE\n");
    }
    return 0;
}

