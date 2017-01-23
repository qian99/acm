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
const int maxn = 100000 + 10;
int a[maxn],p[20];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    p[0] = 1;
    for(int i = 1;i < 20;++i) p[i] = p[i-1]<<1;
    int n;
    scanf("%d",&n);
    for(int i = 0;i < n;++i)
        scanf("%d",&a[i]);
    int pos = -1,cnt,sum;
    for(int i = 30;i >= 0;--i)
    {
        cnt = 0;
        sum = ((1<<i) - 1)|(1<<i);
        for(int j = 0;j < n;++j)
            if(a[j] & (1<<i))
            {
                sum &= a[j];
                cnt++;
            }
        int lowbit = sum & -sum;
        if(lowbit == (1<<i))
        {
            pos = i;
            break;
        }
    }
    printf("%d\n",cnt);
    for(int i = 0;i < n;++i)
        if(a[i] & (1<<pos))
            printf("%d ",a[i]);
    puts("");
    return 0;
}