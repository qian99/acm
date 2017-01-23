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
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
const int maxn=1000000+10;
int values[maxn];
stack<int>now;
stack<int>ls;
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int q;
    while(~scanf("%d",&q))
    {
        while(!now.empty()) now.pop();
        while(!ls.empty()) ls.pop();
        char s[3];
        int v,sum=0,tmp;
        int x,pos=0;
        while(q--)
        {
            scanf("%s",s);
            if(s[0]=='I')
            {
                scanf("%d",&v);
                tmp=sum+v;
                if(!now.empty())
                {
                    x=values[pos];
                    if(sum+v>x)
                       tmp=sum+v;
                    else tmp=x;
                }
                values[++pos]=tmp;
                now.push(v);
                sum+=v;
            }
            else if(s[0]=='D')
            {
                if(now.empty()) continue;
                x=now.top();now.pop();
                pos--;
                sum-=x;
            }
            else if(s[0]=='L')
            {
                if(now.empty()) continue;
                x=now.top();now.pop();
                ls.push(x);
                pos--;
                sum-=x;
            }
            else if(s[0]=='R')
            {
                if(ls.empty()) continue;
                int y=ls.top();ls.pop();
                tmp=sum+y;
                if(!now.empty())
                {
                    x=values[pos];
                    if(sum+y>x)
                       tmp=sum+y;
                    else tmp=x;
                }
                values[++pos]=tmp;
                now.push(y);
                sum+=y;
            }
            else
            {
                scanf("%d",&v);
                printf("%d\n",values[v]);
            }
        }
    }
    return 0;
}
