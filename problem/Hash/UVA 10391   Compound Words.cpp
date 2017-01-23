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
const int maxn=120000+10;
string str[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n=0;
    map<string,int>mp;
    while(cin>>str[++n])
    {
        mp[str[n]]=n;
    }
    string s1,s2;
    int len=0;
    for(int i=1;i<=n;++i)
    {
        len=str[i].length();
        s1="";
        for(int j=0;j<len-1;++j)
        {
            s1+=str[i][j];
            s2=str[i].substr(j+1,len-j-1);
            if(mp[s1]&&mp[s2])
                {cout<<s1<<s2<<endl;break;}
        }
    }
    return 0;
}

