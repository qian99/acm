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
int dcmp(double x) {return (x>eps)-(x<-eps);}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int x,y;
    while(~scanf("%d%d",&x,&y))
    {
        if(y<x)
        {
            printf("-1\n");
            continue;
        }
        double L=(double)y/x,R=(double)(y+1)/x;
        int sx=1;
        double sy=1,tmp;
        int cnt=0;
        while(sx<x)
        {
            tmp=sy/sx;
            if(dcmp(tmp-R)<0)
            {
                int k=R*sx-sy;
                cnt+=k;
                sy+=k;
                tmp=sy/sx;
            }
            if(dcmp(tmp-R)>=0) {sy--;cnt--;}
            tmp=sy/sx;
            sx++;
            sy=sx*tmp;
            cnt++;
        }
        if(y!=(int)sy)
        {
            cnt+=(y-(int)sy);
        }
        printf("%d\n",cnt);
    }
    return 0;
}
