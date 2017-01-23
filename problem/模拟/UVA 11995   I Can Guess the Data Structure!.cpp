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
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(cin>>n)
    {
        queue<int>q;
        stack<int>s;
        priority_queue<int>p;
        int a,b,c;
        bool isqueue=true,isstack=true,isprior=true;
        for(int i=0;i<n;++i)
        {
            cin>>a>>b;
            if(a==1)
            {
                q.push(b);
                s.push(b);
                p.push(b);
            }
            else
            {
                if(q.empty()) isqueue=false;
                if(s.empty()) isstack=false;
                if(p.empty()) isprior=false;
                if(isqueue&&!q.empty())
                {
                    c=q.front();
                    q.pop();
                    if(b!=c) isqueue=false;
                }
                if(isstack&&!s.empty())
                {
                    c=s.top();
                    s.pop();
                    if(b!=c) isstack=false;
                }
                if(isprior&&!p.empty())
                {
                    c=p.top();
                    p.pop();
                    if(b!=c) isprior=false;
                }
            }
        }
        if(!isqueue&&!isstack&&!isprior)
            cout<<"impossible"<<endl;
        else if(isqueue&&!isstack&&!isprior)
            cout<<"queue"<<endl;
        else if(!isqueue&&isstack&&!isprior)
            cout<<"stack"<<endl;
        else if(!isqueue&&!isstack&&isprior)
            cout<<"priority queue"<<endl;
        else
            cout<<"not sure"<<endl;
    }
    return 0;
}

