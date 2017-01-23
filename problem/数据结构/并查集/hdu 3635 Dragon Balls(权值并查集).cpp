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
const int maxn=10000+10;
int pa[maxn],cnt[maxn],move[maxn];
int Find(int x)
{
    if(x==pa[x]) return x;
    int y=Find(pa[x]);
    move[x]=move[pa[x]]+1;
    return y;
}
void Init(int n)
{
    for(int i=1;i<=n;++i)
    {
        pa[i]=i;
        move[i]=0;
        cnt[i]=1;
    }
}
void Uion(int x,int y)
{
    int a=Find(x);
    int b=Find(y);
    if(a!=b)
    {
        pa[a]=b;
        cnt[b]+=cnt[a];
        cnt[a]=0;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n,q,tcase=0;
    char str[5];
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&q);
        Init(n);
        int x,y;
        printf("Case %d:\n",++tcase);
        while(q--)
        {
            scanf("%s",str);
            if(str[0]=='T')
            {
                scanf("%d%d",&x,&y);
                Uion(x,y);
            }
            else
            {
                scanf("%d",&x);
                y=Find(x);
                printf("%d %d %d\n",y,cnt[y],move[x]);
            }
        }
    }
    return 0;
}
