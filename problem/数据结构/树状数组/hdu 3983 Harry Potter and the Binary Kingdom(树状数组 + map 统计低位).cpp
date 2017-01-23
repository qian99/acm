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
const int maxn = (1<<18) + 1;
int C[18][maxn];
void add(int i,int x,int v)
{
    for(;x <= 1<<(i+1);x += x&-x)
    {
        C[i][x] += v;
    }
}
int sum(int i,int x)
{
    int res = 0;
    for(;x > 0; x -= x&-x)
    {
        res += C[i][x];
    }
    return res;
}
int getsum(int i,int l,int r)
{
    return sum(i,r) - sum(i,l-1);
}
map<ll,int>mp;
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t,tcase = 0;
    scanf("%d",&t);
    while(t--)
    {
        int M;
        scanf("%d",&M);
        mp.clear();
        memset(C,0,sizeof(C));
        char str[20];
        int x,m;
        ll delta = 0,val;
        printf("Case %d:\n",++tcase);
        while(M--)
        {
            scanf("%s%d",str,&x);
            val = x - delta;
            if(str[0] == 'I')
            {
                mp[val]++;
                for(int i = 0;i < 18;++i)
                {
                    m = 1<<(i + 1);
                    int p = (val%m + m)%m + 1;
                    add(i,p,1);
                }
            }
            else if(str[0] == 'D')
            {
                if(mp.count(val) == 0)
                {
                    printf("Del error\n");
                    continue;
                }
                int cnt = mp[val];
                mp.erase(val);
                for(int i = 0;i < 18;++i)
                {
                    m = 1<<(i+1);
                    int p = (val%m + m)%m + 1;
                    add(i,p,-cnt);
                }
            }
            else if(str[0] == 'A')
                delta += x;
            else if(str[0] == 'S')
            {
                if(mp.size() && (mp.begin()->first + delta - x) < 0)
                {
                    puts("Sub error");
                    continue;
                }
                delta -= x;
            }
            else if(str[1] == 'N')
            {
                printf("%d\n",mp.count(val)?mp[val]:0);
            }
            else
            {
                m = 1<<(x+1);
                int l = (((1<<x) - delta)%m + m)%m,r = ((m - 1 - delta)%m + m)%m;
                int ans = 0;
                if(l <= r)
                    ans = getsum(x,l + 1,r + 1);
                else
                    ans = getsum(x,1,r + 1) + getsum(x,l + 1,m);
                printf("%d\n",ans);
            }
        }
        puts("");
    }
    return 0;
}
