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
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 1000 +10;
int ext_gcd(int a,int b,int &x,int &y)
{
    if(b==0)
    {
        x=1;y=0;
        return a;
    }
    int d=ext_gcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t;
    int a,m;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&a,&m);
        int x,y;
        int d = ext_gcd(a,m,x,y);
        if(d != 1)
        {
            puts("Not Exist");
        }
        else
        {
            x = (x%m + m)%m;
            if(x == 0) x = m;
            printf("%d\n",x);
        }
    }
    return 0;
}
