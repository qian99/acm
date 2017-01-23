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
const int maxn = 300 + 10;
const int mod = 10007;
struct Point
{
    int x,y;
    Point(int x = 0,int y = 0):x(x),y(y){}
}pt[maxn];
int gcd(int a,int b) { return b == 0 ? a : gcd(b,a%b);}
map<pair<int,int>,int>mp;
int g[maxn][maxn],d[maxn][maxn],inv[mod + 100];
inline int dis(Point a,Point b)
{
    return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}
pair<int,int> getk(int x,int y)
{
    if(x == 0)
    {
        y /= abs(y);
        return make_pair(x,y);
    }
    if(y == 0)
    {
        x /= abs(x);
        return make_pair(x,y);
    }
    int z = gcd(x,y);
    z = abs(z);
    return make_pair(x/z,y/z);
}
int pow_mod(int x,int n)
{
    int res = 1;
    x %= mod;
    while(n)
    {
        if(n & 1) res = res*x%mod;
        x = x*x%mod;
        n >>= 1;
    }
    return res;
}
int det(int n)
{
    int res = 1;
    for(int i = 0;i < n;++i)
    {
        for(int j = i;j < n;++j)
        {
            if(g[j][i])
            {
                for(int k = i;k < n;++k)
                    swap(g[i][k],g[j][k]);
                if(i != j)
                    res = (-res + mod)%mod;
                break;
            }
        }
        if(g[i][i] == 0)
            return -1;
        for(int j = i + 1;j < n;++j)
        {
            if(g[j][i] == 0) continue;
            int mul = g[j][i]*inv[g[i][i]]%mod;
            mul = (mod - mul)%mod;
            for(int k = i;k < n;++k)
                g[j][k] = ((g[j][k] + mul*g[i][k]%mod)%mod + mod)%mod;
        }
        res = res*g[i][i]%mod;
    }
    return res;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    for(int i = 0;i < mod;++i)
        inv[i] = pow_mod(i,mod - 2);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n,R;
        scanf("%d%d",&n,&R);
        for(int i = 0;i < n;++i)
            scanf("%d%d",&pt[i].x,&pt[i].y);
        memset(g,0,sizeof(g));
        memset(d,0,sizeof(d));
        int x,y;
        pair<int,int>val;
        for(int i = 0;i < n;++i)
        {
            mp.clear();
            for(int j = 0;j < n;++j)
            {
                if(i == j) continue;
                if(dis(pt[i],pt[j]) > R*R) continue;
                x = pt[j].x - pt[i].x;
                y = pt[j].y - pt[i].y;
                val = getk(x,y);
                if(mp.find(val) == mp.end())
                {
                    mp[val] = j;
                    g[i][j] = 1;
                    d[i][i]++;
                }
                else
                {
                    int v = mp[val];
                    if(dis(pt[i],pt[j]) < dis(pt[i],pt[v]))
                    {
                        mp[val] = j;
                        g[i][j] = 1;
                        g[i][v] = 0;
                    }
                }
            }
        }
        for(int i = 0;i < n;++i)
            for(int j = 0;j < n;++j)
                g[i][j] = d[i][j] - g[i][j];
        printf("%d\n",det(n-1));
    }
    return 0;
}
