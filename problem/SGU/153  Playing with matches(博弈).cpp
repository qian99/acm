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
const int maxn=100+10;
bool flag[maxn];
int op[10];
bool check(int p)
{
    int mid=p/2;
    for(int i=1;i<=mid;++i)
    {
        if(flag[i]!=flag[mid+i]) return false;
    }
    return true;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n,m;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        op[0]=1;
        for(int i=1;i<=m;++i)
          scanf("%d",&op[i]);
        memset(flag,true,sizeof(flag));
        flag[1]=false;
        bool ff;
        for(int i=2;i<=20;++i)
        {
            ff=false;
            for(int j=0;j<=m;++j)
              if(i-op[j]>0&&!flag[i-op[j]]) ff=true;
            flag[i]=ff;
        }
        int p=50;
        while(true)
        {
            if(check(p)) break;
            p-=2;
        }
        n%=p;
        if(n==0) n=p;
        if(flag[n]) printf("FIRST PLAYER MUST WIN\n");
        else printf("SECOND PLAYER MUST WIN\n");
    }
    return 0;
}
