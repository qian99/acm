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
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=5000+10;
const int maxm=400000+10;
struct DLX
{
    int L[maxm],R[maxm],U[maxm],D[maxm];
    int row[maxm],col[maxm],head[maxm],ans[maxm],cnt[maxm];
    int tot,size;
    void Init(int n)
    {
        for(int i=0;i<=n;++i)
        {
            L[i]=i-1;R[i]=i+1;
            U[i]=D[i]=i;cnt[i]=0;
        }
        L[0]=n;R[n]=0;size=n+1;
        //memset(head,0xff,sizeof(head));
    }
    void AddLink(int r,int c)
    {
        U[size]=U[c];D[size]=c;
        D[U[c]]=size;U[c]=size;
        if(head[r]==-1) head[r]=L[size]=R[size]=size;
        else
        {
            int h=head[r];
            L[size]=L[h];R[size]=h;
            R[L[h]]=size;L[h]=size;
        }
        cnt[c]++;row[size]=r;col[size++]=c;
    }
    void remove(int c)
    {
        L[R[c]]=L[c];R[L[c]]=R[c];
        for(int i=U[c];i!=c;i=U[i])
            for(int j=R[i];j!=i;j=R[j])
            {
                U[D[j]]=U[j];D[U[j]]=D[j];
                cnt[col[j]]--;
            }
    }
    void restore(int c)
    {
        for(int i=U[c];i!=c;i=U[i])
            for(int j=R[i];j!=i;j=R[j])
            {
                U[D[j]]=D[U[j]]=j;
                cnt[col[j]]++;
            }
        R[L[c]]=L[R[c]]=c;
    }
    bool Dancing(int x)
    {
        if(R[0]==0)
        {
            tot=x;
            return true;
        }
        int c=R[0];
        for(int i=R[0];i;i=R[i]) if(cnt[c]>cnt[i]) c=i;
        remove(c);
        for(int i=U[c];i!=c;i=U[i])
        {
            ans[x]=row[i];
            for(int j=R[i];j!=i;j=R[j]) remove(col[j]);
            if(Dancing(x+1)) return true;
            for(int j=L[i];j!=i;j=L[j]) restore(col[j]);
        }
        restore(c);
        return false;
    }
}dlx;
int G[110][110];
int id[110][6][6],conv[5111][3],res[110][2],invcnt;
int n,m,d;
void init(int n,int d)
{
    memset(G,0,sizeof(G));
    invcnt=0;
    for(int i=1;i<=n;++i)
    {
        id[i][0][0]=++invcnt;
        conv[invcnt][0]=i;
        conv[invcnt][1]=conv[invcnt][2]=0;
        for(int j=1;j<=d;++j)
            for(int k=j;k<=d;++k)
            {
                id[i][j][k]=++invcnt;
                conv[invcnt][0]=i;
                conv[invcnt][1]=j;conv[invcnt][2]=k;
            }
    }
    for(int i=0;i<=invcnt;++i) dlx.head[i]=-1;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d%d",&n,&m,&d))
    {
        int N=n*d+n;
        init(n,d);
        dlx.Init(N);
        int u,v,s,t,r;
        while(m--)
        {
            scanf("%d%d",&u,&v);
            G[u][v]=G[v][u]=1;
        }
        for(int i=1;i<=n;++i)
        {
            scanf("%d%d",&s,&t);
            G[i][i]=1;
            r=id[i][0][0];
            dlx.AddLink(r,n*d+i);
            for(int j=s;j<=t;++j)
                for(int k=j;k<=t;++k)
                {
                    r=id[i][j][k];
                    dlx.AddLink(r,n*d+i);
                    for(int v=1;v<=n;++v)
                        if(G[i][v])
                        for(int x=j;x<=k;++x)
                            dlx.AddLink(r,(v-1)*d+x);
                }
        }
        if(dlx.Dancing(0))
        {
            memset(res,0,sizeof(res));
            for(int i=0;i<dlx.tot;++i)
            {
                int u;
                u=conv[dlx.ans[i]][0];
                res[u][0]=conv[dlx.ans[i]][1];
                res[u][1]=conv[dlx.ans[i]][2];
            }
            for(int i=1;i<=n;++i)
                printf("%d %d\n",res[i][0],res[i][1]);
        }
        else printf("No solution\n");
        printf("\n");
    }
    return 0;
}
