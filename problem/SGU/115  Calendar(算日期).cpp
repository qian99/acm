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
const int md[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
int sum[15];
bool check(int x,int y)
{
    return y>=1&&y<=12&&x>=1&&x<=md[y];
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    sum[0]=0;
    for(int i=1;i<=12;++i)
      sum[i]=sum[i-1]+md[i];
    int n,m;
    while(cin>>n>>m)
    {
        if(check(n,m))
        {
            int x=sum[m-1];
            x+=n;
            int ans=x%7;
            if(ans==0) ans=7;
            printf("%d\n",ans);
        }
        else printf("Impossible\n");
    }
    return 0;
}
