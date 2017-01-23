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
const int maxn=1000+10;
int manorder[maxn][maxn],womanrank[maxn][maxn],next[maxn];
int husband[maxn],wife[maxn],n;
queue<int>q;
void engage(int man,int woman)
{
    if(husband[woman])
    {
        int x=husband[woman];
        wife[x]=0;
        q.push(x);
    }
    husband[woman]=man;
    wife[man]=woman;
}
void find()
{
    memset(husband,0,sizeof(husband));
    memset(wife,0,sizeof(wife));
    for(int i=1;i<=n;++i)
       q.push(i);
    while(!q.empty())
    {
        int x=q.front();q.pop();
        int target=manorder[x][next[x]++];
        if(!husband[target]) engage(x,target);
        else if(womanrank[target][husband[target]]>womanrank[target][x])
           engage(x,target);
        else q.push(x);
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        int temp;
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=n;++j)
               scanf("%d",&manorder[i][j]);
            next[i]=1;
        }
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=n;++j)
            {
                scanf("%d",&temp);
                womanrank[i][temp]=j;
            }
        }

        find();
        for(int i=1;i<=n;++i)
            printf("%d\n",wife[i]);
    }
    return 0;
}
