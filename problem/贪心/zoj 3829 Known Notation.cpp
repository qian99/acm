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
const int maxn = 3000 + 10;
char str[maxn],s[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%s",str);
        int n = strlen(str);
        int cnt = 0,ans = 0;
        for(int i = 0;i < n;++i)
            if(str[i] == '*') cnt++;
//        y  >= cnt + 1
        int m = 0;
        for(int i = n - cnt;i < cnt + 1;++i)
            s[m++] = '1',ans++;
        for(int i = 0;i < n;++i)
            s[m++] = str[i];
        cnt = 0;
        int last = m - 1;
        for(int i = 0;i < m;++i)
        {
            if(s[i] == '*') cnt--;
            else cnt++;
            if(cnt < 1)
            {
                while(s[last] == '*') last--;
                swap(s[last],s[i]);
                ans++;
                cnt += 2;
                last--;
            }
        }
        if(s[m - 1] != '*') ans++;
        bool flag = true;
        for(int i = 0;i < n;++i)
            if(str[i] == '*') flag = false;
        if(flag) ans = 0;
        printf("%d\n",ans);
    }
    return 0;
}
