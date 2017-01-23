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
const int maxn = 100 + 10;
char str[maxn];
int dp[maxn][1<<16],cost[maxn],mask[maxn],S,m,n;
int getnum(int & s,int t)
{
    while(s <= t && (str[s] < '0' || str[s] >'9')) s++;
    if(s > t) return -1;
    int val = 0;
    while(s <= t && str[s] >= '0' && str[s] <= '9')
    {
        val = val*10 + (str[s] - '0');
        s++;
    }
    return val;
}
pair<int,int> getinfo()
{
    gets(str);
    int m = strlen(str);
    pair<int,int>res;
    int s = 0,t = m-1,tmp;
    res.first = getnum(s,t);
    res.second = 0;
    while((tmp = getnum(s,t)) != -1)
    {
        res.second |= (1<<(tmp-1));
    }
    return res;
}
inline int Uion(int x,int y)
{
    int st = x;
    st |= (x^y) & y;
    st |= (x&y)<<S;
    return st;
}
int main()
{
//    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d%d",&S,&m,&n))
    {
         Uion(3,3);
        if(S == 0 && m == 0 && n == 0) break;
        getchar();
        int mincost = 0,state = 0;
        pair<int,int>pii;
        for(int i = 0;i < m;++i)
        {
            pii = getinfo();
            mincost += pii.first;
            state = Uion(state,pii.second);
        }
        for(int i = 1;i <= n;++i)
        {
            pii = getinfo();
            cost[i] = pii.first;
            mask[i] = pii.second;
        }
        memset(dp,0x3f,sizeof(dp));
        dp[0][state] = mincost;
        int tot = 1<<(S<<1);
        for(int i = 0;i < n;++i)
            for(int j = 0;j < tot;++j)
            {
                if(dp[i][j] == inf) continue;
                dp[i+1][j] = min(dp[i+1][j],dp[i][j]);
                state = Uion(j,mask[i+1]);
                dp[i+1][state] = min(dp[i+1][state],dp[i][j] + cost[i+1]);
            }
        printf("%d\n",dp[n][tot-1]);
    }
    return 0;
}
