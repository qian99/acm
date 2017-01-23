//æ´◊º∏≤∏«
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


//÷ÿ∏¥∏≤∏«
const int maxn=10000+10;
struct DLX
{
    int U[maxn],D[maxn],L[maxn],R[maxn];
    int cnt[maxn],col[maxn],row[maxn],head[maxn],tot,size;
    bool vis[110];
    void Init(int n)
    {
        for(int i=0;i<=n;++i)
        {
            L[i]=i-1;R[i]=i+1;
            U[i]=D[i]=i;cnt[i]=0;
        }
        L[0]=n;R[n]=0;size=n+1;
        tot=inf;
        memset(head,0xff,sizeof(head));
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
        for(int i=U[c];i!=c;i=U[i])
        {
            L[R[i]]=L[i];
            R[L[i]]=R[i];
        }
    }
    void restore(int c)
    {
        for(int i=U[c];i!=c;i=U[i])
            L[R[i]]=R[L[i]]=i;
    }
    int h()
    {
        memset(vis,0,sizeof(vis));
        int res=0;
        for(int i=R[0];i;i=R[i])
        {
            if(vis[i]) continue;
            res++;
            for(int j=U[i];j!=i;j=U[j])
                for(int k=R[j];k!=j;k=R[k])
                    vis[col[k]]=true;
        }
        return res;
    }
    void Dancing(int x)
    {
        if(x+h()>=tot) return ;
        if(R[0]==0)
        {
            tot=min(tot,x);
            return ;
        }
        int c=R[0];
        for(int i=R[0];i;i=R[i]) if(cnt[c]>cnt[i]) c=i;
        for(int i=U[c];i!=c;i=U[i])
        {
            remove(i);
            for(int j=R[i];j!=i;j=R[j]) remove(j);
            Dancing(x+1);
            for(int j=L[i];j!=i;j=L[j]) restore(j);
            restore(i);
        }
    }
}dlx;