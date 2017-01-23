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
const int maxn = 100000+10;
priority_queue<int>q;
int main()
{
//    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase = 0;
    scanf("%d",&t);
    while(t--)
    {
        int n,a,b;
        scanf("%d",&n);
        for(int i = 0;i < n;++i)
        {
            scanf("%d",&a);
            q.push(a);
        }
        ll ans = 0;
        while(!q.empty())
        {
            a = q.top();q.pop();
            if(q.empty())
            {
                ans += a;
                break;
            }
            b = q.top();q.pop();
            if(a == b) ans += a;
            else
            {
                ans += b;
                q.push(a - b);
            }
        }
        printf("Case #%d: %I64d\n",++tcase,ans);
    }
    return 0;
}
