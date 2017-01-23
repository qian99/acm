#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
//const int maxn=131070+1;
__int64 dp[20][20];
char s1[20],s2[20];
int num[20];
__int64 f(int d,int m)
{
    if(d==0) return m;
    if(d==1) return m*10+1;
    if(dp[d][m]>=0) return dp[d][m];
    dp[d][m]=0;
        for(int j=0;j<10;++j)
        {
            if(j==1)
            dp[d][m]+=f(d-1,m+1);
            else
            dp[d][m]+=f(d-1,m);
        }
    return dp[d][m];
}
__int64 work()
{
    __int64 sum=0;
    int d=num[0]-1;
    int m=0,p;
    for(int i=1;i<num[0];++i)
    {
        p=num[i];
        for(int j=0;j<p;++j)
        {
            if(j==1)
            sum+=f(d,m+1);
            else
            sum+=f(d,m);
        }
        if(num[i]==1) m++;
        d--;
    }
    p=num[num[0]];
    for(int i=0;i<=p;++i)
    {
        if(i==1)
        sum+=f(0,m+1);
        else
        sum+=f(0,m);
    }
    return sum;
}
void getNum(char *s,bool flag)
{
    int len=strlen(s);
    int i=0;
    if(flag)
    {
        int temp=len-1;
        int sub=1;
        while(s[temp]-sub<'0')
        {
            sub='0'-(s[temp]-sub);
            s[temp]='9';
            temp--;
        }
        s[temp]-=sub;
        if(s[temp]=='0')
        {
            i++;
            len--;
        }
    }
    num[0]=0;
    for(int j=1;j<=len;++j)
    {
        num[0]++;
        num[j]=s[i++]-'0';
    }
}
int main()
{
    memset(dp,0xff,sizeof(dp));
    dp[0][0]=0;
    while(~scanf("%s%s",s1,s2))
    {
        __int64 r1,r2;
        getNum(s1,true);
        r1=work();
        getNum(s2,false);
        r2=work();
        printf("%I64d\n",r2-r1);
    }
    return 0;
}
