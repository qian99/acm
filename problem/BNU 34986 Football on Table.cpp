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
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=510+10;
double et[maxn],x,y,dx,dy,W,L;
double cal(vector<double> w,vector<double> d,double a)
{
    double sum=0,ans=0;
    int tot=0;
    for(int i=0;i<(int)w.size();++i)
    {
        if(i) sum+=d[i-1];
        et[tot++]=sum;
        et[tot++]=sum+w[i];
        sum+=w[i];
    }
    double py,now;
    py=(a-x)/dx*dy+y;
    if(py<0||py>W) return 1;
    now=py;
//    if(py>sum) ans+=py-sum;
    if(W-sum>py) ans+=W-sum-py;
    while(tot>0&&et[tot-1]>py) tot--;
    if(tot&1) now=et[tot-1];
    else ans+=now-et[tot-1],now=et[tot-1];
    for(int i=tot-1;i>0;--i)
    {
        if(py-now>=W-sum) break;
        if(i&1)
        {
            now=et[i-1];
            continue;
        }
        if(py-et[i-1]>=W-sum)
        {
            ans+=W-sum-(py-now);
            now=W-sum;
            break;
        }
        else
        {
            ans+=now-et[i-1];
            now=et[i-1];
        }
    }
    return ans/(W-sum);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%lf%lf",&L,&W);
        scanf("%lf%lf%lf%lf",&x,&y,&dx,&dy);
        int m,k;
        scanf("%d",&m);
        vector<double>w,d;
        double xp,ans=1.0,tmp;
        while(m--)
        {
            w.clear();
            d.clear();
            scanf("%lf%d",&xp,&k);
            for(int i=0;i<k;++i)
            {
                scanf("%lf",&tmp);
                w.push_back(tmp);
            }
            for(int i=0;i<k-1;++i)
            {
                scanf("%lf",&tmp);
                d.push_back(tmp);
            }
            ans*=cal(w,d,xp);
        }
        printf("Case #%d: %.5lf\n",++tcase,ans);
    }
    return 0;
}
