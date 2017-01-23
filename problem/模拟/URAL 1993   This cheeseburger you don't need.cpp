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
const int maxn=1000+10;
char str[maxn];
void solve(int s,int t,int flag)
{
    string ss[3];
    ss[0]=ss[1]=ss[2]="";
    int p;
    for(int i=s;i<=t;)
    {
        while(str[i]!='('&&str[i]!='{'&&str[i]!='['&&i<=t) i++;
        if(i>t) break;
        if(str[i]=='{') p=0;
        else if(str[i]=='(') p=1;
        else p=2;
        i++;
        while(str[i]!=')'&&str[i]!='}'&&str[i]!=']')
        {
            ss[p]+=str[i];
            i++;
        }
    }
    p=0;
    for(int i=s;i<=t;)
    {
        while(str[i]!='('&&str[i]!='{'&&str[i]!='['&&i<=t)
        {
            cout<<str[i];
            i++;
        }
        if(flag)
        {
        if(p==0)
        {
            if(ss[p][0]>='a'&&ss[p][0]<='z')
              ss[p][0]='A'+ss[p][0]-'a';
        }
        else
        {
            if(ss[p][0]>='A'&&ss[p][0]<='Z')
              ss[p][0]='a'+ss[p][0]-'A';
        }
        }
        cout<<ss[p++];
        i++;
        while(str[i]!=')'&&str[i]!='}'&&str[i]!=']'&&i<t) i++;
        i++;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(gets(str))
    {
        int s,t;
        int n=strlen(str);
        s=0,t=0;
        bool first=true;
        while(s<n)
        {
            while(str[s]!='('&&str[s]!='{'&&str[s]!='['&&t<n) s++;
            t=s+1;
            while(str[t]!=','&&t<n) t++;
            t--;
            solve(s,t,first);
            first=false;
            s=t+1;
            while(str[s]!='('&&str[s]!='{'&&str[s]!='['&&s<n)
            {
                cout<<str[s];
                s++;
            }
        }
        cout<<endl;
    }
    return 0;
}
