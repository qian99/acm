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
const int maxn=100000+100;
int pa[maxn];
set<int>st[maxn];
set<int>:: iterator it;
map<string,int>mp;
char str[20],name1[30],name2[30];
int Find(int x)
{
    if(x==pa[x]) return x;
    int y=Find(pa[x]);
    it=st[x].begin();
    while(it!=st[x].end())
    {
        int val=*it;
        ++it;
        if(st[y].count(val)) continue;
        st[y].insert(val);
    }
    st[x].clear();
    return pa[x]=y;
}
void Uion(int x,int y)
{
    int a=Find(x);
    int b=Find(y);
    if(a!=b)
    {
        pa[b]=a;
        Find(b);
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        mp.clear();
        int cnt=0;
        while(n--)
        {
            scanf("%s",str);
            if(str[0]=='a')
            {
                scanf("%s",name1);
                mp[string(name1)]=++cnt;
                st[cnt].clear();
                pa[cnt]=cnt;
                int m,v;
                scanf("%d",&m);
                while(m--)
                {
                    scanf("%d",&v);
                    st[cnt].insert(v);
                }
            }
            else if(str[0]=='s')
            {
                scanf("%s%s",name1,name2);
                int x=mp[string(name1)];
                int y=mp[string(name2)];
                Uion(x,y);
            }
            else
            {
                scanf("%s",name1);
                int x=Find(mp[string(name1)]);
                printf("%d\n",st[x].size());
            }
        }
    }
    return 0;
}
