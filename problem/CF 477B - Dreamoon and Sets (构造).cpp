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
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 10000 + 10;
int num[maxn][4];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,k;
    scanf("%d%d",&n,&k);
    int m = 0;
    for(int i = 0;i < n;++i)
    {
        int base = i*6;
        num[i][0] = (base + 1)*k;
        num[i][1] = (base + 2)*k;
        num[i][2] = (base + 3)*k;
        num[i][3] = (base + 5)*k;
        m = max(m,(base + 5)*k);
    }
    printf("%d\n",m);
    for(int i = 0;i < n;++i)
    {
        for(int j = 0;j < 4;++j)
            printf("%d ",num[i][j]);
        puts("");
    }
    return 0;
}