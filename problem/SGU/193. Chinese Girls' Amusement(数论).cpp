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
char str[maxn];
int num[maxn],n;
void div2()
{
    int z=0,tmp;
    for(int i=n-1;i>=0;--i)
    {
        tmp=(num[i]+z*10)&1;
        num[i]=(num[i]+z*10)/2;
        z=tmp;
    }
    while(n>1&&num[n-1]==0) n--;
}
void decreas()
{
    int jw=1;
    int i=0;
    while(jw)
    {
        num[i]-=jw;
        if(num[i]<0) num[i]=9;
        else jw=0;
        i++;
    }
    while(n>1&&num[n-1]==0) n--;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%s",str);
    n=strlen(str);
    for(int i=0;i<n;++i)
      num[i]=(str[n-i-1]-'0');
    if(num[0]&1)
    {
        div2();
    }
    else
    {
        div2();
        if(num[0]&1)
        {
            decreas();
            decreas();
        }
        else decreas();
    }
    for(int i=n-1;i>=0;--i)
      printf("%d",num[i]);
    printf("\n");
    return 0;
}
