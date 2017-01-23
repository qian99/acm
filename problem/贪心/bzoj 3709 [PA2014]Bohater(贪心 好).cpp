#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<set>
#include<cmath>
#include<vector>
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 100000 + 10;
struct Node
{
    int x,y,id;
    Node(int x = 0,int y = 0,int id = 0):x(x),y(y),id(id){}
}na[maxn],nb[maxn];
int ans[maxn];
bool vis[maxn];
bool cmp1(Node a,Node b)
{
    return a.x < b.x;
}
bool cmp2(Node a,Node b)
{
    return a.y > b.y;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n;
    ll hp;
    while(~scanf("%d%lld",&n,&hp))
    {
        int m1 = 0,m2 = 0;
        int x,y;
        for(int i = 1;i <= n;++i)
        {
            scanf("%d%d",&x,&y);
            if(x <= y)
                na[m1++] = Node(x,y,i);
            else
                nb[m2++] = Node(x,y,i);
        }
        sort(na,na + m1,cmp1);
        sort(nb,nb + m2,cmp2);
        memset(vis,0,sizeof(vis));
        int tot = 0;
        for(int i = 0;i < m1;++i)
        {
            if(hp > na[i].x)
            {
                hp += na[i].y - na[i].x;
                ans[tot++] = na[i].id;
            }
            else
                break;
        }
        for(int i = 0;i < m2;++i)
        {
            if(hp > nb[i].x)
            {
                hp += nb[i].y - nb[i].x;
                ans[tot++] = nb[i].id;
            }
            else
                break;
        }
        if(tot != n)
            printf("NIE\n");
        else
        {
            puts("TAK");
            for(int i = 0;i < tot;++i)
            {
                if(i) printf(" ");
                printf("%d",ans[i]);
            }
            puts("");
        }
    }
    return 0;
}
