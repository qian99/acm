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
using namespace std;
typedef long long ll;
const int maxn=4000+10;
char str[maxn];
ll sum[maxn];
int num[maxn];
ll flag[40010];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ll a;
    while(~scanf("%I64d",&a))
    {
        scanf("%s",str);
        int len=strlen(str);
        if(a==0)
        {
            int cnt=-1;
            memset(num,0,sizeof(num));
            if(str[0]=='0') num[++cnt]=1;
            for(int i=1;i<len;++i)
              if(str[i]=='0'&&str[i-1]=='0') num[cnt]++;
              else if(str[i]=='0') num[++cnt]=1;
            ll rnt=0;
            for(int i=0;i<=cnt;++i)
              rnt+=(ll)(num[i]+1)*(len+1)*num[i]*len/2;
            for(int i=0;i<=cnt;++i)
              for(int j=0;j<=cnt;++j)
                rnt-=(ll)(num[i]+1)*(num[j]+1)*num[i]*num[j]/4;
            cout<<rnt<<endl;
            continue;
        }
        sum[0]=0;
        memset(flag,0,sizeof(flag));
        ll lim=len*9;
        ll ans=0;
        for(int i=1;i<=len;++i)
          sum[i]=sum[i-1]+(str[i-1]-'0');
        for(int i=1;i<=len;++i)
          for(int j=i;j<=len;++j)
          {
              ll tmp=sum[j]-sum[i-1];
              if(tmp!=0&&(a%tmp==0)&&(a/tmp<=lim))
                flag[a/tmp]++;
          }
        for(int i=1;i<=len;++i)
          for(int j=i;j<=len;++j)
          {
              ll tmp=sum[j]-sum[i-1];
              if(tmp!=0&&(a%tmp==0)&&(tmp<=lim)&&flag[tmp])
                ans+=flag[tmp];
          }
        cout<<ans<<endl;
    }
    return 0;
}
