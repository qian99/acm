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
const int Size=333;
const int maxn=100000+10;
deque<int>block[Size];
int cnt[Size][maxn];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w ",stdout);
    int n,m,x;
    scanf("%d",&n);
    for(int i = 0;i < n;++i)
    {
        scanf("%d",&x);
        block[i/Size].push_back(x);
        cnt[i/Size][x]++;
    }
    int ans = 0;
    int L,R,l,r,k,pos;
    scanf("%d",&m);
    while(m--)
    {
        scanf("%d%d%d",&x,&L,&R);
        L = (L + ans -1)%n +1;
        R = (R + ans -1)%n +1;
        if(L > R) swap(L,R);
        L--;R--;
        l = L/Size;
        r = R/Size;
        if(x == 1)
        {
            if(l == r)
            {
                pos = R % Size;
                int xx = block[l][pos];
                block[l].erase(block[l].begin() + pos);
                pos = L % Size ;
                block[l].insert(block[l].begin() + pos,xx);
            }
            else
            {
                pos = R %Size;
                int xx = block[r][pos],y;
                block[r].erase(block[r].begin() + pos);
                cnt[r][xx]--;
                for(int i = r-1;i >= l;--i)
                {
                    y = block[i].back();
                    block[i].pop_back();
                    block[i+1].push_front(y);
                    cnt[i][y]--;
                    cnt[i+1][y]++;
                }
                block[l].insert(block[l].begin() + L%Size ,xx);
                cnt[l][xx]++;
            }
        }
        else
        {
            scanf("%d",&k);
            k = (k + ans -1)%n +1;
            ans = 0;
            for(int i = l+1;i < r;++i)
                ans += cnt[i][k];
            if(l != r)
            {
                for(int i = L%Size;i < (int)block[l].size();++i)
                    ans += (block[l][i]==k);
                for(int i = 0;i <= R%Size;++i)
                    ans += (block[r][i]==k);
            }
            else
            {
                for(int i = L%Size;i <= R%Size;++i)
                {
//                    cout<<block[l][i]<<".";
                    ans += (block[l][i]==k);
                }

            }
            printf("%d\n",ans);
        }
    }
    return 0;
}
