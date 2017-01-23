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
const int maxn = 100 + 10;
int F[maxn],tot;
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    F[0] = 0;
    F[1] = 1;
    tot = 2;
    for(int i = 2;;i++)
    {
        F[i] = F[i - 1] + F[i - 2];
        if(F[i] > 1e9) break;
        tot++;
    }
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n;
        scanf("%d",&n);
        bool flag = false;
        for(int i = 0;i < tot;++i)
            for(int j = i;j < tot;++j)
            {
                if((ll)F[i]*F[j] == n)
                    flag = true;
            }
        if(flag)
            puts("TAK");
        else
            puts("NIE");
    }
    return 0;
}
