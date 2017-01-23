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
const int maxn=3000000+10;
bool flag[maxn];
int sum[maxn];
void Init()
{
    memset(flag,0,sizeof(flag));
    flag[0]=flag[1]=true;
    for(int i=2;i<maxn;++i)
    {
        if(!flag[i])
        {
            for(ll j=(ll)i*i;j<maxn;j+=i)
                flag[j]=true;
        }
    }
    memset(sum,0,sizeof(sum));
    for(int i=1;i<maxn;++i)
    {
        int j=3*i+7;
        if(j<maxn&&!flag[j])
            sum[i]=1;
    }
    for(int i=1;i<maxn;++i)
        sum[i]+=sum[i-1];
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    Init();
    int t,n;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        printf("%d\n",sum[n]);
    }
    return 0;
}
