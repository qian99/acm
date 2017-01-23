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
using namespace std;
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,L,n,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        priority_queue<int>ql;
        priority_queue<int,vector<int>,greater<int> >qr;
        scanf("%d%d",&L,&n);
        int now=0,scnt=0;
        int tp,v,lmove=-1;
        int sum=0;
        while(n--)
        {
            scanf("%d",&tp);
            if(tp)
            {
                if(scnt) scnt--;
                else
                {
                    int lp=-1,rp=-1;
                    if(!ql.empty()) lp=ql.top();
                    if(!qr.empty()) rp=qr.top();
                    if(lp==-1&&rp==-1) continue;
                    if(lp==-1) lmove=1;
                    else if(rp==-1) lmove=0;
                    else if(now-lp<rp-now) lmove=0;
                    else if(now-lp>rp-now) lmove=1;
                    if(lmove)
                    {
                        sum+=(rp-now);
                        now=rp;
                        scnt=0;
                        qr.pop();
                        while(!qr.empty()&&(qr.top()==rp))
                        {scnt++;qr.pop();}
                    }
                    else
                    {
                        sum+=(now-lp);
                        now=lp;
                        scnt=0;
                        ql.pop();
                        while(!ql.empty()&&(ql.top()==lp))
                        {scnt++;ql.pop();}
                    }
                }
            }
            else
            {
                scanf("%d",&v);
                if(v>now) qr.push(v);
                else if(v<now) ql.push(v);
                else scnt++;
            }
        }
        printf("Case %d: %d\n",tcase,sum);
    }
    return 0;
}
