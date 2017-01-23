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
const int maxn=10000+10;
struct Node
{
    int px,dx;
    bool operator < (const Node &a) const
    {
        return px>a.px;
    }
};
int pre[maxn];
Node node[maxn];
int Find(int x)
{
    return x==pre[x]?x:pre[x]=Find(pre[x]);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        for(int i=0;i<maxn;++i) pre[i]=i;
        for(int i=0;i<n;++i)
          scanf("%d%d",&node[i].px,&node[i].dx);
        sort(node,node+n);
        int sum=0,tmp;
        for(int i=0;i<n;++i)
        {
            tmp=Find(node[i].dx);
            if(tmp==0) continue;
            tmp=pre[node[i].dx];
            sum+=node[i].px;
            pre[tmp]=pre[tmp-1];
        }
        printf("%d\n",sum);
    }
    return 0;
}
