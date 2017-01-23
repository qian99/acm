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
const int maxn = 200000+10;
int sq[maxn],tot;
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
//    tot = 0;
//    for(int i = 1;i < maxn;++i)
//    {
//        if(i*i < maxn)
//            sq[tot++] = i*i;
//        else break;
//    }
    int n,k;
    while(~scanf("%d%d",&n,&k))
    {
        bool flag = false;
        for(int i = 1;i*i < n && !flag;++i)
        {
            if(i*i > n) break;
            if(k == 2)
            {
                if(i*i != n - i*i)
                    flag = true;
                continue;
            }
            int remain = i*i,other = n - i*i;
            int sum = (k-1)*(k-2)/2;
            int lastone;
            int now = k - 2;
            if(other <= now)
            {
                sum -= other;
                sum += ++now;
            }
            lastone = remain - sum;
            if(lastone <= now || lastone <= 0) continue;
            if(sum + lastone != remain) continue;
            if(other == lastone)
            {
                lastone--;
                now++;
            }
            if(lastone <= now) continue;
            flag = true;
        }
        if(flag) puts("YES");
        else puts("NO");
    }
    return 0;
}
