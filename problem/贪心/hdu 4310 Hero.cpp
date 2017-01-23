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
struct Node
{
    double dps,hp;
    bool operator <(const Node &a) const
    {
        return (a.dps/a.hp)<(dps/hp);
    }
};
Node node[50];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        for(int i=0;i<n;++i)
         scanf("%lf%lf",&node[i].dps,&node[i].hp);
        sort(node,node+n);
        int sum=0,cnt=0;
        for(int i=0;i<n;++i)
        {
            sum+=node[i].dps*node[i].hp+node[i].dps*cnt;
            cnt+=node[i].hp;
        }
        printf("%d\n",sum);
    }
    return 0;
}
