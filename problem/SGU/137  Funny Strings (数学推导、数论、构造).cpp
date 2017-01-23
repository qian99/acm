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
const int maxn=1000+10;
int num[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,k;
    memset(num,0,sizeof(num));
    scanf("%d%d",&n,&k);
    int m=0,add;
    add=k/n;
    k%=n;
    while((m*k)%n!=n-1) m++;
    for(int i=m;i!=n-1;i=(i+m)%n)
      num[i]=1;
    num[n-1]=1;
    printf("%d",num[0]+add);
    for(int i=1;i<n;++i)
      printf(" %d",num[i]+add);
    printf("\n");
    return 0;
}
