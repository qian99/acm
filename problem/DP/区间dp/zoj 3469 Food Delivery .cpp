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
const int maxn=1000+10;
int dp[maxn][maxn][2];
vector<pair<int,int> >vl,vr;
int f(int l,int r,int k)
{
    if(dp[l][r][k]!=-1)
        return dp[l][r][k];
    int& ret=dp[l][r][k];
    ret=inf;
    if(k==0)
    {
        if(l!=0)
        {
            int tmp=vl[l-1].second+vr[r].second;
            ret=min(ret,f(l-1,r,0)+(vl[l].first-vl[l-1].first)*tmp);
            ret=min(ret,f(l-1,r,1)+(vr[r].first+vl[l].first)*tmp);
        }
    }
    else
    {
        if(r!=0)
        {
            int tmp=vr[r-1].second+vl[l].second;
            ret=min(ret,f(l,r-1,1)+(vr[r].first-vr[r-1].first)*tmp);
            ret=min(ret,f(l,r-1,0)+(vl[l].first+vr[r].first)*tmp);
        }
    }
    return ret;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,v,x;
    while(~scanf("%d%d%d",&n,&v,&x))
    {
        vl.clear();
        vr.clear();
        int xa,xb;
        for(int i=0;i<n;++i)
        {
            scanf("%d%d",&xa,&xb);
            if(xa>x)
                vr.push_back(make_pair(xa-x,xb));
            else if(xa<x)
                vl.push_back(make_pair(x-xa,xb));
        }
        vl.push_back(make_pair(0,0));
        vr.push_back(make_pair(0,0));
        int cntl=vl.size()-1,cntr=vr.size()-1;
        sort(vl.begin(),vl.end());
        sort(vr.begin(),vr.end());
        for(int i=0;i<cntl;++i)
            vl[i].second=vl[i+1].second;
        vl[cntl].second=0;
        for(int i=cntl;i>0;--i)
            vl[i-1].second+=vl[i].second;
         for(int i=0;i<cntr;++i)
            vr[i].second=vr[i+1].second;
        vr[cntr].second=0;
        for(int i=cntr;i>0;--i)
            vr[i-1].second+=vr[i].second;
        memset(dp,0xff,sizeof(dp));
        dp[0][0][0]=dp[0][0][1]=0;
        int ans=v*min(f(cntl,cntr,0),f(cntl,cntr,1));
        printf("%d\n",ans);
    }
    return 0;
}
