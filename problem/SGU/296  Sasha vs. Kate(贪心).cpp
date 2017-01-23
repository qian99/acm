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
char num[maxn],res[maxn];
int now;
void solve(int l,int r,int k)
{
    int end=now==0?'1':'0';
    bool flag=false;
    for(int i='9';i>=end;--i)
    {
        for(int j=l;j<=r;++j)
        {
            if(num[j]==i&&k-1<=r-j)
            {
                res[now++]=i;
                solve(j+1,r,k-1);
                flag=true;
                break;
            }
        }
        if(flag) break;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,k;
    scanf("%s",num);
    scanf("%d",&k);
    n=strlen(num);
    k=n-k;
    now=0;
    solve(0,n-1,k);
    for(int i=0;i<k;++i)
        printf("%c",res[i]);
    printf("\n");
    return 0;
}
