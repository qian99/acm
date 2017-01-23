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
int parents[maxn],sex[maxn];
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
   }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        int n,m;
        scanf("%d%d",&n,&m);
        for(int i=0;i<=n;++i) parents[i]=i,sex[i]=0;
        int a,b;
        bool flag=true;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&a,&b);
            if(!flag) continue;
            if(Find(a)==Find(b)) flag=false;
            if(sex[a]==0) sex[a]=b;
            if(sex[b]==0) sex[b]=a;
            Uion(sex[a],b);
            Uion(sex[b],a);
        }
        printf("Scenario #%d:\n",tcase);
        if(flag)
          printf("No suspicious bugs found!\n\n");
        else
          printf("Suspicious bugs found!\n\n");
    }
    return 0;
}
