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
const int maxn = 100000+10;
int a[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t,tcase = 0;
    scanf("%d",&t);
    while(t--)
    {
        int n;
        scanf("%d",&n);
        for(int i = 1;i <= n;++i)
            scanf("%d",&a[i]);
        int cnt = 0;
        for(int i = 1;i < n;++i)
        {
            if(a[i] == 1 && a[i+1] == 2) cnt++;
            if(a[i] == 2 && a[i+1] == 1) cnt++;
            if(abs(a[i+1] - a[i]) > 3 || (a[i+1]==a[i]&&a[i]!=1))
            {
                cnt = -1;
                break;
            }
        }
        if(a[n] == 0) cnt = cnt + 1;
        else cnt = (cnt + 1)*2;
        printf("Case #%d: %d\n",++tcase,cnt);
    }
    return 0;
}
