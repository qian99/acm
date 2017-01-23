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
const int maxn=100000+10;
struct Node
{
    int d,t;
    bool operator < (const Node &a ) const
    {
        return t>a.t;
    }
};
Node node[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int T,n,tcase=0;
    scanf("%d",&T);
    while(T--)
    {
        tcase++;
        scanf("%d",&n);
        for(int i=0;i<n;++i)
           scanf("%d%d",&node[i].d,&node[i].t);
        sort(node,node+n);
        int nowt=0,res=0;
        for(int i=0;i<n;++i)
        {
            res=max(res,nowt+node[i].d+node[i].t);
            nowt+=node[i].d;
        }
        printf("Case %d: %d\n",tcase,res);
    }
    return 0;
}
