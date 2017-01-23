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
const int maxn = 1000+ 10;
char str[maxn];
bool check(int x)
{
    if(x > 0 && str[x] == str[x-1]) return false;
    if(x > 1 && str[x] == str[x-2]) return false;
    return true;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,p;
    scanf("%d%d",&n,&p);
    scanf("%s",str);
    bool flag = false;
    for(int i = n - 1;i >= 0;--i)
    {
        str[i]++;
        while(str[i] - 'a' < p && !check(i)) str[i]++;
        if(str[i] - 'a' >= p) continue;
        int j = i + 1;
        for(;j < n;++j)
        {
            str[j] = 'a';
            while(str[j] - 'a' < p && !check(j)) str[j]++;
            if(str[j] - 'a' >= 'p') break;
        }
        if(j < n) continue;
        flag = true;
        break;
    }
    if(!flag) puts("NO");
    else
    {
        for(int i = 0;i < n;++i)
            putchar(str[i]);
        puts("");
    }
    return 0;
}