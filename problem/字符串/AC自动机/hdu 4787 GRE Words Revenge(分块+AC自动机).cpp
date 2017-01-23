#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<vector>
#include<bitset>
#include<set>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100000+100;
const int maxm=5000000+10;
const int Size=2333;
char str[maxn],pargraph[maxm],stmp[maxm];
int S[maxn],T[maxn];
struct AC
{
    int ch[maxn*2][2],val[maxn*2],next[maxn*2],lastv[maxn*2];
    int size;
    void Init()
    {
        ch[0][0]=ch[0][1]=0;
        val[0]=size=0;
    }
    void Insert(const char * s,int L,int R)
    {
        int u=0,c;
        for(int i=L;i<=R;++i)
        {
            c=s[i]-'0';
            if(!ch[u][c])
            {
                ch[u][c]=++size;
                ch[size][0]=ch[size][1]=0;
                val[size]=0;
            }
            u=ch[u][c];
        }
        val[u]=1;
    }
    bool check(const char * s,int L,int R)
    {
        int u=0,c;
        for(int i=L;i<=R;++i)
        {
            c=s[i]-'0';
            if(!ch[u][c]) return false;
            u=ch[u][c];
        }
        return val[u];
    }
    void build()
    {
        queue<int>q;
        memset(next,0,sizeof(int)*(size+2));
        memset(lastv,0,sizeof(int)*(size+2));
        if(ch[0][0]) q.push(ch[0][0]);
        if(ch[0][1]) q.push(ch[0][1]);
        int u,v;
        while(!q.empty())
        {
            u=q.front();q.pop();
            for(int c=0;c<2;++c)
            {
                v=ch[u][c];
                if(!v) { continue; }
                q.push(v);
                int j=next[u];
                while(j&&!ch[j][c]) j=next[j];
                next[v]=ch[j][c];
                lastv[v]=val[next[v]]?next[v]:lastv[next[v]];
            }
        }
    }
    int Find(const char *s,int len)
    {
        int u=0,v,c;
        int cnt=0;
        for(int i=0;i<len;++i)
        {
            c=s[i]-'0';
            while(u&&!ch[u][c]) u=next[u];
            u=ch[u][c];
            if(val[u]||lastv[u])
            {
                v=val[u]?u:lastv[u];
                while(v)
                {
                    cnt+=val[v];
                    v=lastv[v];
                }
            }
        }
        return cnt;
    }
}BigAc,SmallAc;
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        int L=0,tot=0,len,csize=0,pre=0;
        S[0]=T[0]=0;
        BigAc.Init();
        SmallAc.Init();
        scanf("%d",&n);
        printf("Case #%d:\n",++tcase);
        while(n--)
        {
            scanf("%s",stmp);
            len=strlen(stmp);
            int p=L%(len-1),m=0;
            for(int i=p+1;i<len;++i)
                pargraph[m++]=stmp[i];
            for(int i=1;i<=p;++i)
                pargraph[m++]=stmp[i];
            if(stmp[0]=='+')
            {
                for(int i=1;i<len;++i)
                    str[T[tot]+i]=pargraph[i-1];
                tot++;
                S[tot]=T[tot-1]+1;
                T[tot]=T[tot-1]+len-1;
                if(BigAc.check(str,S[tot],T[tot])||SmallAc.check(str,S[tot],T[tot])) {tot--;continue;}
                csize+=len-1;
                if(csize>Size)
                {
                    for(int j=pre+1;j<=tot;++j)
                        BigAc.Insert(str,S[j],T[j]);
                    BigAc.build();
                    SmallAc.Init();
                    pre=tot;csize=0;
                }
                else
                {
                    SmallAc.Insert(str,S[tot],T[tot]);
                    SmallAc.build();
                }
            }
            else
            {
                int ans=0;
                ans+=BigAc.Find(pargraph,m);
                ans+=SmallAc.Find(pargraph,m);
                L=ans;
                printf("%d\n",ans);
            }
        }
    }
    return 0;
}
