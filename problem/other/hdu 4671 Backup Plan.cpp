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
const int maxn=100+10;
struct Data
{
    int num,tt;
    bool operator <(const Data &a) const
    {
        return tt<a.tt;
    }
};
int aa[maxn][2];
Data d[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        memset(d,0,sizeof(d));
        int mx=0;
        for(int i=1;i<=n;++i) d[i].num=i;
        for(int i=1;i<=m;++i)
        {
            int tmp=i%n;
            if(tmp==0) tmp=n;
            mx=max(mx,tmp);
            aa[i][0]=tmp;
            d[tmp].tt++;
        }
        sort(d+1,d+n+1);
        for(int i=1;i<=mx;++i)
        {
            int k=1;
            for(int j=1;j<=m;++j)
            {
                if(aa[j][0]==i)
                {
                    while(aa[j][0]==d[k].num)
                    {k++;k%=n;if(k==0) k=n;}
                    aa[j][1]=d[k].num;
                    k++;
                    k%=n;
                    if(k==0) k=n;
                }
            }
        }
        for(int i=1;i<=m;++i)
        {
            printf("%d %d",aa[i][0],aa[i][1]);
            int k=1;
            for(int j=3;j<=n;++j)
            {
                while(k==aa[i][0]||k==aa[i][1]) k++;
                printf(" %d",k);
                k++;
            }
            printf("\n");
        }
    }
    return 0;
}
