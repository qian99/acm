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
    int pos,l,r,gval;
    Node(int pos = 0,int l = 0,int r = 0,int gval = 0):pos(pos),l(l),r(r),gval(gval){}
    bool operator < (const Node & a) const
    {
        if(gval != a.gval) return gval < a.gval;
        if(pos != a.pos) return pos < a.pos;
        return r < a.r;
    }
}node[maxn*20];
int gcd(int a,int b) { return b == 0?a:gcd(b,a%b);}
vector<Node>vt[maxn];
int a[maxn],n;
map<int,ll>mp;
void precal()
{
    mp.clear();
    for(int i = 0;i <= n;++i) vt[i].clear();
    vt[n].push_back(Node(n,n,n,a[n]));
    Node ntmp;
    int x;
    for(int i = n - 1;i >= 1;--i)
    {
        int size = vt[i + 1].size();
        int cnt = 1;
        vt[i].push_back(Node(i,i,i,a[i]));
        for(int j = 0;j < size;++j)
        {
            ntmp = vt[i+1][j];
            x = gcd(a[i],ntmp.gval);
            if(cnt && vt[i][cnt-1].gval == x)
                vt[i][cnt - 1].r = ntmp.r;
            else
                vt[i].push_back(Node(i,ntmp.l,ntmp.r,x)),cnt++;
        }
    }
    for(int i = 1;i <= n;++i)
        for(int j = 0;j < (int)vt[i].size();++j)
        {
            ntmp = vt[i][j];
            mp[ntmp.gval] += (ntmp.r - ntmp.l + 1);
        }
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    scanf("%d",&n);
    for(int i = 1;i <= n;++i)
        scanf("%d",&a[i]);
    precal();
    int m,x;
    scanf("%d",&m);
    while(m--)
    {
        scanf("%d",&x);
        printf("%I64d\n",mp[x]);
    }
    return 0;
}