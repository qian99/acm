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
const int maxn=10000000+10;
const int maxm=200+10;
int ch[maxn][2],val[maxn],size,maxval;
char str[maxm];
void Init()
{
    ch[0][0]=ch[0][1]=0;
    val[0]=0;size=0;
    maxval=0;
}
void Insert(const char *s)
{
    int u=0,n=strlen(s);
    for(int i=0;i<n;++i)
    {
        int c=s[i]-'0';
        if(!ch[u][c])
        {
            ch[u][c]=++size;
            ch[size][0]=ch[size][1]=0;
            val[size]=0;
        }
        u=ch[u][c];val[u]++;
        maxval=max(maxval,val[u]*(i+1));
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        Init();
        int n;
        scanf("%d",&n);
        for(int i=0;i<n;++i)
        {
            scanf("%s",str);
            Insert(str);
        }
        printf("%d\n",maxval);
    }
    return 0;
}

