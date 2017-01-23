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
const int maxn=2000000+10;
struct Node
{
    int val,type;
    bool operator <(const Node &a )const
    {
        return (val==a.val&&type<a.type)||(val<a.val);
    }
}node[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int tcase=0,n;
    while(~scanf("%d",&n))
    {
        if(n==-1) break;
        tcase++;
        int tot=0,x,y;
        for(int i=0;i<n;++i)
        {
            scanf("%d%d",&x,&y);
            node[tot].val=x;node[tot++].type=0;
            node[tot].val=y;node[tot++].type=1;
        }
        sort(node,node+tot);
        int ans=0,cnt=0;
        for(int i=0;i<tot;++i)
        {
            if(node[i].type==0)
                cnt++;
            else cnt--;
            ans=max(ans,cnt);
        }
        printf("Case %d: %d\n",tcase,ans);
    }
    return 0;
}

