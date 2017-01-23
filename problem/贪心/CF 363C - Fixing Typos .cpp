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
const int maxn = 200000 + 10;
char str[maxn];
stack<char>S;
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    scanf("%s",str);
    int n = strlen(str);
    char x,y,z;
    for(int i = 0;i < n;++i)
    {
        if(S.empty())
            S.push(str[i]);
        else
        {
            x = S.top();S.pop();
            if(S.empty())
            {
                S.push(x);
                S.push(str[i]);
                continue;
            }
            y = S.top();S.pop();
            if(x == str[i] && y == str[i])
            {
                S.push(y);
                S.push(x);
                continue;
            }
            if(S.empty())
            {
                S.push(y);
                S.push(x);
                S.push(str[i]);
                continue;
            }
            z = S.top();S.pop();
            if(y == z && x == str[i])
            {
                S.push(z);
                S.push(y);
                S.push(x);
            }
            else
            {
                S.push(z);
                S.push(y);
                S.push(x);
                S.push(str[i]);
            }
        }
    }
    int len = 0;
    while(!S.empty())
    {
        str[len++] = S.top();
        S.pop();
    }
    reverse(str,str + len);
    str[len] = 0;
    printf("%s\n",str);
    return 0;
}