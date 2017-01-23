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
int ans[maxn];
void cal()
{
    int n;
    int last = 0;
    for(n = 4;n <= 100;n += 2)
    {
        int ans = 0;
        for(int i = 1;i <= n/3;++i)
            for(int j = i;j <= n - (i + j);++j)
            {
                if(i + j > n - (i + j))
                {
                    int k = n - (i + j);
                    if(i != j && i != k && j != k)
                        ans += 2;
                    else ans++;
                }

            }
        cout<<n<<" "<<ans<<" "<<ans - last<<endl;
        last = ans;
    }
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
//    cal();
    memset(ans,0,sizeof(ans));
    int add = 1;
    for(int i = 3;i < maxn;i += 6)
    {
        ans[i] = ans[i - 2] + add;
        ans[i+2] = ans[i] + add-1;
        ans[i+4] = ans[i+2] + add;
        add++;
    }
    add = 1;
    for(int i = 4;i < maxn;i += 6)
    {
        ans[i] = ans[i - 2] + add - 1;
        ans[i+2] = ans[i] + add;
        ans[i+4] = ans[i+2] + add - 1;
        add++;
    }
    int t,tcase;
    scanf("%d",&t);
    while(t--)
    {
        int n;
        scanf("%d%d",&tcase,&n);
        printf("%d %d\n",tcase,ans[n]);
    }
    return 0;
}

