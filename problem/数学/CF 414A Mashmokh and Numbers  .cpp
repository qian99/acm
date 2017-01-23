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
const int maxn=100000+10;
int a[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,k;
    scanf("%d%d",&n,&k);
    if(n/2>k)
    {
        printf("-1\n");
        return 0;
    }
    if(n==1&&k!=0)
    {
        printf("-1\n");
        return 0;
    }
    int tmp;
    if(n&1)
    {
        tmp=(n-3)/2;
        k=k-tmp;
    }
    else
    {
        tmp=(n-2)/2;
        k-=tmp;
    }
    a[0]=k;a[1]=2*k;
    tmp=1;
    for(int i=2;i<n;++i)
    {
        while(tmp==k||tmp==2*k||tmp+1==k||tmp+1==2*k) tmp++;
        a[i++]=tmp++;a[i]=tmp++;
    }
    for(int i=0;i<n;++i)
        printf("%d ",a[i]);
    printf("\n");
    return 0;
}