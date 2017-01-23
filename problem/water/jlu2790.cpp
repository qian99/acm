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
const int maxn=100+10;
char a[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    cin>>t;
    while(t--)
    {
        double sum=0;
        double tp;
        for(int i=0;i<12;++i)
        {
            cin>>tp;
            sum+=tp;
        }
        sum/=12.0;
        sprintf(a,"%.2lf",sum);
        int len=strlen(a);
        int lim=len;
        for(int i=1;i<=3;++i)
        {
            if(a[len-i]=='0'||a[len-i]=='.') lim--;
            else break;
        }
        a[lim]='\0';
        cout<<"$"<<a<<endl;
    }
    return 0;
}
