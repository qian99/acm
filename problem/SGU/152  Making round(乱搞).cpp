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
const int maxn=10000+10;
struct Node
{
    double val;
    int id;
    bool operator <(const Node &a) const
    {
        return val>a.val;
    }
}node[maxn];
int res[maxn],num[maxn];
int dcmp(double x)
{
    if(fabs(x)<eps) return 0;
    return x>0?1:-1;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,sum=0,total=0;
    double tmp;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&num[i]);
        total+=num[i];
    }
    for(int i=1;i<=n;++i)
    {
        if(num[i]==0) res[i]=0,node[i].val=0;
        else
        {
            tmp=(double)num[i]/total*100+eps;
            res[i]=(int)tmp;
            node[i].val=tmp-res[i];
        }
        node[i].id=i;
        sum+=res[i];
    }
    sum=100-sum;
    sort(node+1,node+n+1);
    int i=1;
    while(sum)
    {
        if(dcmp(node[i].val)==0) break;
        res[node[i].id]++;
        i++;
        sum--;
    }
    if(sum)
    {
        printf("No solution\n");
        return 0;
    }
    printf("%d",res[1]);
    for(int i=2;i<=n;++i)
        printf(" %d",res[i]);
    printf("\n");
    return 0;
}
