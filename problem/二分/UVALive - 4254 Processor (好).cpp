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
const int maxn=20000+10;
struct Node
{
    int l,r,w;
    Node(){}
    Node(int l,int r,int w):l(l),r(r),w(w){}
    bool operator <(const Node &a) const
    {
        return r>a.r;
    }
}node[maxn];
bool cmp(Node a,Node b) { return a.l<b.l; }
int n;
bool check(int speed)
{
    priority_queue<Node>q;
    Node nd;
    int i=0,nowtime=0,tot;
    while(true)
    {
        while(node[i].l<=nowtime&&i<n) {q.push(node[i]);i++;}
        tot=speed;
        while(!q.empty()&&tot)
        {
            nd=q.top();q.pop();
            int tmp=min(tot,nd.w);
            tot-=tmp;nd.w-=tmp;
            if(nd.w) q.push(nd);
        }
        nowtime++;
        if(!q.empty()&&q.top().r<=nowtime) return false;
        if(q.empty()&&i==n) break;
    }
    return true;
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
        int L=1,R=0;
        for(int i=0;i<n;++i)
        {
            scanf("%d%d%d",&node[i].l,&node[i].r,&node[i].w);
            R+=node[i].w;
        }
        sort(node,node+n,cmp);
        while(L<R)
        {
            int m=(L+R)>>1;
            if(check(m)) R=m;
            else L=m+1;
        }
        printf("%d\n",L);
    }
    return 0;
}

