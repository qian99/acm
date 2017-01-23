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
char str[maxn];
int getsum(int len)
{
    //int len=strlen(str);
    int sum=0;
    for(int i=0;i<len;++i)
    {
        sum+=(int)(str[i]-'0');
    }
    return sum;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%s",str);
        int len=strlen(str);
        if(len==1)
        {
            printf("19\n");
            continue;
        }
        int sum=getsum(len);
        int w=sum%10;
        int jw=0;
        w=10-w;
        if(w==0) w=10;
        int u=str[len-1]-'0';
        if(9-u>=w)
        {
            str[len-1]='0'+u+w;
            printf("%s\n",str);
        }
        else
        {
            jw=1;
            int i=len-2;
            while(jw&&i>=0)
            {
                u=str[i]-'0';
                str[i]=(u+jw)%10+'0';
                jw=(u+jw)/10;
                i--;
            }
            sum=getsum(len)+jw;
            sum-=str[len-1]-'0';
            sum=sum%10;
            sum=10-sum;
            if(sum==10) sum=0;
            str[len-1]=sum+'0';
            if(jw) printf("%d",jw);
            printf("%s\n",str);
        }
    }
    return 0;
}
