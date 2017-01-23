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
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100000+10;
struct Point
{
    int x,y;
    Point(){}
    Point(int x,int y):x(x),y(y) {}
}pt[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,X,Y,Z,p;
    scanf("%d%d%d%d%d%d",&n,&m,&X,&Y,&Z,&p);
    for(int i=0;i<p;++i)
        scanf("%d%d",&pt[i].x,&pt[i].y);
    X=X%4;Y%=2;Z%=4;
    int N=n,M=m;
    for(int i=0;i<p;++i)
    {
        n=N,m=M;
        int x=pt[i].x,y=pt[i].y;
        if(X==1) pt[i]=Point(y,n-x+1),swap(n,m);
        else if(X==2) pt[i]=Point(n-x+1,m-y+1);
        else if(X==3) pt[i]=Point(m-y+1,x),swap(n,m);
        x=pt[i].x,y=pt[i].y;
        if(Y) pt[i]=Point(x,m-y+1);
        x=pt[i].x,y=pt[i].y;
        if(Z==3) pt[i]=Point(y,n-x+1);
        else if(Z==2) pt[i]=Point(n-x+1,m-y+1);
        else if(Z==1) pt[i]=Point(m-y+1,x);
        printf("%d %d\n",pt[i].x,pt[i].y);
    }
    return 0;
}