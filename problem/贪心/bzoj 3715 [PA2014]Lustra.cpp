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
    int w1,w2,h1,h2;
    Node(int w1 = 0,int w2 = 0,int h1 = 0,int h2 = 0):w1(w1),w2(w2),h1(h1),h2(h2){}
    bool operator < (const Node & a) const
    {
        if(w2 != a.w2) return w2 < a.w2;
        if(h2 != a.h2) return h2 < a.h2;
        if(w1 != a.w1) return w1 > a.w1;
        return h1 > a.h1;
    }
}node[maxn];
inline bool check(Node a,Node b)
{
    return b.h1 <= a.h1 && b.h2 >= a.h2 && b.w1 <= a.w1 && b.w2 >= a.w2;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n;
        scanf("%d",&n);
        for(int i = 0;i < n;++i)
        {
            scanf("%d%d%d%d",&node[i].w1,&node[i].w2,&node[i].h1,&node[i].h2);
        }
        sort(node,node + n);
        bool flag = true;
        for(int i = 0;i < n - 1;++i)
        {
            if(!check(node[i],node[n - 1]))
            {
                flag = false;
                break;
            }
        }
        if(flag)
            puts("TAK");
        else
            puts("NIE");
    }
    return 0;
}
