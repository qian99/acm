#include <iostream>
#include<cstdio>
#include<memory.h>
#include<algorithm>
#include<math.h>
#include<map>
using namespace std;
typedef long long ll;
const int maxn=200+10;
const int mod=100003;
const ll ct=(1e15+10)*2;
ll num[6][maxn];
ll table[mod+10];
void hash(ll x)
{
    int p=x%mod;
    while(table[p]!=-1&&table[p]!=x)
    {
        p++;
        if(p==mod) p=0;
    }
    table[p]=x;
}
bool gethash(ll x)
{
    int p=x%mod;
    while(table[p]!=x&&table[p]!=-1)
    {
        p++;
        if(p==mod) p=0;
    }
    if(table[p]!=x) return false;
    return true;
}
int main()
{
    //freopen("in.txt","r",stdin);
    int t,n;
    scanf("%d",&t);
    while(t--)
    {
        memset(table,0xff,sizeof(table));
        scanf("%d",&n);
        for(int i=0;i<5;++i)
        {
            for(int j=0;j<n;++j)
              scanf("%I64d",&num[i][j]);
        }
        ll tmp;
        for(int i=0;i<n;++i)
          for(int j=0;j<n;++j)
          {
              tmp=num[0][i]+num[1][j];
              tmp+=ct;
              hash(tmp);
          }
        bool find=false;
        for(int i=0;i<n;++i)
        {
          for(int j=0;j<n;++j)
          {
              for(int k=0;k<n;++k)
              {
                tmp=num[2][i]+num[3][j]+num[4][k];
                tmp=-tmp;
                if(tmp>=-ct&&tmp<=ct&&gethash(tmp+ct))
                {
                    find=true;
                    break;
                }
              }
              if(find) break;
          }
          if(find) break;
        }
        if(find) puts("Yes");
        else puts("No");
    }
    return 0;
}
