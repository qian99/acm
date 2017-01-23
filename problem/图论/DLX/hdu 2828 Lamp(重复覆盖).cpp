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
const int maxm=100000+10;
struct DLX
{
    int U[maxm],D[maxm],L[maxm],R[maxm];
    int head[maxm],cnt[maxm],row[maxm],col[maxm];
    bool vis[maxm];
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
        memset(vis,0,sizeof(vis));
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
        cnt[c]++;col[size]=c;row[size++]=r;
    }
    void remove(int c)
    {
        for(int i=U[c];i!=c;i=U[i])
        {
            R[L[i]]=R[i];
            L[R[i]]=L[i];
        }
    }
    void restore(int c)
    {
        for(int i=U[c];i!=c;i=U[i])
        {
            L[R[i]]=R[L[i]]=i;
        }
    }
    bool Dancing()
    {
        if(R[0]==0) return true;
        int c=R[0];
        for(int i=R[0];i;i=R[i]) if(cnt[c]>cnt[i]) c=i;
        for(int i=U[c];i!=c;i=U[i])
        {
            if(vis[row[i]^1]) continue;
            vis[row[i]]=true;
            remove(i);
            for(int j=R[i];j!=i;j=R[j]) remove(j);
            if(Dancing()) return true;
            for(int j=L[i];j!=i;j=L[j]) restore(j);
            restore(i);
            vis[row[i]]=false;
        }
        return false;
    }
}dlx;
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    char str[7];
    while(~scanf("%d%d",&n,&m))
    {
        dlx.Init(n);
        for(int i=1;i<=n;++i)
        {
            int k,u;
            scanf("%d",&k);
            while(k--)
            {
                scanf("%d%s",&u,str);
                if(str[1]=='N')
                    dlx.AddLink((u-1)<<1,i);
                else dlx.AddLink((u-1)<<1|1,i);
            }
        }
        if(dlx.Dancing())
        {
            for(int i=0;i<m*2;i+=2)
            {
                if(i) printf(" ");
                if(dlx.vis[i]) printf("ON");
                else printf("OFF");
            }
            printf("\n");
        }
        else puts("-1");
    }
    return 0;
}
