#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<set>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=250000;
vector<string>vt[7];
map<string,int>mp;
struct Node
{
    string s;
    int num;
    bool operator <(const Node &a) const
    {
        return (a.num==num&&s<a.s)||(num>a.num);
    }
}node[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int now=0;
    for(int i=0;i<7;++i) vt[i].clear();
    string str;
    while(cin>>str)
    {
        if(str=="<text>")
        {
            vt[now].clear();
            while(cin>>str)
            {
                if(str=="</text>") break;
                if(str.length()<4) continue;
                vt[now].push_back(str);
            }
            now=(now+1)%7;
        }
        else
        {
            mp.clear();
            int N,id,cnt=0,size;
            cin>>N;
            cin>>str;
            cout<<"<top "<<N<<">"<<endl;
            for(int i=0;i<7;++i)
            {
                size=vt[i].size();
                for(int j=0;j<size;++j)
                {
                    id=mp[vt[i][j]];
                    if(id) node[id].num++;
                    else
                    {
                        mp[vt[i][j]]=++cnt;
                        node[cnt].s=vt[i][j];
                        node[cnt].num=1;
                    }
                }
            }
            sort(node+1,node+cnt+1);
            for(int i=1;i<=min(cnt,N);++i)
                cout<<node[i].s<<" "<<node[i].num<<endl;
            int last=node[min(cnt,N)].num;
            for(int i=min(cnt,N)+1;i<=cnt;++i)
                if(node[i].num==last)
                    cout<<node[i].s<<" "<<node[i].num<<endl;
            cout<<"</top>"<<endl;
        }
    }
    return 0;
}
