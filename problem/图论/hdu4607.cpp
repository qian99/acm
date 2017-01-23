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
const int maxn=100000+10;
int maxlen;
int ans[maxn],treenode[maxn];
vector<int>G[maxn];
int dfs(int u,int fa,int val)
{
    int aa[3]={0};
    int child=0;
    for(int i=0;i<G[u].size();++i)
    {
        int v=G[u][i];
        if(v!=fa)
        {
            child++;
            int tmp=dfs(v,u,val+1);
            aa[0]=tmp;
            sort(aa,aa+3);
        }
    }
    maxlen=max(maxlen,val+aa[2]);
    maxlen=max(maxlen,aa[1]+aa[2]);
    //if(child==0&&fa>0) return 1;
    return aa[2]+1;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n,m,k;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        for(int i=0;i<=n;++i) G[i].clear();
        maxlen=0;
        //memset(ans,0,sizeof(ans));
        memset(treenode,0,sizeof(treenode));
        int a,b;
        for(int i=0;i<n-1;++i)
        {
            scanf("%d%d",&a,&b);
            treenode[a]++;
            treenode[b]++;
            G[a].push_back(b);
            G[b].push_back(a);
        }
        int s;
        for(int i=1;i<=n;++i)
        {
            if(treenode[i]==1)
            {
                s=i;
                break;
            }
        }
        dfs(s,-1,0);
        int sum=0;
        ans[0]=0;
        ans[1]=0;
        for(int i=2;i<=n;++i)
        {
            if(i-1<=maxlen) sum+=1;
            else sum+=2;
            ans[i]=sum;
        }
        for(int i=0;i<m;++i)
        {
            scanf("%d",&a);
            printf("%d\n",ans[a]);
        }
    }
    return 0;
}