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
int rank[maxn],degree[maxn];
vector<int>G[maxn];
void find_ans(int n)
{
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(degree[j]==0)
            {
                rank[i]=j;
                degree[j]--;
                for(int k=0;k<G[j].size();++k)
                    degree[G[j][k]]--;
                break;
            }
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        for(int i=0;i<=n;++i) G[i].clear();
        memset(degree,0,sizeof(degree));
        int a,b;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&a,&b);
            degree[b]++;
            G[a].push_back(b);
        }
        find_ans(n);
        printf("%d",rank[1]);
        for(int i=2;i<=n;++i)
          printf(" %d",rank[i]);
        printf("\n");
    }
    return 0;
}
