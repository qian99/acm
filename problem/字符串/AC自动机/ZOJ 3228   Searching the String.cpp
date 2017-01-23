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
const int maxm=600000+10;
const int maxn=100000+10;
int ch[maxm][26],next[maxm],lastv[maxm],val[maxm],size;
int slen[maxn],ans[maxn][2],type[maxn],flag[maxn][2],id[maxn];
char str[maxn],ss[11];
void Init()
{
    memset(ch[0],0,sizeof(ch[0]));
    memset(slen,0,sizeof(slen));
    memset(ans,0,sizeof(ans));
    memset(id,0,sizeof(id));
    memset(flag,0xff,sizeof(flag));
    next[0]=lastv[0]=0;
    val[0]=size=0;
}
void Insert(const char *s,int v)
{
    int u=0,n=strlen(s);
    for(int i=0;i<n;++i)
    {
        int c=s[i]-'a';
        if(!ch[u][c])
        {
            ch[u][c]=++size;
            memset(ch[size],0,sizeof(ch[size]));
            next[size]=val[size]=lastv[size]=0;
        }
        u=ch[u][c];
    }
    val[u]=v;
    slen[v]=n;
}
void build()
{
    queue<int>q;
    for(int c=0;c<26;++c)
        if(ch[0][c]) q.push(ch[0][c]);
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
void solve()
{
    int n=strlen(str);
    int u=0,v,c,t;
    for(int i=0;i<n;++i)
    {
        c=str[i]-'a';
        u=ch[u][c];
        if(val[u]||lastv[u])
        {
            v=val[u]?u:lastv[u];
            while(v)
            {
                t=val[v];
                flag[t][0]=i;
                ans[t][0]++;
                if(i>=flag[t][1]+slen[t])
                {
                    flag[t][1]=i;
                    ans[t][1]++;
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
    int n,tcase=0;
    map<string,int>mp;
    while(~scanf("%s",str))
    {
        tcase++;
        Init();
        scanf("%d",&n);
        mp.clear();
        int u;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&type[i]);
            scanf("%s",ss);
            u=mp[(string)ss];
            if(u) id[i]=u;
            else
            {
                id[i]=i;
                Insert(ss,i);
                mp[(string)ss]=i;
            }
        }
        build();
        solve();
        printf("Case %d\n",tcase);
        for(int i=1;i<=n;++i)
            printf("%d\n",ans[id[i]][type[i]]);
        printf("\n");
    }
    return 0;
}
