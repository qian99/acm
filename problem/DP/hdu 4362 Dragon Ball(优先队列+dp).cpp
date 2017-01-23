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
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxm=55;
const int maxn=1000+10;
int dp[maxm][maxn];
struct Node
{
    int pos,cost;
    Node(int pos=0,int cost=0):pos(pos),cost(cost){}
    bool operator <(const Node &a) const
    {
        return pos<a.pos;
    }
}node[maxm][maxn];
struct Data
{
    int val,id;
    Data(int val=0,int id=0):val(val),id(id){}
    bool operator <(const Data &a) const
    {
        return val>a.val;
    }
};
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,m,n,x;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d",&m,&n,&x);
        for(int i=1;i<=m;++i)
            for(int j=1;j<=n;++j)
                scanf("%d",&node[i][j].pos);
        for(int i=1;i<=m;++i)
            for(int j=1;j<=n;++j)
                scanf("%d",&node[i][j].cost);
        for(int i=1;i<=m;++i)
            sort(node[i]+1,node[i]+n+1);
        memset(dp,0x3f,sizeof(dp));
        for(int i=1;i<=n;++i) node[0][i]=Node(inf,inf);
        dp[0][1]=0;
        node[0][1]=Node(x,0);
        for(int i=1;i<=m;++i)
        {
            priority_queue<Data>ql,qr;
            int last=0,addl=0;
            Data tmp;
            for(int j=1;j<=n;++j)
            {
                if(node[i-1][j].pos<=node[i][1].pos)
                {
                    ql.push(Data(dp[i-1][j]+node[i][1].pos-node[i-1][j].pos,j));
                    last=j;
                }
                else
                    qr.push(Data(dp[i-1][j]+node[i-1][j].pos-node[i][1].pos,j));
            }
            for(int j=1;j<=n;++j)
            {
                if(!ql.empty())
                {
                    tmp=ql.top();
                    dp[i][j]=tmp.val+node[i][j].cost+addl;
                }
                while(!qr.empty())
                {
                    tmp=qr.top();
                    if(tmp.id<=last) {qr.pop();continue;}
                    dp[i][j]=min(dp[i][j],dp[i-1][tmp.id]+node[i-1][tmp.id].pos-node[i][j].pos+node[i][j].cost);
                    break;
                }
                addl+=node[i][j+1].pos-node[i][j].pos;
                while(last+1<=n&&node[i-1][last+1].pos<=node[i][j+1].pos)
                {
                    ql.push(Data(dp[i-1][last+1]+node[i][j+1].pos-node[i-1][last+1].pos-addl,last+1));
                    last++;
                }
            }
        }
        int ans=inf;
        for(int i=1;i<=n;++i)
            ans=min(ans,dp[m][i]);
        printf("%d\n",ans);
    }
    return 0;
}
