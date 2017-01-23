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
bool isprime(int x)
{
    int m=sqrt(x);
    int i=2;
    while(i<=m)
      if(x%i==0) return false;
      else i++;
    return true;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,t;
    cin>>t;
    while(t--)
    {
        cin>>n;
        int m=(sqrt(n));
        int i=2;
        bool flag=false;
        while(i<=m)
        {
            if(n%i==0)
            {
                if(isprime(i)&&isprime(n/i))
                    flag=true;
                break;
            }
            i++;
        }
        if(flag) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
