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
#define inf 2139062143
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
const int maxn=10000+10;
int parents[maxn],sum[maxn];
bool isring[maxn];
int x1[maxn],c1[maxn],x2[maxn],c2[maxn];
int Find(int x)
{
    return x==parents[x]?x:parents[x]=Find(parents[x]);
}
void Uion(int x,int y)
{
    int a=Find(x);
    int b=Find(y);
    if(a!=b)
    {
        parents[b]=a;
        sum[a]+=sum[b];
        sum[b]=0;
    }
    else
        isring[a]=true;
}
void work(int n,int m,int *x,int *c)
{
    for(int i=0;i<=n;++i)
    {
        parents[i]=i;
        sum[i]=1;
        isring[i]=false;
    }
    int u,v;
    for(int i=0;i<m;++i)
    {
        scanf("%d%d",&u,&v);
        Uion(u,v);
    }
    x[0]=c[0]=0;
    for(int i=1;i<=n;++i)
    {
        if(sum[i])
        {
            if(isring[i]) c[++c[0]]=sum[i];
            else x[++x[0]]=sum[i];
        }
    }
    sort(c+1,c+c[0]+1);
    sort(x+1,x+x[0]+1);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        int n,m;
        tcase++;
        scanf("%d%d",&n,&m);
        work(n,m,x1,c1);
        scanf("%d%d",&n,&m);
        work(n,m,x2,c2);
        bool flag=true;
        if(c1[0]==c2[0]&&x1[0]==x2[0])
        {
            for(int i=1;i<=c1[0];++i)
            {
                if(c1[i]!=c2[i])
                {
                    flag=false;
                    break;
                }
            }
            for(int i=1;i<=x1[0];++i)
            {
                if(x1[i]!=x2[i])
                {
                    flag=false;
                    break;
                }
            }
        }
        else flag=false;
        printf("Case #%d: ",tcase);
        if(flag) printf("YES\n");
        else printf("NO\n");

    }
    return 0;
}
