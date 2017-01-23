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
const int maxn=50000+10;
int pa[maxn],lson[maxn],rson[maxn];
int conv[maxn];
struct Node
{
    int id,va,vb;
    bool operator <(const Node &a) const
    {
        return va<a.va;
    }
}node[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    memset(pa,0,sizeof(pa));
    memset(lson,0,sizeof(lson));
    memset(rson,0,sizeof(rson));
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&node[i].va,&node[i].vb);
        node[i].id=i;
    }
    sort(node+1,node+n+1);
    conv[node[1].id]=1;
    stack<int>S;
    S.push(1);
    for(int i=2;i<=n;++i)
    {
        conv[node[i].id]=i;
        int fp=0,sp=0;
        while(!S.empty())
        {
            int tmp=S.top();
            if(node[tmp].vb<node[i].vb)
            {
                fp=tmp;
                break;
            }
            else
            {
                sp=tmp;
                S.pop();
            }
        }
        pa[i]=fp;
        rson[fp]=i;
        lson[i]=sp;
        pa[sp]=i;
        S.push(i);
    }
    printf("YES\n");
    for(int i=1;i<=n;++i)
    {
        int p=conv[i];
        printf("%d %d %d\n",node[pa[p]].id,node[lson[p]].id,node[rson[p]].id);
    }
    return 0;
}
