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
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 100000 + 10;
int p[maxn],p2[maxn];
set<int>A,B;
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,a,b;
    scanf("%d%d%d",&n,&a,&b);
    for(int i = 0;i < n;++i)
    {
        scanf("%d",&p[i]);
        A.insert(p[i]);
    }
    for(int i = 0;i < n;++i)
    {
        if(A.find(p[i]) != A.end())
        {
            int x = a - p[i];
            if(A.find(x) == A.end())
            {
                B.insert(p[i]);
                A.erase(p[i]);
            }
        }
    }
    int tail = 0;
    for(set<int> :: iterator it = B.begin(); it != B.end();++it)
        p2[tail++] = *it;
    bool flag = true;
    for(int i = 0;i < tail;++i)
    {
        int x = b - p2[i];
        if(B.find(x) == B.end())
        {
            if(A.find(x) != A.end())
            {
                B.insert(x);
                p2[tail++] = x;
                A.erase(x);
                A.erase(a - x);
                if(B.find(a - x) == B.end())
                {
                    p2[tail++] = a - x;
                    B.insert(a - x);
                }
            }
            else
            {
                flag = false;
                break;
            }
        }
    }
    if(!flag)
        puts("NO");
    else
    {
        puts("YES");
        for(int i = 0;i < n;++i)
        {
            if(i) printf(" ");
            if(A.find(p[i]) != A.end())
                printf("0");
            else
                printf("1");
        }
    }
    return 0;
}