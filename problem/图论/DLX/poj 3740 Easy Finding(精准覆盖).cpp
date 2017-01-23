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
const int maxm=110000+10;
struct DLX
{
    int L[maxm],R[maxm],U[maxm],D[maxm];
    int row[maxm],col[maxm],head[maxn],ans[maxn],cnt[maxn];
    int n,tot,size;
    void Init(int n)
    {
        this->n=n;
        for(int i=0;i<=n;++i)
        {
            L[i]=i-1;R[i]=i+1;
            U[i]=D[i]=i;cnt[i]=0;
        }
        L[0]=n;R[n]=0;size=n+1;
        memset(head,0xff,sizeof(head));
    }
    void AddLinks(int r,int c)
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
                --cnt[col[j]];
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
        L[R[c]]=c;R[L[c]]=c;
    }
    bool Dancing(int x)
    {
        if(R[0]==0)
        {
            tot=x;
            return true;
        }
        int c=R[0];
        for(int i=R[0];i;i=R[i]) if(R[c]>R[i]) c=i;
        remove(c);
        for(int i=U[c];i!=c;i=U[i])
        {
            ans[x]=row[i];
            for(int j=R[i];j!=i;j=R[j]) remove(col[j]);
            if(Dancing(x+1)) return true;
            for(int j=R[i];j!=i;j=R[j]) restore(col[j]);
        }
        restore(c);
        return false;
    }
}dlx;
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        dlx.Init(m);
        int v;
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=m;++j)
            {
                scanf("%d",&v);
                if(v) dlx.AddLinks(i,j);
            }
        }
        if(dlx.Dancing(0))
            puts("Yes, I found it");
        else puts("It is impossible");
    }
    return 0;
}
