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
const int maxn=1000000+10;
int parent[maxn],val[maxn],xv[maxn],size[maxn];
int Find(int x)
{
    if(x==parent[x]) return x;
    int y=parent[x];
    parent[x]=Find(parent[x]);
    xv[x]^=xv[y];
    val[x]^=xv[y];
    return parent[x];
}
void Uion(int x,int y)
{
    int a=Find(x);
    int b=Find(y);
    if(a!=b)
    {
        if(val[x]==val[y]) xv[b]^=1;
        parent[b]=a;
        size[a]+=size[b];
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    char str[10];
    while(~scanf("%d%d",&n,&m))
    {
        for(int i=1;i<=n;++i)
        {
            parent[i]=parent[i+n]=i+n;
            size[i]=0;size[i+n]=1;
            val[i]=val[i+n]=xv[i]=xv[i+n]=0;
        }
        int tot=n+n,u,v;
        while(m--)
        {
            scanf("%s%d",str,&u);
            if(str[0]=='L')
            {
                scanf("%d",&v);
                Uion(u,v);
            }
            else if(str[0]=='D')
            {
                size[Find(u)]--;
                parent[u]=++tot;
                parent[tot]=tot;
                size[tot]=1;
                val[u]=val[tot]=xv[tot]=0;
            }
            else if(str[0]=='Q')
            {
                scanf("%d",&v);
                int a=Find(u);
                int b=Find(v);
                if(a==b)
                {
                    if(val[u]==val[v]) printf("Same\n");
                    else printf("Different\n");
                }
                else printf("Unknown\n");
            }
            else
                printf("%d\n",size[Find(u)]);
        }
    }
    return 0;
}
