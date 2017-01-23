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
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=200+10;
const int mod=1000000007;
struct Point
{
    int x,y;
    Point(){}
    Point(int x,int y):x(x),y(y){}
}pt[maxn];
Point dec(Point a,Point b)
{
    return Point(a.x-b.x,a.y-b.y);
}
ll Cross(Point a,Point b)
{
    return (ll)a.x*b.y-(ll)a.y*b.x;
}
ll dp[maxn][maxn];
ll f(int l,int r)
{
    if(r-l<=1) return 1;
    if(dp[l][r]!=-1) return dp[l][r];
    dp[l][r]=0;
    for(int i=l+1;i<r;++i)
    {
        if(Cross(dec(pt[r],pt[l]),dec(pt[l],pt[i]))<0)
            dp[l][r]=(dp[l][r]+f(l,i)*f(i,r))%mod;
    }
    return dp[l][r];
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    cin>>n;
    for(int i=0;i<n;++i)
        cin>>pt[i].x>>pt[i].y;
    ll dir=0;
    pt[n]=pt[0];
    for(int i=0;i<n;++i)
        dir+=Cross(pt[i],pt[i+1]);
    if(dir>0) reverse(pt,pt+n);
    memset(dp,0xff,sizeof(dp));
    cout<<f(0,n-1)<<endl;
    return 0;
}