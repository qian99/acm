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
const int maxn=200;
const int maxm=100+10;
const int maxl=1000000+10;
char pat[maxn][maxm],str[maxl];
int ch[20010][26],val[20010],size,lastv[20010],next[20010];
int cnt[maxn],maxv;
void Init()
{
    memset(cnt,0,sizeof(cnt));
    memset(ch[0],0,sizeof(ch[0]));
    val[0]=0;size=0;maxv=0;
}
void insert(const char * s,int v)
{
    int u=0,n=strlen(s);
    for(int i=0;i<n;++i)
    {
        int c=s[i]-'a';
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
    memset(lastv,0,sizeof(lastv));
    memset(next,0,sizeof(next));
    for(int i=0;i<26;++i)
        if(ch[0][i]) {q.push(ch[0][i]);}
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int c=0;c<26;++c)
        {
            int v=ch[u][c];
            if(!v) {ch[u][c]=ch[next[u]][c];continue;}
            q.push(v);
            int j=next[u];
            while(j&&!ch[j][c]) j=next[j];
            next[v]=ch[j][c];
            lastv[v]=val[next[v]]?next[v]:lastv[next[v]];
        }
    }
}
void find(const char * s)
{
    int n=strlen(s);
    int j=0;
    for(int i=0;i<n;++i)
    {
        int c=s[i]-'a';
        j=ch[j][c];
        if(val[j]||lastv[j])
        {
            int u=val[j]?j:lastv[j];
            while(u)
            {
                cnt[val[u]]++;
                maxv=max(maxv,cnt[val[u]]);
                u=lastv[u];
            }
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    map<string,int>mp;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        mp.clear();
        Init();
        int tmp;
        for(int i=1;i<=n;++i)
        {
            scanf("%s",pat[i]);
            tmp=mp[string(pat[i])];
            if(tmp) mp[string(pat[i])]=tmp;
            else
            {
                mp[string(pat[i])]=i;
                insert(pat[i],i);
            }
        }
        build();
        scanf("%s",str);
        find(str);
        printf("%d\n",maxv);
        for(int i=1;i<=n;++i)
        {
            tmp=mp[string(pat[i])];
            if(cnt[tmp]==maxv)
                printf("%s\n",pat[i]);
        }
    }
    return 0;
}

