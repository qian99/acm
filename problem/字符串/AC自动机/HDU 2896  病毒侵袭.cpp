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
const int maxm=10000+10;
const int csize=130;
int ch[maxn][csize],val[maxn],next[maxn],lastv[maxn],size;
void Init()
{
    memset(ch[0],0,sizeof(ch[0]));
    memset(next,0,sizeof(next));
    memset(lastv,0,sizeof(lastv));
    val[0]=0;size=0;
}
void insert(const char *s,int v)
{
    int u=0,n=strlen(s);
    for(int i=0;i<n;++i)
    {
        int c=(int)s[i];
        if(!ch[u][c])
        {
            ch[u][c]=++size;
            memset(ch[size],0,sizeof(ch[size]));
            val[size]=0;
        }
        u=ch[u][c];
    }
    val[u]=v;
}
void build()
{
    queue<int>q;
    for(int i=0;i<csize;++i)
        if(ch[0][i]) q.push(ch[0][i]);
    int r,u,v;
    while(!q.empty())
    {
        r=q.front();q.pop();
        for(int c=0;c<csize;++c)
        {
            u=ch[r][c];
            if(!u) {ch[r][c]=ch[next[r]][c];continue;}
            q.push(u);
            v=next[r];
            while(v&&!ch[v][c]) v=next[v];
            next[u]=ch[v][c];
            lastv[u]=val[next[u]]?next[u]:lastv[next[u]];
        }
    }
}
char str[maxm];
bool vis[maxm];
int vir[maxm];
void find(const char * s)
{
    int u=0,n=strlen(s);
    for(int i=0;i<n;++i)
    {
        int c=(int)s[i];
        u=ch[u][c];
        if(val[u]||lastv[u])
        {
            int v=val[u]?u:lastv[u];
            while(v)
            {
                if(!vis[v])
                {
                    vis[val[v]]=true;
                    vir[++vir[0]]=val[v];
                }
                v=lastv[v];
            }
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d",&n))
    {
        Init();
        for(int i=1;i<=n;++i)
        {
            scanf("%s",str);
            insert(str,i);
        }
        build();
        int total=0;
        memset(vis,0,sizeof(vis));
        scanf("%d",&m);
        for(int i=1;i<=m;++i)
        {
            scanf("%s",str);
            vir[0]=0;
            find(str);
            if(vir[0])
            {
                sort(vir+1,vir+vir[0]+1);
                printf("web %d:",i);
                for(int j=1;j<=vir[0];++j)
                {
                    printf(" %d",vir[j]);
                    vis[vir[j]]=false;
                }
                printf("\n");
                total++;
            }
        }
        printf("total: %d\n",total);
    }
    return 0;
}

