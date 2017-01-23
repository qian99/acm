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
const int maxn = 110;
struct Node
{
    int L,R,id;
    Node(int L = 0,int R = 0,int id = 0):L(L),R(R),id(id){}
    bool operator < (const Node & a) const
    {
        return L > a.L;
    }
}node[maxn],a[maxn];
bool vis[maxn];
map<int,int>mp;
int ans[maxn],tot,n;
int solve(int n)
{
    mp.clear();
    sort(a + 1,a + n + 1);
    bool flag;
    int cnt = 0;
    for(int i = 1;i <= n;++i)
    {
        flag = false;
        for(int j = a[i].R;j >= a[i].L;--j)
        {
            if(mp.find(j) != mp.end()) continue;
            mp[j] = 1;
            flag = true;
            break;
        }
        if(flag) cnt++;
    }
    return cnt;
}
void cal(int pos,int limit)
{
    if(limit > n || pos > tot) return ;
    for(int i = n;i >= limit;--i)
    {
//        if(n - limit + 1 >= tot - i + 1)
//            continue;
        int m = 0;
        for(int j = i;j <= n;++j)
            a[++m] = node[j];
        for(int j = 1;j < pos;++j)
            a[++m] = node[ans[j]];
        if(solve(m) == tot)
        {
            ans[pos] = i;
            cal(pos + 1,i + 1);
            return ;
        }
    }
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(int i = 1;i <= n;++i)
        {
            scanf("%d%d",&node[i].L,&node[i].R);
            node[i].id = i;
        }
        for(int i = 1;i <= n;++i)
            a[i] = node[i];
        tot = solve(n);
        for(int i = n - tot + 1;i >= 1;--i)
        {
            int m = 0;
            for(int j = i;j <= n;++j)
                a[++m] = node[j];
            if(solve(m) == tot)
            {
                ans[1] = i;
                cal(2,i + 1);
                break;
            }
        }
        sort(ans + 1,ans + tot + 1);
        printf("%d\n",tot);
        for(int i = 1;i <= tot;++i)
        {
            if(i > 1) printf(" ");
            printf("%d",ans[i]);
        }
        puts("");
    }
    return 0;
}

