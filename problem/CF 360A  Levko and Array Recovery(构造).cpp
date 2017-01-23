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
#include<set>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=5000+10;
int n,m;
struct Node
{
    int type,L,R,v;
}node[maxn];
int a[maxn],b[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;++i)
        scanf("%d%d%d%d",&node[i].type,&node[i].L,&node[i].R,&node[i].v);
    for(int i=1;i<=n;++i) a[i]=inf;
    for(int i=m-1;i>=0;--i)
    {
        if(node[i].type==2)
        {
            for(int j=node[i].L;j<=node[i].R;j++)
                if(a[j]==inf||a[j]>node[i].v)
                    a[j]=node[i].v;
        }
        else
        {
            for(int j=node[i].L;j<=node[i].R;++j)
                if(a[j]!=inf) a[j]-=node[i].v;
        }
    }
    for(int i=1;i<=n;++i)
    {
        if(a[i]==inf) a[i]=1;
        b[i]=a[i];
    }
    bool flag=true;
    for(int i=0;i<m;++i)
    {
        if(node[i].type==1)
        {
            for(int j=node[i].L;j<=node[i].R;++j)
                b[j]+=node[i].v;
        }
        else
        {
            int tmp=-inf;
            for(int j=node[i].L;j<=node[i].R;++j)
                tmp=max(tmp,b[j]);
            if(tmp!=node[i].v) {flag=false;break;}
        }
    }
    if(flag)
    {
        puts("YES");
        printf("%d",a[1]);
        for(int i=2;i<=n;++i)
            printf(" %d",a[i]);
        printf("\n");
    }
    else puts("NO");
    return 0;
}