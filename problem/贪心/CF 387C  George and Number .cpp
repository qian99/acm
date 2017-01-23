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
const int maxn=100000+1000;
char str[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%s",str);
    int n=strlen(str);
    int ans=1;
    for(int i=n-1;i>=0;--i)
    {
        if(str[i]!='0')
        {
            if(i*2<n||(i*2==n&&str[0]<str[i]))
                break;
            else {ans++;n=i;}
        }
    }
    printf("%d\n",ans);
    return 0;
}

