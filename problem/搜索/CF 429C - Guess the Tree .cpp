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
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
int cnt[25],f[25],t[25],n;
bool dfs(int step,int lim)
{
    if(step==n)
    {
        for(int i=0;i<n;++i)
            if(f[i]!=t[i]) return false;
        return true;
    }
    while(cnt[lim]==0) lim--;
    f[step]=1; t[step]=lim;
    for(int i=0;i<step;++i)
    {
        if(lim+1<t[i]&&f[i]+lim<=t[i])
        {
            f[i]+=lim;
            cnt[lim]--;
            if(dfs(step+1,lim)) return true;
            f[i]-=lim;
            cnt[lim]++;
            if(lim==1) break;
        }
    }
    return false;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d",&n);
    int tmp;
    memset(cnt,0,sizeof(cnt));
    for(int i=0;i<n;++i)
    {
        scanf("%d",&tmp);
        cnt[tmp]++;
    }
    f[0]=1;t[0]=n;
    if(cnt[2]||cnt[n]!=1) puts("NO");
    else if(!dfs(1,n-1)) puts("NO");
    else puts("YES");
    return 0;
}
