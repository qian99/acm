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
const int maxn=30000+10;
char str[maxn];
stack<int>S;
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    char ss[5];
    scanf("%s",ss);
    scanf("%s",str);
    int n=strlen(str);
    int turns=(ss[0]=='B');
    bool flag=true;
    int nowlen=0;
    if(str[0]!=ss[0]) flag=false;
    else
    {
        S.push(turns);
        S.push(turns^1);
        nowlen=3;
    }
    int x;
    for(int i=1;i<n;++i)
    {
        if(S.empty()) {flag=false;break;}
        x=S.top();S.pop();
        if((x^1)==(str[i]-'A')) continue;
        if(nowlen+2>n) {flag=false;break;}
        nowlen+=2;
        S.push(x);
        S.push(x^1);
    }
    if(!S.empty()) flag=false;
    if(n==1&&str[0]!=ss[0]) flag=true;
    if(flag) puts("YES");
    else puts("NO");
    return 0;
}

