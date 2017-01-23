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
string str[25];
char xx[30];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,tcase=0;
    string ch;
    while(cin>>n)
    {
        if(n==0) break;
        cin>>ch;
        for(int i=0;i<26;++i)
            xx[ch[i]-'A']=i+'A';
        for(int i=0;i<n;++i)
        {
            cin>>str[i];
            int len=str[i].length();
            for(int j=0;j<len;++j)
                str[i][j]=xx[str[i][j]-'A'];
        }
        sort(str,str+n);
        for(int i=0;i<n;++i)
        {
            int len=str[i].length();
            for(int j=0;j<len;++j)
                str[i][j]=ch[str[i][j]-'A'];
        }
        cout<<"year "<<++tcase<<endl;
        for(int i=0;i<n;++i)
            cout<<str[i]<<endl;
    }
    return 0;
}
