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
const int maxn=100000+10;
int ch[maxn][10],val[maxn],size;
char str[20];
void Init()
{
    memset(ch[0],0,sizeof(ch[0]));
    val[0]=0;size=0;
}
bool Insert(const char *s)
{
    int u=0,n=strlen(s);
    for(int i=0;i<n;++i)
    {
        int c=str[i]-'0';
        if(!ch[u][c])
        {
            ch[u][c]=++size;
            memset(ch[size],0,sizeof(ch[size]));
            val[size]=0;
        }
        else if(i==n-1) return false;
        u=ch[u][c];
        if(val[u]) return false;
    }
    val[u]=1;
    return true;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n;
        bool flag=true;
        Init();
        scanf("%d",&n);
        for(int i=0;i<n;++i)
        {
            scanf("%s",str);
            flag=flag&&Insert(str);
        }
        if(flag) puts("YES");
        else puts("NO");
    }
    return 0;
}

