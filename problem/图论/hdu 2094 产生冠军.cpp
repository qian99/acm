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
const int maxn=2000+10;
int degree[maxn];
vector<int>G[maxn];
bool vis[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    map<string,int>mp;
    while(cin>>n)
    {
        if(n==0)break;
        for(int i=0;i<=2*n;++i) G[i].clear();
        memset(degree,0,sizeof(degree));
        memset(vis,0,sizeof(vis));
        m=0;
        string str1,str2;
        mp.clear();
        for(int i=0;i<n;++i)
        {
            cin>>str1>>str2;
            if(!mp[str1]) mp[str1]=++m;
            if(!mp[str2]) mp[str2]=++m;
            G[mp[str1]].push_back(mp[str2]);
            degree[mp[str2]]++;
        }
        int cnt=0;
        queue<int>q;
        for(int i=1;i<=m;++i)
          if(!degree[i]) q.push(i),cnt++;
        bool flag=(cnt==1);
        while(!q.empty())
        {
            int u=q.front();q.pop();
            vis[u]=true;
            for(int i=0;i<G[u].size();++i)
            {
                int v=G[u][i];
                degree[v]--;
                if(!degree[v]) q.push(v),cnt++;
            }
        }
        for(int i=1;i<=m;++i) if(!vis[i]&&!degree[i]) flag=false;
        if(flag) puts("Yes");
        else puts("No");
    }
    return 0;
}
