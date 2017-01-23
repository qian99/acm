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
const int maxn=300000+10;
const int maxm=20000001;
int post[maxn],pre[maxm],child[maxn],parent[maxm],num[maxn],dfs_clock;
int n;
void Init()
{
    scanf("%d",&n);
    int ff=1;
    for(int i=0;i<n;++i)
    {
        scanf("%d",&num[i]);
        child[i]=ff;
        ff+=num[i];
        for(int j=0;j<num[i];++j)
            parent[child[i]+j]=i;
    }
}
void dfs()
{
    int node=0;
    int visited=0;
    dfs_clock=0;
    while(true)
    {
        if(!visited)
        {
            pre[node]=dfs_clock++;
            if(num[node])
            {
                if(child[node]<n)
                   node=child[node];
                else
                {
                    for(int i=0;i<num[node];++i)
                    {
                        pre[child[node]+i]=dfs_clock;
                        dfs_clock+=2;
                    }
                    visited=1;
                }
            }
            else visited=1;
        }
        else
        {
            post[node]=dfs_clock++;
            if(node==0) break;
            int p=parent[node];
            if(node<child[p]+num[p]-1)
            {
                ++node;
                visited=0;
                if(node>=n)
                {
                    for(;node<child[p]+num[p];node++,dfs_clock+=2)
                        pre[node]=dfs_clock;
                    node=p;
                    visited=1;
                }
            }
            else
              node=p;
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,m,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        Init();
        dfs();
        if(tcase>1) printf("\n");
        printf("Case %d:\n",tcase);
        scanf("%d",&m);
        int a,b;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&a,&b);
            if(a>=n||a==b)
            {
                printf("No\n");
                continue;
            }
            int leave=(b<n?post[b]:pre[b]+1);
            if(pre[a]<pre[b]&&leave<post[a])
              printf("Yes\n");
            else
              printf("No\n");
        }
    }
    return 0;
}
