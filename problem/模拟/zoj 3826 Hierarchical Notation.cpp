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
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 500000 + 10;
char str[maxn],s[maxn];
map<string,int>mp[maxn];
string Ends[maxn],S[maxn];
int tot,negcnt;
int solve(int L,int R)
{
    bool flag = true;
    for(int i = L;i <= R;++i)
        if(str[i] == ',' || str[i] == ':')
        {
            flag = false;
            break;
        }
    if(flag)
    {
        negcnt++;
        Ends[negcnt] = "";
        for(int i = L;i <= R;++i)
            Ends[negcnt] += str[i];
        return -negcnt;
    }
    int id = ++tot;
    if(str[L] == '{' && str[R] == '}') {L++;R--;}
    int last = L,cnt = 0;
    for(int i = L;i <= R;++i)
    {
        if(str[i] == '{') cnt++;
        if(str[i] == '}') cnt--;
        if(str[i] == ',' && cnt == 0)
        {
            string tmp = "";
            int j = last;
            while(str[j] != ':') tmp += str[j++];
            mp[id][tmp] = solve(j + 1,i - 1);
            last = i + 1;
        }
    }
    string tmp = "";
    int j = last;
    while(str[j] != ':') tmp += str[j++];
    mp[id][tmp] = solve(j + 1,R);
    return id;
}
void print(int rt)
{
    if(rt < 0)
    {
        cout<<Ends[-rt];
        return ;
    }
    cout<<"{";
    map<string,int>:: iterator it = mp[rt].begin();
    cout<<(it -> first)<<":";
    print(it -> second);
    it++;
    while(it != mp[rt].end())
    {
        cout<<","<<(it -> first)<<":";
        print(it -> second);
        it++;
    }
    cout<<"}";
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%s",str);
        tot = negcnt = 0;
        int n = strlen(str);
        for(int i = 0;i <= n;++i) mp[i].clear();
        solve(0,n - 1);
//        print(1);
        int q;
        scanf("%d",&q);
        while(q--)
        {
            scanf("%s",s);
            n = strlen(s);
            int m = 0;
            string tmp = "";
            for(int i = 0;i < n;++i)
                if(s[i] == '.')
                {
                    S[m++] = tmp;
                    tmp = "";
                }
                else tmp += s[i];
            S[m++] = tmp;
            int now = 1;
            for(int i = 0;i < m;++i)
            {
                if(now < 0) {now = inf;break;}
                if(mp[now].find(S[i]) == mp[now].end())
                {
                    now = inf;
                    break;
                }
                else
                    now = mp[now][S[i]];
            }
            if(now == inf) cout<<"Error!"<<endl;
            else
            {
                print(now);
                puts("");
            }
        }
    }
    return 0;
}
