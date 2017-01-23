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
const int maxn=200+10;
const int mod=100000;
int ch[maxn][4],next[maxn],flag[maxn],size;
int indx[maxn];
void Init()
{
    memset(ch[0],0,sizeof(ch[0]));
    memset(next,0,sizeof(next));
    indx['A']=0;indx['C']=1;indx['T']=2;indx['G']=3;
    size=0;
}
void Insert(const char * s)
{
    int u=0,n=strlen(s);
    for(int i=0;i<n;++i)
    {
        int c=indx[s[i]];
        if(!ch[u][c])
        {
            ch[u][c]=++size;
            memset(ch[size],0,sizeof(ch[size]));
            flag[size]=0;
        }
        u=ch[u][c];
    }
    flag[u]=1;
}
void build()
{
    queue<int>q;
    for(int i=0;i<4;++i)
        if(ch[0][i]) q.push(ch[0][i]);
    int r,u,v;
    while(!q.empty())
    {
        r=q.front();q.pop();
        for(int c=0;c<4;++c)
        {
            u=ch[r][c];
            if(!u) {ch[r][c]=ch[next[r]][c];continue;}
            q.push(u);
            v=next[r];
            while(v&&!ch[v][c]) v=next[v];
            next[u]=ch[v][c];
            flag[u]|=flag[next[u]];
        }
    }
}
char str[55];
ll matrix[maxn][maxn],res[maxn][maxn],tmp[maxn][maxn];
void mul(ll a[maxn][maxn],ll b[maxn][maxn])
{
    for(int i=0;i<=size;++i)
        for(int j=0;j<=size;++j)
        {
            tmp[i][j]=0;
            for(int k=0;k<=size;++k)
            {
                tmp[i][j]+=a[i][k]*b[k][j];
                tmp[i][j]%=mod;
            }
        }
    for(int i=0;i<=size;++i)
        for(int j=0;j<=size;++j)
            b[i][j]=tmp[i][j];
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int m,n;
    Init();
    scanf("%d%d",&m,&n);
    for(int i=0;i<m;++i)
    {
        scanf("%s",str);
        Insert(str);
    }
    build();
    memset(matrix,0,sizeof(matrix));
    memset(res,0,sizeof(res));
    for(int i=0;i<=size;++i)
    {
        if(flag[i]) continue;
        for(int c=0;c<4;++c)
            if(!flag[ch[i][c]])
                matrix[i][ch[i][c]]++;
    }
    for(int i=0;i<=size;++i) res[i][i]=1;
    while(n)
    {
        if(n&1) mul(matrix,res);
        mul(matrix,matrix);
        n>>=1;
    }
    int ans=0;
    for(int i=0;i<=size;++i)
        ans=(ans+res[0][i])%mod;
    printf("%d\n",ans);
    return 0;
}
