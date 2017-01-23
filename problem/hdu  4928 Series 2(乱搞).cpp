#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<set>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=1000000+10;
ll A[maxn],B[maxn];
void cal(int & zero,int & len)
{
    int tot = 0;
    if(zero) B[++tot] = A[1],zero--;
    for(int i = 1;i < len;++i)
        B[++tot] = (A[i+1]-A[i]);
    len = 0;
//    bool flag = (B[0] == 0);
    for(int i = 1;i <=tot ;++i)
        A[++len] = B[i];
}
int check(int &zero ,int & len)
{
    if(!zero)
    {
        bool flag = false;
        for(int i = 1;i < len ;++i)
            if(A[i] > A[i+1]) {flag = true ;break;}
        if(flag) reverse(A+1,A+len+1);
    }
    for(int i = 1; i < len ;++i)
        if(A[i] > A[i+1]) return false;
    int tot = 0;
    bool headzero = (A[1] == 0);
    for(int i = 1; i <= len;++i)
        if(A[i] == 0 && headzero) zero++;
        else {A[++tot] = A[i]; headzero = false ;}
    len = tot;
    return true;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w ",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n;
        scanf("%d",&n);
        for(int i = 1;i <= n;++i)
            scanf("%I64d",&A[i]);
        int zero = 0,len = n;
        if(!check(zero,len)) printf("ugly series\n");
        else
        {
            int ans = 0;
            for(int i = 1;i < n;++i)
            {
                cal(zero,len);
                if(!check(zero,len)) break;
                ans++;
            }
            if(ans == n-1) printf("nice series\n");
            else printf("%d\n",ans);
        }
    }
    return 0;
}
