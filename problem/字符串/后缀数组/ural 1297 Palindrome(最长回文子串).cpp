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
const int maxn=3000+10;
char s[maxn];
int sa[maxn],t[maxn],t2[maxn],c[maxn];
int rank[maxn],height[maxn];
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
int d[maxn][20];
void Rmq_init(int n)
{
    for(int i=1;i<=n;++i) d[i][0]=height[i];
    for(int j=1;(1<<j)<=n;++j)
        for(int i=1;i+(1<<j)-1<=n;++i)
            d[i][j]=min(d[i][j-1],d[i+(1<<(j-1))][j-1]);
}
int lcp(int L,int R)
{
    L=rank[L];R=rank[R];
    if(L>R) swap(L,R);
    L++;
    int k=0;
    while(1<<(k+1)<=R-L+1) k++;
    return min(d[L][k],d[R-(1<<k)+1][k]);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%s",s);
    int n=strlen(s);
    for(int i=1;i<=n;++i)
        s[i+n]=s[n-i];
    s[n]='$';
    s[n*2+1]=0;
    build_sa(n*2+1,300);
    getHeight(n*2);
    Rmq_init(n*2);
    int maxl=1,L=0,R=0,tmp;
    for(int i=0;i<n;++i)
    {
        //ÆæÊý
        if(i<n-2)
        {
            tmp=lcp(i+1,n*2-(i+1));
            if(tmp>1&&tmp*2-1>maxl)
            {
                maxl=tmp*2-1;
                L=i+2-tmp;
                R=i+tmp;
            }
        }
        //Å¼Êý
        tmp=lcp(i+1,n*2-i);
        if(tmp*2>maxl)
        {
            maxl=tmp*2;
            L=i-tmp+1;
            R=i+tmp;
        }
    }
    for(int i=L;i<=R;++i)
        printf("%c",s[i]);
    printf("\n");
    return 0;
}
