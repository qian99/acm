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
const int maxn=100000+10;
char str[maxn],str2[maxn];
double sum[maxn],sum2[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w ",stdout);
    scanf("%s",str);
    scanf("%s",str2);
    int n=strlen(str);
    int m=strlen(str2);
    reverse(str,str+n);
    reverse(str2,str2+m);
    for(int i = 0;i < n;++i)
        if(str[i] == '1') sum[i]++;
    for(int i = 0;i < m;++i)
        if(str2[i] == '1') sum2[i]++;
    int N = max(n,m);
    for(int i = N-1;i >= 2;--i)
    {
        if(sum[i] > 0 && sum2[i] > 0)
        {
            double tmp = min(sum[i] , sum2[i]);
            sum[i] -= tmp;
            sum2[i] -= tmp;
        }
        if(sum[i])
        {
            sum[i-1] += sum[i];
            sum[i-2] += sum[i];
            sum[i] = 0;
        }
        if(sum2[i])
        {
            sum2[i-1] += sum2[i];
            sum2[i-2] += sum2[i];
            sum2[i] = 0;
        }
    }
    int res = 0;
    for(int i = 2;i >= 0;--i)
        if(sum[i] > sum2[i])
        {
            res = 1;
            break;
        }
        else if(sum[i] < sum2[i])
        {
            res = -1;
            break;
        }
    if(res == 1) printf(">\n");
    else if(res == -1) printf("<\n");
    else printf("=\n");
    return 0;
}
