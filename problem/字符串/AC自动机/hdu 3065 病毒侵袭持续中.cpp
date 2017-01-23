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
const int maxn=50000+10;
const int maxm=2000000+10;
int ch[maxn][26],next[maxn],lastv[maxn],val[maxn],size;
int cnt[1010];
char pstr[1010][55],str[maxm];
void Init()
{
    memset(ch[0],0,sizeof(ch[0]));
    memset(next,0,sizeof(next));
    memset(lastv,0,sizeof(lastv));
    val[0]=size=0;
}
void insert(const char * s,int v)
{
    int u=0,n=strlen(s);
    for(int i=0;i<n;++i)
    {
        int c=s[i]-'A';
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
    for(int i=0;i<26;++i)
        if(ch[0][i]) q.push(ch[0][i]);
    int r,u,v;
    while(!q.empty())
    {
        r=q.front();q.pop();
        for(int c=0;c<26;++c)
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
void find(const char * s)
{
    int u=0,n=strlen(s);
    for(int i=0;i<n;++i)
    {
        if(s[i]<'A'||s[i]>'Z'){u=0;continue;}
        int c=s[i]-'A';
        u=ch[u][c];
        if(val[u]||lastv[u])
        {
            int v=val[u]?u:lastv[u];
            while(v)
            {
                cnt[val[v]]++;
                v=lastv[v];
            }
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        Init();
        for(int i=1;i<=n;++i)
        {
            scanf("%s",pstr[i]);
            insert(pstr[i],i);
        }
        build();
        memset(cnt,0,sizeof(cnt));
        scanf("%s",str);
        find(str);
        for(int i=1;i<=n;++i)
        {
            if(cnt[i])
                printf("%s: %d\n",pstr[i],cnt[i]);
        }
    }
    return 0;
}

