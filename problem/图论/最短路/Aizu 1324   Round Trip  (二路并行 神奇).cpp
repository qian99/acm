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
const int maxn=55;
const int maxm=1024;
struct Node
{
    int d,u1,u2,state;
    Node(){}
    Node(int d,int u1,int u2,int state):d(d),u1(u1),u2(u2),state(state){}
    bool operator <(const Node &a) const
    {
        return d>a.d;
    }
};
vector<pair<int,int> >Go[maxn];
vector<pair<int,int> >Back[maxn];
int h[maxn],msk[maxn],cnt[maxm],val[maxn];
int d[maxn][maxn][maxm];
void Init(int n)
{
    memset(msk,0,sizeof(msk));
    memset(cnt,0,sizeof(cnt));
    for(int i=0;i<=n;++i)
    {
        Go[i].clear();
        Back[i].clear();
    }
}
int solve(int n)
{
    priority_queue<Node>q;
    memset(d,0x3f,sizeof(d));
    d[1][1][1]=0;
    q.push(Node(0,1,1,1));
    Node node;
    int u1,u2,st;
    while(!q.empty())
    {
        node=q.top();q.pop();
        u1=node.u1;u2=node.u2;
        st=node.state;
        if(d[u1][u2][st]<node.d) continue;
        if(h[u1]<=h[u2])
        {
            for(int i=0;i<(int)Go[u1].size();i++)
            {
                int v=Go[u1][i].first;
                int nowst=1<<msk[v],cost=node.d+Go[u1][i].second;
                if(h[v]>h[u2])
                {
                    nowst=1<<msk[u2];
                    if(h[u1]==h[u2]) nowst|=st;
                }
                else if(h[v]==h[u2]) nowst|=(1<<msk[u2]);
                if(h[u1]==h[v]) nowst|=st;
                if(!(h[v]==h[u1]&&(st>>msk[v]&1))&&v!=u2) cost+=val[v];
                if(d[v][u2][nowst]>cost)
                {
                    d[v][u2][nowst]=cost;
                    q.push(Node(cost,v,u2,nowst));
                }
            }
        }
        else
        {
            for(int i=0;i<(int)Back[u2].size();++i)
            {
                int v=Back[u2][i].first;
                int nowst=1<<msk[v],cost=node.d+Back[u2][i].second;
                if(h[v]>h[u1])
                {
                    nowst=1<<msk[u1];
                    if(h[u1]==h[u2]) nowst|=st;
                }
                else if(h[v]==h[u1]) nowst|=(1<<msk[u1]);
                if(h[u2]==h[v]) nowst|=st;
                if(!(h[v]==h[u2]&&(st>>msk[v]&1))&&v!=u1) cost+=val[v];
                if(d[u1][v][nowst]>cost)
                {
                    d[u1][v][nowst]=cost;
                    q.push(Node(cost,u1,v,nowst));
                }
            }
        }
    }
    int ans=inf;
    for(int i=0;i<maxm;++i) ans=min(ans,d[n][n][i]);
    return ans==inf?-1:ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        if(n==0&&m==0) break;
        Init(n);
        for(int i=2;i<n;++i)
        {
            scanf("%d%d",&val[i],&h[i]);
            msk[i]=cnt[h[i]]++;
        }
        h[1]=0;h[n]=1000;
        val[1]=val[n]=0;
        msk[1]=cnt[h[1]]++;
        msk[n]=cnt[h[n]]++;
        int u,v,w;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            if(h[u]<=h[v]) Go[u].push_back(make_pair(v,w));
            if(h[u]>=h[v]) Back[v].push_back(make_pair(u,w));
        }
        int ans=solve(n);
        printf("%d\n",ans);
    }
    return 0;
}
