#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=15000+10;
struct Node
{
    int id,r;
    bool operator <(const Node & a) const
    {
        return r>a.r;
    }
};
int sum[maxn],p[maxn],w[maxn],l[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    scanf("%d",&n);
    priority_queue<Node>q;
    for(int i=1;i<=n;++i)
      scanf("%d%d%d",&w[i],&l[i],&p[i]);
    sum[n+1]=0;
    for(int i=n;i>=1;i--)
      sum[i]=sum[i+1]+w[i];
    int cost=0,pos;
    int minval=inf;
    Node node;
    for(int i=n;i>=1;--i)
    {
        while(!q.empty())
        {
            node=q.top();
            if(sum[i]-node.r>0)
            {
                q.pop();
                cost-=p[node.id];
            }
            else break;
        }
        cost+=p[i];
        if(cost<minval)
        {
            minval=cost;
            pos=i;
        }
        node.id=i;
        node.r=l[i]-w[i]+sum[i];
        q.push(node);
    }
    cost=0;
    for(int i=pos;i<=n;i++)
    {
        cost+=w[i];
        if(cost<=l[i])
        {
            printf("%d\n",i);
        }
    }
    return 0;
}
