#include <iostream>
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
const int maxn=100000+10;
//const int maxm=1<<17;
int d[maxn][17],value[maxn],counts[maxn],num[maxn],leftn[maxn],rightn[maxn];
void RMQ_init(int n)
{
    for(int i=1;i<=n;++i) d[i][0]=counts[i];
    for(int j=1;(1<<j)<=n;++j)
    {
        for(int i=1;i<=n;++i)
        {
            d[i][j]=max(d[i][j-1],d[i+(1<<(j-1))][j-1]);
        }
    }
}
int RMQ(int L,int R)
{
    if(R<L) return 0;
    int k=0;
    while((1<<(k+1))<=R-L+1) k++;
    return max(d[L][k],d[R-(1<<k)+1][k]);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,q,a,b;
    while(cin>>n)
    {
        if(n==0) break;
        cin>>q;
        b=inf;
        int m=0;
        memset(counts,0,sizeof(counts));
        for(int i=1;i<=n;++i)
        {
            cin>>a;
            if(a==b)
            {
                counts[m]++;
                leftn[i]=leftn[i-1];
                num[i]=m;
            }
            else
            {
                b=a;
                m++;
                counts[m]=1;
                value[m]=a;
                leftn[i]=i;
                num[i]=m;
                for(int j=i-1;j>=leftn[i-1];--j)
                  rightn[j]=i-1;
            }
        }
        for(int j=n;j>=leftn[n];--j)
           rightn[j]=n;
        RMQ_init(m);
        for(int i=0;i<q;++i)
        {
            cin>>a>>b;
            int res=0;
            int L,R;
            if(rightn[a]>=leftn[b])
            {
                res=b-a+1;
            }
            else
            {
                L=rightn[a]-a+1;
                R=b-leftn[b]+1;
                res=max(res,L);
                res=max(res,R);
                res=max(res,RMQ(num[a]+1,num[b]-1));
            }
            cout<<res<<endl;
        }
    }
    return 0;
}
