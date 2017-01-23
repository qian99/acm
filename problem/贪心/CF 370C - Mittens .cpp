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
const int maxn = 5000 + 10;
int a[maxn],ans[maxn][2];
int main()
{
//    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i = 0;i < n;++i)
        scanf("%d",&a[i]);
    sort(a,a+n);
    int res = 0;
    for(int i = 0;i < n;++i)
    {
        ans[i][0] = a[i];
        ans[i][1] = a[(i+n/2)%n];
        res += a[i] != a[(i+n/2)%n];
    }
    printf("%d\n",res);
    for(int i = 0;i < n;++i)
        printf("%d %d\n",ans[i][0],ans[i][1]);
    return 0;
}
