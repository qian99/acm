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
const int maxn=1000+10;
const int maxm=500000+10;
struct DLX
{
    int L[maxm],R[maxm],U[maxm],D[maxm];
    int row[maxm],col[maxm],head[maxn],ans[maxn],cnt[maxn];
    int tot,size;
    void Init(int n)
    {
        for(int i=0;i<=n;++i)
        {
            L[i]=i-1;R[i]=i+1;
            U[i]=D[i]=i;cnt[i]=0;
        }
        L[0]=n;R[n]=0;size=n+1;
        memset(head,0xff,sizeof(head));
        tot=inf;
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
    void Dancing(int x)
    {
        if(x>=tot) return ;
        if(R[0]==0)
        {
            tot=x;
            return ;
        }
        int c=R[0];
        for(int i=R[0];i;i=R[i]) if(cnt[c]>cnt[i]) c=i;
        remove(c);
        for(int i=U[c];i!=c;i=U[i])
        {
            ans[x]=row[i];
            for(int j=R[i];j!=i;j=R[j]) remove(col[j]);
            Dancing(x+1);
            for(int j=L[i];j!=i;j=L[j]) restore(col[j]);
        }
        restore(c);
    }
}dlx;
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n,m,p;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d",&n,&m,&p);
        dlx.Init(n*m);
        int x1,y1,x2,y2;
        for(int i=1;i<=p;++i)
        {
            scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
            if(x1>x2) swap(x1,x2);
            if(y1>y2) swap(y1,y2);
            x1++;y1++;
            for(int x=x1;x<=x2;++x)
                for(int y=y1;y<=y2;++y)
                {
                    dlx.AddLink(i,(x-1)*m+y);
                }
        }
        dlx.Dancing(0);
        if(dlx.tot==inf) dlx.tot=-1;
        printf("%d\n",dlx.tot);
    }
    return 0;
}
