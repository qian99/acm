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
const int maxn=300+10;
struct Node
{
    int fc,lc;
}node[maxn];
char str[maxn];
bool vis[30];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        for(int i=0;i<n;++i)
        {
            scanf("%s",str);
            node[i].fc=str[0]-'A';
            scanf("%s",str);
            node[i].lc=str[0]-'A';
        }
        int ans=inf;
        int N=1<<18,tmp,x;
        for(int i=0;i<N;++i)
        {
            tmp=0;x=i;
            while(x)
            {
                x=x&(x-1);
                tmp++;
            }
            if(tmp>ans) continue;
            memset(vis,0,sizeof(vis));
            for(int j=0;j<n;++j)
            {
                if(i&(1<<node[j].lc)) continue;
                if(!vis[node[j].fc])
                {
                    vis[node[j].fc]=true;
                    tmp++;
                    if(tmp>ans) break;
                }
            }
            if(tmp<ans) ans=tmp;
        }
        printf("%d\n",ans);
    }
    return 0;
}
