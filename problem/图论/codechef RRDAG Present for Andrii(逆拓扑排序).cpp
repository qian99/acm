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
const int maxn = 1500 + 10;
char mat[maxn][maxn];
bool a[maxn][maxn];
int degree[maxn];
vector<int>g;
priority_queue<int>q;
vector<pair<int,int> > ans;
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        memset(degree,0,sizeof(degree));
        memset(a,0,sizeof(a));
        for(int i = 0;i < n;++i)
        {
            scanf("%s",mat[i]);
            for(int j = 0;j < n;++j)
            {
                if(mat[i][j] == '1')
                {
                    degree[i]++;
                    a[j][i] = true;
                }
            }
        }
        while(!q.empty()) q.pop();
        for(int i = 0;i < n;++i)
            if(degree[i] == 0)
                q.push(i);
        g.clear();
        while(!q.empty())
        {
            int u = q.top();q.pop();
            g.push_back(u);
            for(int i = 0;i < n;++i)
            {
                if(u == i) continue;
                if(a[u][i])
                {
                    degree[i]--;
                    if(degree[i] == 0)
                        q.push(i);
                }
            }
        }
        reverse(g.begin(),g.end());
        ans.clear();
        for(int i = 0;i < n;++i)
            for(int j = i + 1;j < n;++j)
                if(!a[g[j]][g[i]])
                    ans.push_back(make_pair(g[i] + 1,g[j] + 1));
        sort(ans.begin(),ans.end());
        int tot = ans.size();
        printf("%d\n",tot);
        for(int i = 0;i < tot;++i)
            printf("%d %d\n",ans[i].first,ans[i].second);
    }
    return 0;
}
