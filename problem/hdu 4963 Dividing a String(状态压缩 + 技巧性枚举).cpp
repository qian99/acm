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
const int maxn = 55;
char str[maxn],sc[maxn],S[maxn],T[maxn];
int val[maxn],cnt[1<<20],pw[maxn],W[maxn],n;
vector<int>vt[2][1<<21];
void Init()
{
    pw[0] = 1;
    for(int i = 1;i < maxn;++i)
        pw[i] = 1<<i;
    int x;
    for(int i = 0;i < (1<<20);++i)
    {
        x = i;
        while(x)
        {
            cnt[i]++;
            x &= (x-1);
        }
    }
}
void dfs(int pos,int x,int y,int vx,int vy,int type)
{
    if(x + n - pos < y) return ;
    if(pos == n)
    {
        int state = 0;
        if(type == 0)
        {
            for(int i = y;i < x;++i) state = (state<<1)|S[i];
            state |= pw[(x - y)];
            vt[0][state].push_back(vx);
        }
        else
        {
            for(int i = x - 1;i >= y;--i) state = (state<<1)|S[i];
            state |= pw[(x - y)];
            vt[1][state].push_back(vy);
        }
        return ;
    }
    if(x >= y || sc[pos] == T[x])
    {
        S[x] = sc[pos];
        dfs(pos+1,x+1,y,vx + W[pos],vy,type);
    }
    if(y >= x || sc[pos] == S[y])
    {
        T[y] = sc[pos];
        dfs(pos+1,x,y+1,vx,vy + W[pos],type);
    }
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    Init();

    while(~scanf("%d",&n))
    {
        if(n == 0) break;
        scanf("%s",str);
        int cntA = 0,cntB = 0;
        for(int i = 0;i < n*2;++i)
            if(str[i] == 'A') cntA++;
            else cntB++;
        if(cntA & 1)
        {
            printf("-1\n");
            continue;
        }
        int sum = 0;
        for(int i = 0;i < n*2;++i)
        {
            scanf("%d",&val[i]);
            sum += val[i];
        }
        for(int i = 0;i < n;++i)
        {
            sc[i] = str[i] - 'a';
            W[i] = val[i];
        }
        dfs(0,0,0,0,0,0);
        for(int i = 0;i < n;++i)
        {
            sc[i] = str[n*2 - i - 1] - 'a';
            W[i] = val[n*2 - i - 1];
        }
        dfs(0,0,0,0,0,1);
        int ans = inf,tmp;
        for(int i = 0;i < (1<<(n+1));++i)
        {
            if(vt[0][i].size() && vt[1][i].size())
            {
                sort(vt[0][i].begin(),vt[0][i].end());
                sort(vt[1][i].begin(),vt[1][i].end());
                for(int j = 0,k = vt[1][i].size() - 1;j < (int)vt[0][i].size();++j)
                    for(;k >= 0;k--)
                    {
                        tmp = vt[0][i][j] + vt[1][i][k];
                        ans = min(ans,abs(sum - tmp*2));
                        if(tmp*2 <= sum) break;
                    }
            }
            vt[0][i].clear();
            vt[1][i].clear();
        }
        if(ans == inf) ans = -1;
        printf("%d\n",ans);
    }
    return 0;
}
