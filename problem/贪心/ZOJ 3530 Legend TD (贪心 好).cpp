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
ll Gold[maxn];
ll solve(ll n,ll cost,ll W)
{
    ll sum=0,tmp,num;
    ll F=0;
    for(int i=0;i<=n;++i)
    {
        sum+=F*W;
        num=Gold[i]/cost;
        Gold[i+1]+=Gold[i]%cost;
        if(F>W)
        {
            if(W+num<=F)
            {
                W+=num;
                num=0;
            }
            else
            {
                tmp=F-W;
                W+=tmp;
                num-=tmp;
                F+=num/2;
                W+=num/2;
                num&=1;
                if(num)
                {
                    if((F+1)*W>(W+1)*F) F++;
                    else W++;
                }
            }
        }
        else
        {
            if(F+num<=W)
            {
                F+=num;
                num=0;
            }
            else
            {
                tmp=W-F;
                F+=tmp;
                num-=tmp;
                W+=num/2;
                F+=num/2;
                num&=1;
                if(num)
                {
                    if((F+1)*W>(W+1)*F) F++;
                    else W++;
                }
            }
        }
    }
    return sum;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ll n,F,W,G;
    while(~scanf("%lld%lld%lld%lld",&n,&F,&W,&G))
    {
        ll Att,Gd,last,Def=0,tmp;
        memset(Gold,0,sizeof(Gold));
        bool flag=true;
        Gold[0]+=G;
        for(int i=1;i<=n;++i)
        {
            scanf("%lld%lld",&Att,&Gd);
            if(!flag) continue;
            if(Att>Def)
            {
                last=i-1;
                while(last>=0&&Att>Def)
                {
                    if(Gold[last])
                    {
                        if(Gold[last]+Def>=Att)
                        {
                            tmp=(Att-Def);
                            Def+=tmp;
                            Gold[last]-=tmp;
                        }
                        else
                        {
                            Def+=Gold[last];
                            Gold[last]=0;
                        }
                    }
                    if(Gold[last]) break;
                    last--;
                }
                if(Att>Def) flag=false;
            }
            Gold[i]+=Gd;
        }
        if(!flag) printf("It's useless to collect wood.\n");
        else
        {
            ll ans=solve(n,F,W);
            printf("%lld\n",ans);
        }
    }
    return 0;
}
