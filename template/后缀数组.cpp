char s[maxn];
int sa[maxn],t[maxn],t2[maxn],c[maxn];
int height[maxn],rank[maxn];
void build_sa(int n,int m)
{
    int i,*x=t,*y=t2;
    for(i=0;i<m;++i) c[i]=0;
    for(i=0;i<n;++i) c[x[i]=s[i]]++;
    for(i=1;i<m;++i) c[i]+=c[i-1];
    for(i=n-1;i>=0;--i) sa[--c[x[i]]]=i;
    for(int k=1;k<=n;k<<=1)
    {
        int p=0;
        for(i=n-k;i<n;++i) y[p++]=i;
        for(i=0;i<n;++i) if(sa[i]>=k) y[p++]=sa[i]-k;
        for(i=0;i<m;++i) c[i]=0;
        for(i=0;i<n;++i) c[x[y[i]]]++;
        for(i=1;i<m;++i) c[i]+=c[i-1];
        for(i=n-1;i>=0;--i) sa[--c[x[y[i]]]]=y[i];
        swap(x,y);
        p=1;x[sa[0]]=0;
        for(i=1;i<n;++i)
            x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])?p-1:p++;
        if(p>=n) break;
        m=p;
    }
}
void getHeight(int n)
{
    int i,j,k=0;
    for(i=0;i<=n;++i) rank[sa[i]]=i;
    for(i=0;i<n;++i)
    {
        if(k) k--;
        j=sa[rank[i]-1];
        while(s[i+k]==s[j+k]) k++;
        height[rank[i]]=k;
    }
}
int d[maxn][21];
int Log[maxn];
void Init_Rmq(int n)
{
    Log[0]=-1;
    for(int i=1;i<=n;++i) Log[i]=(i&(i-1))?Log[i-1]:Log[i-1]+1;
    for(int i=1;i<=n;++i) d[i][0]=height[i];
    for(int i=1;i<=Log[n];++i)
        for(int j=1;j+(1<<i)-1<=n;++j)
            d[j][i]=min(d[j][i-1],d[j+(1<<(i-1))][i-1]);
}
int lcp(int L,int R)
{
    L=rank[L],R=rank[R];
    if(L>R) swap(L,R);
    L++;
    int t=Log[R-L+1];
    return min(d[L][t],d[R-(1<<t)+1][t]);
}