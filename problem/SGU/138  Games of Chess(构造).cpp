#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100+10;
const int maxm=10000+10;
struct Node
{
    int u,degree;
    bool operator <(const Node & a) const
    {
        return degree>a.degree;
    }
}node[maxn];
int ans[maxm][2];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,sum=0;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&node[i].degree);
        node[i].u=i;
        sum+=node[i].degree;
    }
    sort(node+1,node+n+1);
    memset(ans,0,sizeof(ans));
    sum/=2;
    printf("%d\n",sum);
    int m=0;
    for(int i=1;i<=n;++i)
    {
        while(m<sum&&node[i].degree>1)
        {
            ans[m++][0]=node[i].u;
            node[i].degree--;
        }
        if(m<sum)
        {
            ans[m][0]=node[i+1].u;
            ans[m][1]=node[i].u;
            m++;
            node[i].degree--;
            node[i+1].degree--;
        }
    }
    int s=0;
    while(!node[s].degree) s++;
    for(int i=0;i<m;++i)
    {
        printf("%d ",ans[i][0]);
        if(ans[i][1]) printf("%d\n",ans[i][1]);
        else
        {
            printf("%d\n",node[s].u);
            node[s].degree--;
            while(!node[s].degree) s++;
        }
    }
    return 0;
}
