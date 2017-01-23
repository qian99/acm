#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
#include<vector>
#include<queue>
#include<stack>
using namespace std;
typedef long long ll;
const int maxn=10000+10;
const char *ed="</html>";
char str[maxn],tmp[maxn];
bool checkbk(char c)
{
    return c==32||c==9||c==10;
}
string getTag(int pos,int & nxt)
{
    nxt=pos;
    while(str[nxt]!='>') nxt++;
    string rs="";
    while(pos<=nxt)
    {
        rs+=str[pos++];
    }
    nxt++;
    return rs;
}
string getContest(int pos,int &nxt)
{
    nxt=pos;
    while(str[nxt]!='<') nxt++;
    string rs="";
    while(checkbk(str[pos])&&pos<nxt) pos++;
    if(str[pos]=='<') return rs;
    while(pos<nxt)
    {
        if(checkbk(str[pos]))
        {
            while(checkbk(str[pos])) pos++;
            if(str[pos]=='<') continue;
            rs+=' ';
        }
        else
        {
            rs+=str[pos++];
        }
    }
    return rs;
}
inline void ptk(int k)
{
    for(int i=0;i<k;++i)
      cout<<" ";
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    cin>>t;
    getchar();
    while(t--)
    {
        tcase++;
        int n=0;
        while(true)
        {
            str[n]=getchar();
            if(str[n]=='<')
            {
                n++;
                bool ff=true;
                for(int j=1;j<7;++j)
                {
                    str[n]=getchar();
                    if(str[n++]!=ed[j]) {ff=false;break;}
                }
                if(ff) break;
            }
            else n++;
        }
        cout<<"Case #"<<tcase<<":"<<endl;
        string s;
        int now=0,nxt;
        int column=0;
        while(now<n)
        {
            if(str[now]=='<')
            {
                s=getTag(now,nxt);
                if(s[1]=='/') ptk(column-1);
                else ptk(column);
                cout<<s<<endl;
                if(s[1]=='/') column--;
                else if(s[s.length()-2]!='/') column++;
                now=nxt;
            }
            else
            {
                s=getContest(now,nxt);
                now=nxt;
                if(s=="") continue;
                ptk(column);
                cout<<s<<endl;
            }
        }
    }
    return 0;
}
