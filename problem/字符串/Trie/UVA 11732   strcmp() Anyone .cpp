#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=4000000+10;
int cnt[maxn],val[maxn],size;
int son[maxn],nexts[maxn];
char c[maxn];
char str[1010];
ll ans;
void Init()
{
    son[0]=nexts[0]=0;
    size=0;val[0]=0;cnt[0]=0;
}
void insert(const char *s)
{
    ans+=val[0];
    val[0]++;
    int u=0,n=strlen(s);
    int v;
    bool flag;
    for(int i=0;i<n;++i)
    {
        flag=false;
        for(v=son[u];v;v=nexts[v])
        {
            if(s[i]==c[v])
            {
                flag=true;
                break;
            }
        }
        if(!flag)
        {
            v=++size;
            nexts[v]=son[u];
            son[u]=v;val[v]=0;
            son[v]=0;
            c[v]=s[i];cnt[v]=0;
        }
        u=v;
        ans+=val[u]*2;
        val[u]++;
    }
    if(cnt[u]) ans+=cnt[u];
    cnt[u]++;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int tcase=0,n;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        tcase++;
        Init();
        ans=0;
        for(int i=0;i<n;++i)
        {
            scanf("%s",str);
            insert(str);
        }
        printf("Case %d: %lld\n",tcase,ans);
    }
    return 0;
}

