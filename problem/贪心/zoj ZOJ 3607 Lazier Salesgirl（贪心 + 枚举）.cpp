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
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 1000 + 10;
int T[maxn],P[maxn];
double sum[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n;
        scanf("%d",&n);
        for(int i = 1;i <= n;++i)
            scanf("%d",&P[i]);
        for(int i = 1;i <= n;++i)
            scanf("%d",&T[i]);
        sum[0] = 0;
        for(int i = 1;i <= n;++i)
            sum[i] = sum[i-1] + P[i];
        double minw = 0,maxavg = 0;
        double w = 0,avg;
        T[0] = 0;
        for(int i = 1;i <= n;++i)
        {
            int j = i-1;
            w = T[i] - T[i-1];
            while(j+1 <= n && T[j] + w >= T[j+1])
            {
                j++;
            }
            avg = sum[j]/j;
            if(avg > maxavg)
            {
                maxavg = avg;
                minw = w;
            }
            i = j;
        }
        printf("%.6lf %.6lf\n",minw,maxavg);
    }
    return 0;
}
