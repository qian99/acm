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
const int maxn=100+10;
int x[maxn],y[maxn][maxn],z[maxn],n;
bool test(int m)
{
    memset(z,0,sizeof(z));
    memset(y,0,sizeof(y));
    for(int i=0;i<m;++i)
        y[i][0]=x[n-i-1],z[i]=1;
    int p=0;
    for(int i=n-m-1;i>=0;--i)
    {
        bool flag=false;
        for(int j=0;j<m;++j)
        {
            bool canuse=true;
            for(int k=0;k<z[p];++k)
            {
                if(y[p][k]<z[p]-(k+1)+1)
                    {canuse=false;break;}
            }
            if(canuse)
            {
                flag=true;
                y[p][z[p]++]=x[i];
                p=(p+1)%m;
                break;
            }
            p=(p+1)%m;
        }
        if(!flag) return false;
    }
    return true;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d",&n))
    {
        for(int i=0;i<n;++i)
            scanf("%d",&x[i]);
        sort(x,x+n);
        int l=1,r=n;
        while(l<r)
        {
            int m=(l+r)>>1;
            if(test(m))
                r=m;
            else l=m+1;
        }
        printf("%d\n",l);
    }
    return 0;
}