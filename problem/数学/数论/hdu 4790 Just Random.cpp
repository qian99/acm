#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
#include<vector>
#include<queue>
using namespace std;
typedef long long ll;
struct Node
{
    ll prel,prer;
    ll sufl,sufr;
    ll z;
};
Node getNode(ll a,ll b,ll p)
{
    Node node;
    node.prel=a%p;
    node.z=0;
    ll pos=a+(p-node.prel-1);
    if(pos>b)
    {
        node.prer=b%p;
        node.sufl=node.sufr=-1;
    }
    else if(pos==b)
    {
        node.prer=b%p;
        node.sufl=node.sufr=-1;
    }
    else
    {
        node.prer=pos%p;
        if(b-pos<p)
        {
            node.sufl=(pos+1)%p;
            node.sufr=(b-pos)%p-1;
            node.z=0;
        }
        else
        {
            node.z=(b-pos)/p;
            ll tmp=(b-pos)%p;
            if(tmp==0)
            {
                node.sufl=node.sufr=-1;
            }
            else
            {
                node.sufl=0;
                node.sufr=(b-pos)%p-1;
            }
        }
    }
    return node;
}
ll getLen(ll a,ll b,ll c,ll d)
{
    if(a>d||b<c) return 0;
    if(a<c&&b>d) return d-c+1;
    if(b>=c&&b<=d) return b-max(a,c)+1;
    return min(b,d)-a+1;
}
ll gcd(ll a,ll b)
{
    return b==0?a:gcd(b,a%b);
}
int main()
{
    //freopen("in.txt","r",stdin);
    int t,tcase=0;
    ll a,b,c,d,m,p;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        scanf("%I64d%I64d%I64d%I64d",&a,&b,&c,&d);
        scanf("%I64d%I64d",&p,&m);
        Node x,y;
        x=getNode(a,b,p);
        y=getNode(c,d,p);
        ll ans=0;
        ll lx,ly,la=-1,lb=-1;
        //前前
        if(x.prer<=m)
          lx=m-x.prer,ly=m-x.prel;
        else if(x.prel>m)
          lx=p-(x.prer-m),ly=p-(x.prel-m);
        else
          lx=0,ly=m-x.prel,la=p-(x.prer-m),lb=p-1;
        ans+=getLen(y.prel,y.prer,lx,ly);
        if(la!=-1) ans+=getLen(y.prel,y.prer,la,lb);
        //前中
        ans+=(x.prer-x.prel+1)*y.z;
        //前后
        if(y.sufl!=-1)
        {
            ans+=getLen(y.sufl,y.sufr,lx,ly);
            if(la!=-1) ans+=getLen(y.sufl,y.sufr,la,lb);
        }
        //中前
        ans+=(y.prer-y.prel+1)*x.z;
        //中中
        ans+=x.z*y.z*p;
        //中后
        if(y.sufl!=-1) ans+=(y.sufr-y.sufl+1)*x.z;
        //后
        if(x.sufl!=-1)
        {
            //后前
            la=lb=-1;
            if(x.sufr<=m)
              lx=m-x.sufr,ly=m-x.sufl;
            else if(x.sufl>m)
              lx=p-(x.sufr-m),ly=p-(x.sufl-m);
            else
              lx=0,ly=m-x.sufl,la=p-(x.sufr-m),lb=p-1;
            ans+=getLen(y.prel,y.prer,lx,ly);
            if(la!=-1) ans+=getLen(y.prel,y.prer,la,lb);
            //后中
            ans+=(x.sufr-x.sufl+1)*y.z;
            //后后
            if(y.sufl!=-1) ans+=getLen(y.sufl,y.sufr,lx,ly);
            if(y.sufl!=-1&&la!=-1) ans+=getLen(y.sufl,y.sufr,la,lb);
        }
        ll fenmu=(b-a+1)*(d-c+1);
        ll g=gcd(ans,fenmu);
        fenmu/=g;
        ans/=g;
        printf("Case #%d: %I64d/%I64d\n",tcase,ans,fenmu);
    }
    return 0;
}
