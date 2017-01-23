#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<set>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
int md[15]={0,31,29,31,30,31,30,31,31,30,31,30,31};
const char *Ms[13]={"","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sept","Oct","Nov","Dec"};
const int maxn=100000+10;
const int maxt=1440;
struct Classes
{
    int smon,sday,s;
    int tmon,tday,t;
    double val;
    bool operator <(const Classes &a) const
    {
        if(tmon!=a.tmon) return tmon<a.tmon;
        if(tday!=a.tday) return tday<a.tday;
        return t<a.t;
    }
}cs[maxn];
int getmon(const char *s)
{
    for(int i=1;i<=12;++i)
    {
        bool flag=true;
        for(int j=0;j<3;++j)
            if(s[j]!=Ms[i][j]) {flag=false;break;}
        if(flag) return i;
    }
    return 0;
}
int gettime(int hour,int second,const char *s)
{
    if(s[0]=='p') hour+=12;
    return hour*60+second;
}
int getdays(const char *s)
{
    int res=0;
    int i=0;
    while(s[i]>='0'&&s[i]<='9')
    {
        res=res*10+(s[i]-'0');
        i++;
    }
    return res;
}
char str[20];
double dp[maxn],maxv[maxn];
bool check(Classes a,Classes b)
{
    a.t+=5;
    if(a.t>=maxt)
    {
        a.tday++;
        a.t=a.t-maxt;
    }
    if(a.tday>md[a.tmon])
    {
        a.tday=1;
        a.tmon++;
    }
    if(a.tmon!=b.smon) return a.tmon<b.smon;
    if(a.tday!=b.sday) return a.tday<b.sday;
    return a.t<=b.s;
}
int f(int l,int r,int p)
{
    if(!check(cs[l],cs[p])) return -1;
    int ans=l;
    l++;
    while(l<r)
    {
        int m=(l+r)>>1;
        if(check(cs[m],cs[p]))
        {
            ans=m;
            l=m+1;
        }
        else r=m;
    }
    if(check(cs[r],cs[p])) ans=max(r,ans);
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        if(n==0)
        {
            printf("0.0\n");
            continue;
        }
        int h,s;
        for(int i=0;i<n;++i)
        {
            scanf("%s",str);
            cs[i].smon=getmon(str);
            scanf("%s",str);
            cs[i].sday=getdays(str);
            scanf("%d:%d %s",&h,&s,str);
            cs[i].s=gettime(h,s,str);

            scanf("%s",str);
            cs[i].tmon=getmon(str);
            scanf("%s",str);
            cs[i].tday=getdays(str);
            scanf("%d:%d %s",&h,&s,str);
            cs[i].t=gettime(h,s,str);
            scanf("%lf",&cs[i].val);
        }
        sort(cs,cs+n);
        dp[0]=maxv[0]=cs[0].val;
        for(int i=1;i<n;++i)
        {
            int p=f(0,i-1,i);
            if(p==-1) dp[i]=cs[i].val;
            else dp[i]=maxv[p]+cs[i].val;
            maxv[i]=max(maxv[i-1],dp[i]);
        }
        printf("%.1lf\n",maxv[n-1]);
    }
    return 0;
}
