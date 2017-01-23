#include <iostream>
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
const int maxn=100000+10;
char str[maxn],a[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(gets(str))
    {
        int n=strlen(str);
        int m=0;
        int t=n-1;
        int ts=n-1;
        while(t>=0)
        {
            while(str[ts]!='['&&str[ts]!=']'&&ts>=0)
            {
                ts--;
            }
            if(ts<0)
            {
                for(int i=0;i<=t;++i)
                  cout<<str[i];
                  break;
            }
            if(str[ts]=='[')
            {
                for(int i=ts+1;i<=t;++i)
                  cout<<str[i];
            }
            if(str[ts]==']')
            {
                for(int i=t;i>ts;--i)
                  a[m++]=str[i];
            }
            t=ts-1;
            ts=t;
        }
        for(int i=m-1;i>=0;--i)
           cout<<a[i];
        cout<<endl;
    }
    return 0;
}
