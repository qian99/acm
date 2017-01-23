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
const string s1="Register";
struct Data
{
    int value,t,nt;
    bool operator <(const Data &a)const
    {
        if(a.nt==nt) return a.value<value;
        return a.nt<nt;
    }
};
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    string str;
    priority_queue<Data>qq;
    int a,b,k;
    Data tp;
    while(cin>>str)
    {
        if(str!=s1) break;
        cin>>a>>b;
        tp.value=a;
        tp.t=b;
        tp.nt=b;
        qq.push(tp);
    }
    cin>>k;
    while(k--&&!qq.empty())
    {
        tp=qq.top();
        qq.pop();
        cout<<tp.value<<endl;
        tp.nt+=tp.t;
        qq.push(tp);
    }
    return 0;
}

