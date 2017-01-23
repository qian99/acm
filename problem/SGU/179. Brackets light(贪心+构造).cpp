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
const int maxn=10000+10;
char str[maxn],res[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%s",str);
    int n=strlen(str);
    int p,i=n-1;
    while(i>0&&str[i]==')'&&str[i-1]=='(') i-=2;
    if(i<0)
    {
        printf("No solution\n");
    }
    else
    {
        p=i;
        while(str[p]!='(') p--;
        int top=0,m=0;
        for(i=0;i<p;++i)
        {
            res[m++]=str[i];
            if(str[i]=='(') top++;
            else top--;
        }
        res[m++]=')';top--;
        for(i=0;i<top;++i)
          res[n-i-1]=')';
        int k=(n-top-m)/2;
        for(i=0;i<k;++i)
          res[m+i]='(';
        m+=k;
        for(i=0;i<k;++i)
          res[m+i]=')';
        res[n]='\0';
        printf("%s\n",res);
    }
    return 0;
}
