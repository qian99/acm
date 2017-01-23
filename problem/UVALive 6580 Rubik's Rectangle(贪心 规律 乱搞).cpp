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
const int maxn = 100 + 10;
map<int,string>mp;
vector<pair<int,int> >ans;
void Init()
{
    mp[1234] = "";
    mp[2314] = "01032123";
    mp[2431] = "01021323";
    mp[2143] = "01013232";
    mp[4321] = "010212";
    mp[4132] = "01012323";
    mp[3412] = "01023213";
    mp[3124] = "0101";
    mp[3241] = "01032321";
    mp[4213] = "01032132";
    mp[1423] = "01210323";
    mp[1342] = "01120323";
}
int a[maxn][maxn],b[maxn][maxn],flip[maxn],n,m;
bool checkrow(int x)
{
    bool flag = true;
    for(int i = 1;i <= m;++i)
        if(a[x][i] != b[x][i])
            flag = false;
    if(flag) return true;
    reverse(a[x] + 1,a[x] + m + 1);
    for(int i = 1;i <= m;++i)
        if(a[x][i] != b[x][i])
            return false;
    ans.push_back(make_pair(0,x));
    return true;
}
bool checkcol(int y)
{
    bool flag = true;
    for(int i = 1;i <= n;++i)
        if(a[i][y] != b[i][y])
            flag = false;
    if(flag) return true;
    for(int i = 1;i <= n/2;++i)
        swap(a[i][y],a[n - i + 1][y]);
    for(int i = 1;i <= n;++i)
        if(a[i][y] != b[i][y])
            return false;
    ans.push_back(make_pair(1,y));
    return true;

}
int c[4],d[4],e[4];
inline int convert()
{
    return c[0]*1000 + c[1]*100 + c[2]*10 + c[3];
}
bool cal(int x1,int y1,int x2,int y2,int ins)
{
    for(int i = 0;i < 4;++i)
        e[i] = c[i];
    sort(e,e + 4);
    for(int i = 0;i < 4;++i)
        if(d[i] != e[i])
            return false;
    for(int i = 0;i < 4;++i)
    {
        for(int j = 0;j < 4;++j)
            if(c[i] == e[j])
            {
                c[i] = j + 1;
                break;
            }
    }
    int hval = convert();
    if(mp.find(hval) == mp.end()) return false;
    if(ins)
    {
        string op = mp[hval];
        int len = op.length();
        for(int i = 0;i < len;++i)
        {
            if(op[i] == '0')
                ans.push_back(make_pair(0,x1));
            else if(op[i] == '1')
                ans.push_back(make_pair(1,y1));
            else if(op[i] == '2')
                ans.push_back(make_pair(0,x2));
            else
                ans.push_back(make_pair(1,y2));
        }
    }
    return true;
}
void getstate(int i,int j)
{
    c[0] = a[i][j];
    d[0] = b[i][j];
    c[1] = a[i][m - j + 1];
    d[1] = b[i][m - j + 1];
    c[2] = a[n - i + 1][j];
    d[2] = b[n - i + 1][j];
    c[3] = a[n - i + 1][m - j + 1];
    d[3] = b[n - i + 1][m - j + 1];
}
bool solve()
{
    int N = n/2,M = m/2;
    if(N <= 0 || M <= 0) return true;
    for(int i = 1;i <= M;++i)
    {
        getstate(1,i);
        if(!cal(1,i,n,m - i + 1,0))
        {
            ans.push_back(make_pair(1,i));
            for(int j = 1;j <= N;++j)
                swap(a[j][i],a[n - j + 1][i]);
        }
        getstate(1,i);
        if(!cal(1,i,n,m - i + 1,1))
            return false;
    }
    bool flag;
    for(int i = 2;i <= N;++i)
    {
        flag = true;
        for(int j = 1;j <= M;++j)
        {
            getstate(i,j);
            if(!cal(i,j,n - i + 1,m - j + 1,0))
                flag = false;
        }
        if(!flag)
        {
            ans.push_back(make_pair(0,i));
            reverse(a[i] + 1,a[i] + m + 1);
        }
        for(int j = 1;j <= M;++j)
        {
            getstate(i,j);
            if(!cal(i,j,n - i + 1,m - j + 1,1))
                return false;
        }
    }
    return true;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    Init();
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&m,&n);
        for(int i = 1;i <= n;++i)
            for(int j =1;j <= m;++j)
            {
                scanf("%d",&a[i][j]);
                b[i][j] = (i-1)*m + j;
            }
        ans.clear();
        if(n & 1)
        {
            if(!checkrow((n + 1)/2))
            {
                puts("IMPOSSIBLE");
                continue;
            }
        }
        if(m & 1)
        {
            if(!checkcol((m + 1)/2))
            {
                puts("IMPOSSIBLE");
                continue;
            }
        }

        if(solve())
        {
            printf("POSSIBLE");
            printf(" %d",(int)ans.size());
            for(int i = 0;i < (int)ans.size();++i)
            {
                putchar(' ');
                if(ans[i].first == 0)
                    putchar('R');
                else
                    putchar('C');
                printf("%d",ans[i].second);
            }
            puts("");
        }
        else
            puts("IMPOSSIBLE");
    }
    return 0;
}
