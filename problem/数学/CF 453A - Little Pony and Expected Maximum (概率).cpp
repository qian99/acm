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
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int m,n;
    scanf("%d%d",&m,&n);
    double ans=0;
    for(int i=m;i>=1;--i)
    {
        ans+=(pow(i*1.0/m,n)-pow((i-1)*1.0/m,n))*i;
    }
//    if(!(ans>=0&&ans<=m)) ans=m;
    printf("%.10lf\n",ans);
    return 0;
}