#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
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
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int a,b,c,d,x,y;
    while(~scanf("%d%d%d",&a,&b,&c))
    {
        if(a==0&&b==0&&c==0) break;
        d=ext_gcd(a,b,x,y);
        c/=d;a/=d;b/=d;
        x*=c;y*=c;
        while(abs(x)+abs(y)>abs(x-b)+abs(y+a)) {x-=b;y+=a;}
        while(abs(x)+abs(y)>abs(x+b)+abs(y-a)) {x+=b;y-=a;}
        while((abs(x)+abs(y)==abs(x-b)+abs(y+a))&&(abs(a*x)+abs(b*y)>abs((x-b)*a)+abs((y+a)*b))) {x-=b;y+=a;}
        while((abs(x)+abs(y)==abs(x+b)+abs(y-a))&&(abs(a*x)+abs(b*y)>abs((x+b)*a)+abs((y-a)*b))) {x+=b;y-=a;}
        x=abs(x);y=abs(y);
        printf("%d %d\n",x,y);
    }
    return 0;
}
