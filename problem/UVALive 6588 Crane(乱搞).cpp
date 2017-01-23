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
const int maxn = 10000 + 10;
int a[maxn],p[maxn],n;
vector<pair<int,int> >ans;
void SWAP(int x,int y,int len)
{
    if(len == 1)
    {
        p[a[x]] = y;
        p[a[y]] = x;
        swap(a[x],a[y]);
        ans.push_back(make_pair(x,y));
    }
    else
    {
        ans.push_back(make_pair(x + 1,y + len - 2));
        ans.push_back(make_pair(x,x + 1));
        ans.push_back(make_pair(x + 1,y + len - 2));
        p[a[x]] = y;
        p[a[y]] = x;
        swap(a[x],a[y]);
    }
}
void solve(int val)
{
    if(a[val] == val) return ;
    int s,t,len;
    s = val; t = p[val];
    len = t - s;
    while(t + len - 2 > n)
    {
        len = n - t + 1;
        SWAP(t - len - 1,t,len + 1);
        t = t - len - 1;
        len = t - s;
    }
    SWAP(s,t,len);
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
            scanf("%d",&a[i]);
            p[a[i]] = i;
        }
        ans.clear();
        for(int i = 1;i <= n;++i)
            solve(i);
        printf("%d\n",(int)ans.size());
        for(int i = 0;i < (int)ans.size();++i)
            printf("%d %d\n",ans[i].first,ans[i].second);
    }
    return 0;
}

