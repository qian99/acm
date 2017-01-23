#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<vector>
#include<bitset>
#include<set>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=200000+10;
int num[maxn],pre[maxn],next[maxn];
map<int,int>mp;
bool solve(int L,int R)
{
    if(L>=R) return true;
    int i=L,j=R;
    while(i<=j)
    {
        if(pre[i]<L&&next[i]>R)
            return solve(L,i-1)&&solve(i+1,R);
        if(pre[j]<L&&next[j]>R)
            return solve(L,j-1)&&solve(j+1,R);
        i++;j--;
    }
    return false;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        mp.clear();
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&num[i]);
            if(mp.find(num[i])!=mp.end())
                pre[i]=mp[num[i]];
            else pre[i]=-1;
            mp[num[i]]=i;
        }
        mp.clear();
        for(int i=n;i>=1;--i)
        {
            if(mp.find(num[i])!=mp.end())
                next[i]=mp[num[i]];
            else next[i]=inf;
            mp[num[i]]=i;
        }
        if(solve(1,n)) puts("non-boring");
        else puts("boring");
    }
    return 0;
}
