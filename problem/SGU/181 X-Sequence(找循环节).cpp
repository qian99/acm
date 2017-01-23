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
const int maxn=20000+10;
int hash[maxn],xx[maxn],cnt;
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int A,a,b,c,m,k,x;
    scanf("%d%d%d%d%d%d",&A,&a,&b,&c,&m,&k);
    memset(hash,0,sizeof(hash));
    cnt=0;
    x=A;
    hash[x]=1;
    xx[cnt++]=x;
    int tmp;
    while(true)
    {
        tmp=(((x*x)%m)*a)%m+(x*b)%m+c;
        tmp%=m;
        if(hash[tmp]) break;
        hash[tmp]=1;
        xx[cnt++]=tmp;
        x=tmp;
    }
    int p=cnt-1;
    int z=1;
    while(xx[p]!=tmp)
    {
        z++;
        p--;
    }
    int w=cnt-z;
    int ans;
    if(k<cnt)
    {
        ans=xx[k];
    }
    else
    {
        tmp=(k-w+1)%z;
        tmp--;
        if(tmp<0) tmp=z-1;
        ans=xx[tmp+w];
    }
    printf("%d\n",ans);
    return 0;
}
