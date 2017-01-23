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
const int maxn=100000+10;
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
int lenv[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int tcase=0;
    while(~scanf("%s",s))
    {
        if(s[0]=='#') break;
        tcase++;
        int n=strlen(s);
        build_sa(n+1,200);
        getHeight(n);
        Init_Rmq(n);
        int tot=0,maxv=-1,k,R,tmp;
        for(int l=1;l<n;++l)
            for(int i=0;i+l<n;i+=l)
            {
                k=lcp(i,i+l);
                R=k/l+1;
                tmp=l-k%l;
                tmp=i-tmp;
                if(tmp>=0&&k%l!=0)
                    if(lcp(tmp,tmp+l)) R++;
                if(R>maxv)
                {
                    tot=0;
                    maxv=R;
                    lenv[tot++]=l;
                }
                else if(R==maxv)
                    lenv[tot++]=l;
            }
        int start=0,end=0;
        bool find=false;
        for(int i=1;i<=n&&!find;++i)
        {
            for(int j=0;j<tot;++j)
            {
                tmp=lenv[j];
                if(lcp(sa[i],sa[i]+tmp)>=(maxv-1)*tmp)
                {
                    start=sa[i];
                    end=sa[i]+maxv*tmp-1;
                    find=true;
                    break;
                }
            }
        }
        printf("Case %d: ",tcase);
        for(;start<=end;start++)
            putchar(s[start]);
        printf("\n");
    }
    return 0;
}

