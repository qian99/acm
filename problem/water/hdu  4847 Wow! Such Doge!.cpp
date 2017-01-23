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
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=1000000+10;
char str[maxn];
bool check(int pos)
{
    if(str[pos]!='d'&&str[pos]!='D') return false;
    if(str[pos+1]!='o'&&str[pos+1]!='O') return false;
    if(str[pos+2]!='g'&&str[pos+2]!='G') return false;
    if(str[pos+3]!='e'&&str[pos+3]!='E') return false;
    return true;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int cnt=0;
    while(gets(str))
    {
        int n=strlen(str);
        for(int i=0;i<=n-4;++i)
            if(check(i)) cnt++;
    }
    printf("%d\n",cnt);
    return 0;
}
