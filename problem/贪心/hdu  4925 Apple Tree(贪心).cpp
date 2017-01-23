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
const int maxn=100+10;
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n,m;
        scanf("%d%d",&n,&m);
        ll sum1=0,sum2=0;
        for(int i=0;i<n;++i)
            for(int j=0;j<m;++j)
            {
                if((i+j)&1)
                {
                    int tmp=1;
                    if(i-1>=0) tmp*=2;
                    if(i+1<n) tmp*=2;
                    if(j-1>=0) tmp*=2;
                    if(j+1<m) tmp*=2;
                    sum1+=tmp;
                }
                else
                {
                    int tmp=1;
                    if(i-1>=0) tmp*=2;
                    if(i+1<n) tmp*=2;
                    if(j-1>=0) tmp*=2;
                    if(j+1<m) tmp*=2;
                    sum2+=tmp;
                }
            }
        if(sum2>sum1) sum1=sum2;
        printf("%I64d\n",sum1);
    }
    return 0;
}