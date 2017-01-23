#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=1000+10;
struct Wormholes
{
    int x,y,z;
}ww[maxn];
int gcd(int a,int b)
{
    int c;
    while(b!=0)
    {
        c=b;
        b=a%b;
        a=c;
    }
    return a;
}
bool check(Wormholes a,Wormholes b)
{
    if(a.y<=b.y&&a.z>=b.z) return false;
    if(b.y<=a.y&&b.z>=a.z) return false;
    int r=max(a.z,b.z)-min(a.y,b.y);
    int l=abs(min(a.z,b.z)-max(a.y,b.y));
    int c=gcd(a.x,b.x);
    if(l%c==0) return false;
    if(c-l%c+l<=r) return false;
    return true;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        for(int i=0;i<n;++i)
          scanf("%d%d%d",&ww[i].x,&ww[i].y,&ww[i].z);
        bool flag=true;
        for(int i=0;i<n&&flag;++i)
        {
            for(int j=i+1;j<n&&flag;++j)
               flag=flag&&check(ww[i],ww[j]);
        }
        if(flag) printf("Can Take off\n");
        else printf("Cannot Take off\n");
    }
    return 0;
}
