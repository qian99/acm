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
const int maxn=55000;
int n,m;
int sum[maxn],len,res;
void cal(int p)
{
    int tmp;
    while(p!=0)
    {
        tmp=p%m;
        p/=m;
        res+=tmp*tmp;
    }
}
char convert(int s)
{
    if(s>=0&&s<=9) return s+'0';
    return s-10+'A';
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&n,&m))
    {
        res=len=0;
        int i=2,lim=sqrt(n+0.5);
        cal(1);
        if(n!=1) cal(n);
        while(i<=lim)
        {
            if(n%i==0)
            {
                cal(i);
                if(i!=(n/i)) cal(n/i);
            }
            i++;
        }
        while(res!=0)
        {
            sum[len++]=res%m;
            res/=m;
        }
        for(int j=len-1;j>=0;--j)
          printf("%c",convert(sum[j]));
        printf("\n");
    }
    return 0;
}
