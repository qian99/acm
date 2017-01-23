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
const int maxn=100+10;
int ch[maxn][2],tot;
char str1[maxn],str2[maxn];
void dfs(int p,int l,int r,int &rt)
{
    if(l>r) return;
    tot++;
    if(l==r)
    {
        if(rt!=-1) rt=p+1;
        return;
    }
    for(int i=l;i<=r;++i)
    {
        if(str1[p]==str2[i])
        {
            if(rt!=-1) rt=p+1;
            dfs(p+1,l,i-1,ch[p+1][0]);
            dfs(tot,i+1,r,ch[p+1][1]);
            break;
        }
    }
}
void dfs2(int rt)
{
    if(!rt) return ;
    dfs2(ch[rt][0]);
    dfs2(ch[rt][1]);
    printf("%c",str1[rt-1]);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%s%s",str1,str2))
    {
        memset(ch,0,sizeof(ch));
        int n=strlen(str1);
        int tmp=-1;
        tot=0;
        dfs(0,0,n-1,tmp);
        dfs2(1);
        printf("\n");
    }
    return 0;
}
