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
string num[55];
bool cmp(string a,string b)
{
    return a+b>b+a;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(cin>>n)
    {
        if(n==0) break;
        for(int i=0;i<n;++i)
            cin>>num[i];
        sort(num,num+n,cmp);
        for(int i=0;i<n;++i)
            cout<<num[i];
        cout<<endl;
    }
    return 0;
}

