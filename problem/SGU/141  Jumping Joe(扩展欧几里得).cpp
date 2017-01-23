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
void ext_gcd(ll a,ll b,ll & x,ll & y,ll & d)
{
    if(b==0)
    {
        d=a;x=1;y=0;
        return ;
    }
    ext_gcd(b,a%b,y,x,d);
    y-=(a/b)*x;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ll x,y,p,k,d,tmp;
    ll N1,N2,P1,P2,ta,tb;
    cin>>x>>y>>p>>k;
    if(p==0&&k==0)
    {
        cout<<"YES"<<endl;
        cout<<"0 0 0 0"<<endl;
        return 0;
    }
    ext_gcd(x,y,P1,P2,d);
    if(p%d) {cout<<"NO"<<endl;return 0;}
    ta=x/d;tb=y/d;
    P1=P1*(p/d);
    P2=P2*(p/d);
    while(abs(P1)+abs(P2)>abs(P1-tb)+abs(P2+ta)) {P1-=tb;P2+=ta;}
    while(abs(P1)+abs(P2)>abs(P1+tb)+abs(P2-ta)) {P1+=tb;P2-=ta;}
    if(abs(P1)+abs(P2)>k)
    {
        cout<<"NO"<<endl;
        return 0;
    }
    N1=N2=0;
    tmp=k-abs(P1)-abs(P2);
    if(tmp%2==0)
    {
        if(P1<0) swap(P1,N1),N1=-N1;
        if(P2<0) swap(P2,N2),N2=-N2;
        P1+=(tmp/2);
        N1+=(tmp/2);
    }
    else
    {
        if((ta+tb)%2==0)
        {
            printf("NO\n");
            return 0;
        }
        else
        {
            if(abs(P1+tb)+abs(P2-ta)<abs(P1-tb)+abs(P2+ta))
            {
                P1+=tb;
                P2-=ta;
            }
            else
            {
                P1-=tb;
                P2+=ta;
            }
            if(abs(P1)+abs(P2)>k)
            {
                printf("NO\n");
                return 0;
            }
            k-=abs(P1)+abs(P2);
            if(P1<0) swap(P1,N1),N1=-N1;
            if(P2<0) swap(P2,N2),N2=-N2;
            P1+=(k/2);
            N1+=(k/2);
        }
    }
    cout<<"YES"<<endl;
    cout<<P1<<" "<<N1<<" "<<P2<<" "<<N2<<endl;
    return 0;
}

