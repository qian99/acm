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
#define inf 2139062143
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=1000000+10;
char str[maxn];
bool check(int U,int I)
{
    ll total=U*3+I;
    ll p=1;
    while(total>p){ p*=2;}
    if(total==p) return true;
    while(p<Inf/2)
    {
        if((p-total)%6==0) return true;
        p*=2;
    }
    return false;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    scanf("%d",&n);
    while(n--)
    {
        scanf("%s",str);
        int len=strlen(str);
        bool flag=true;
        if(str[0]!='M') flag=false;
        else
        {
            int U=0,I=0;
            for(int i=1;i<len;++i)
            {
                if(str[i]=='U') U++;
                else if(str[i]=='I') I++;
                else
                {
                    flag=false;
                    break;
                }
            }
            if(flag&&check(U,I)) flag=true;
            else flag=false;
        }
        if(flag) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
