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
const int maxn=15000+10;
double a[maxn],b[maxn];
int n;
double cal(double x)
{
    double sum=0;
    for(int i=0;i<n;++i)
      sum+=abs(x-a[i])*b[i];
    return sum;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(cin>>n)
    {
        double L=50000,R=0;
        for(int i=0;i<n;++i)
        {
            cin>>a[i]>>b[i];
            L=min(L,a[i]);
            R=max(R,a[i]);
        }
        double m1,m2;
        double tp1,tp2;
        for(int i=0;i<100;++i)
        {
            m1=(L+R)/2;
            m2=(L+m1)/2;
            tp1=cal(m1);
            tp2=cal(m2);
            if(tp1<tp2)
              L=m2;
            else R=m1;
        }
        printf("%.5lf\n",L);
    }
    return 0;
}
