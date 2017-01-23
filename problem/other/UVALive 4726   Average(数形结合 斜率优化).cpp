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
const int maxn=100000+10;
struct Point
{
    double x,y;
    Point (){};
    Point (double xx,double yy) {x=xx;y=yy;}
};
Point p[maxn];
typedef Point Vector;
double Cross(Vector a,Vector b) {return a.x*b.y-a.y*b.x;}
Vector operator -(Point a,Point b) {return Vector(a.x-b.x,a.y-b.y);}
double calk(Point a,Point b) {  return (b.y-a.y)/(b.x-a.x);}
int dcmp(double x)
{
    if(fabs(x)==0) return 0;
    return x>0?1:-1;
}
char str[maxn];
int n,L,maxl,maxr;
double maxv;
Point sp[maxn];
void solve()
{
    int m=0;
    sp[m++]=p[0];
    int s=0,tmp;
    double k,tmp2;
    bool flag;
    for(int i=L;i<=n;++i)
    {
        flag=false;
        if(s<m&&sp[s].x<=i-L)
        {
            k=calk(sp[s],p[i]);
            while(s+1<m)
            {
                tmp2=calk(sp[s+1],p[i]);
                if(dcmp(k-tmp2)<=0) {s++;k=tmp2;}
                else break;
            }
            tmp=dcmp(k-maxv);
            if(tmp>=0)
            {
                maxv=k;
                if(tmp>0||(tmp==0&&maxr-maxl+1>(int)(p[i].x-sp[s].x+eps)))
                {maxl=sp[s].x+1+eps;maxr=p[i].x+eps;}
            }
        }
        while(m>s+1&&Cross(sp[m-1]-sp[m-2],p[i-L+1]-sp[m-1])<0) m--;
        sp[m++]=p[i-L+1];
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&L);
        scanf("%s",str);
        int sum=0;
        p[0]=Point(0,0);
        for(int i=0;i<n;++i)
        {
            sum+=(str[i]-'0');
            p[i+1]=Point(i+1,sum);
        }
        maxv=0;
        if(L==1)
        {
            if(sum==0) {maxl=maxr=1;}
            else
            {
                for(int i=0;i<n;++i)
                    if(str[i]=='1') {maxl=maxr=i+1;break;}
            }
        }
        else solve();
        printf("%d %d\n",maxl,maxr);
    }
    return 0;
}

