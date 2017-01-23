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
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=6000+10;
struct Node
{
    double val;
    int id;
    Node(){};
    Node(double vv,int ii) {val=vv;id=ii;}
    bool operator <(const Node &a) const
    {
        return val<a.val;
    }
}node[maxn];
int dcmp(double x)
{
    if(fabs(x)<eps) return 0;
    return x>0?1:-1;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;++i)
    {
        scanf("%lf",&node[i].val);
        node[i].val-=2;node[i].id=i+1;
    }
    sort(node,node+n);
    int x,y;
    for(int i=0;i<n;++i)
    {
        if(dcmp(node[i].val)>=0)
        {
            x=i-1;
            y=i;
            break;
        }
    }
    double sum=0;
    printf("yes\n");
    for(int i=0;i<n;++i)
    {
        if(dcmp(sum)>0)
        {
            sum+=node[x].val;
            printf("%d ",node[x].id);
            x--;
        }
        else
        {
            sum+=node[y].val;
            printf("%d ",node[y].id);
            y++;
        }
    }
    return 0;
}

