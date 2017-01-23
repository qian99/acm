#include <iostream>
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
const int maxn=500+10;
struct Node
{
    string x,y;
};
Node clover[maxn],dlover[maxn];
vector<int>G[maxn];
int link[maxn];
bool vis[maxn];
bool dfs(int u)
{
    for(int i=0;i<G[u].size();++i)
    {
        int v=G[u][i];
        if(!vis[v])
        {
            vis[v]=true;
            if(link[v]==-1||dfs(link[v]))
            {
                link[v]=u;
                return true;
            }
        }
    }
    return false;
}
int hungary(int n)
{
    int ret=0;
    memset(link,0xff,sizeof(link));
    for(int i=1;i<=n;++i)
    {
        memset(vis,0,sizeof(vis));
        if(dfs(i)) ret++;
    }
    return ret;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    cin>>t;
    while(t--)
    {
        int c,d,v;
        cin>>c>>d>>v;
        for(int i=1;i<=v;++i) G[i].clear();
        int m1=0,m2=0;
        string a,b;
        for(int i=0;i<v;++i)
        {
            cin>>a>>b;
            if(a[0]=='C') clover[m1++]=(Node){a,b};
            else dlover[m2++]=(Node){a,b};
        }
        for(int i=0;i<m1;++i)
        {
            for(int j=0;j<m2;++j)
            {
                if(clover[i].x==dlover[j].y||clover[i].y==dlover[j].x)
                   G[i+1].push_back(j+1);
            }
        }
        printf("%d\n",v-hungary(m1));
    }
    return 0;
}
