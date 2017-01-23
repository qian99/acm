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
const int maxn=100000+10;
int ch[maxn][26],tot;
char str[maxn];
void Insert()
{
    int u = 0;
    for(int i = 0;str[i];++i)
    {
        int c = str[i] - 'a';
        if(!ch[u][c])
        {
            ch[u][c] = ++tot;
            memset(ch[tot] ,0 ,sizeof(ch[tot]));
        }
        u = ch[u][c];
    }
}
bool dfs(int u,int type)
{
    bool flag=false;
    for(int i = 0;i < 26 ; ++i)
    {
        if(ch[u][i])
        {
            flag = true;
            if(!dfs(ch[u][i],type)) return true;
        }
    }
    if(!flag) return type;
    return false;
}
int main()
{
//    freopen("in.txt","r",stdin);
    //freopen("out.txt","w ",stdout);
    int n,k;
    scanf("%d%d",&n,&k);
    memset(ch[0],0,sizeof(ch[0]));
    tot=0;
    for(int i = 0;i < n;++i)
    {
        scanf("%s",str);
        Insert();
    }
    bool winit=dfs(0,0);
    bool loseit=dfs(0,1);
    if(winit&&loseit) puts("First");
    else if(!winit) puts("Second");
    else if(k & 1) puts("First");
    else puts("Second");
    return 0;
}
