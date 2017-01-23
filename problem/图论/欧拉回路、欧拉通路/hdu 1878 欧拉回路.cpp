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
int parents[maxn],du[maxn];
int sum;
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
        sum++;
        parents[b]=a;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        scanf("%d",&m);
        for(int i=1;i<=n;++i) parents[i]=i;
        memset(du,0,sizeof(du));
        int x,y;
        sum=0;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&x,&y);
            Uion(x,y);
            du[x]++;
            du[y]++;
        }
        bool flag=true;
        for(int i=1;i<=n;++i)
        {
            if(du[i]%2!=0)
            {
                flag=false;
                break;
            }
        }
        flag=flag&&(n==sum+1);
        if(flag)
          printf("1\n");
        else
          printf("0\n");
    }
    return 0;
}
