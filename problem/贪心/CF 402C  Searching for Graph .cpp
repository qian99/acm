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
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=50+10;
struct Node
{
    int u,d;
    Node(){}
    Node(int u,int d):u(u),d(d) {}
    bool operator <(const Node &a) const
    {
        return d>a.d;
    }
}S[maxn];
int g[maxn][maxn];
int cnt;
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n,p;
        scanf("%d%d",&n,&p);
        int tot=2*n+p;
        memset(g,0,sizeof(g));
        priority_queue<Node>q;
        for(int i=1;i<=n;++i)
            q.push(Node(i,0));
        Node tmp;
        while(tot--)
        {
            cnt=0;
            S[cnt++]=q.top();q.pop();
            while(true)
            {
                tmp=q.top();q.pop();
                bool flag=false;
                for(int i=0;i<cnt;++i)
                {
                    if(g[tmp.u][S[i].u]) continue;
                    flag=true;
                    g[tmp.u][S[i].u]=g[S[i].u][tmp.u]=1;
                    tmp.d++;S[i].d++;
                    S[cnt++]=tmp;
                    break;
                }
                if(!flag) S[cnt++]=tmp;
                else break;
            }
            for(int i=0;i<cnt;++i)
                q.push(S[i]);
        }
        for(int i=1;i<=n;++i)
            for(int j=i+1;j<=n;++j)
                if(g[i][j])
                    printf("%d %d\n",i,j);
    }
    return 0;
}
