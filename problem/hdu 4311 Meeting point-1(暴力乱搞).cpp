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
struct Point
{
    int x,y,id;
    Point(int x = 0,int y = 0,int id = 0):x(x),y(y),id(id){}
}pt[maxn];
ll ans[maxn];
bool cmp1(Point a,Point b)
{
    return a.x < b.x;
}
bool cmp2(Point a,Point b)
{
    return a.y < b.y;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        memset(ans,0,sizeof(ans));
        int n;
        scanf("%d",&n);
        for(int i = 0;i < n;++i)
        {
            scanf("%d%d",&pt[i].x,&pt[i].y);
            pt[i].id = i;
        }

        ll sum = 0,d;
        sort(pt,pt + n,cmp1);
        for(int i = 1;i < n;++i)
            sum += (ll)pt[i].x - pt[0].x;
        ans[pt[0].id] += sum;
        for(int i = 1;i < n;++i)
        {
            d = (ll)pt[i].x - pt[i-1].x;
            sum += d*i;
            sum -= d*(n - i);
            ans[pt[i].id] += sum;
        }
        sort(pt,pt + n,cmp2);
        sum = 0;
        for(int i = 1;i < n;++i)
            sum += (ll)pt[i].y - pt[0].y;
        ans[pt[0].id] += sum;
        for(int i = 1;i < n;++i)
        {
            d = (ll)pt[i].y - pt[i-1].y;
            sum += d*i;
            sum -= d*(n - i);
            ans[pt[i].id] += sum;
        }
        ll minv = ans[0];
        for(int i = 1;i < n;++i)
            minv = min(minv,ans[i]);
        printf("%I64d\n",minv);
    }
    return 0;
}
