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
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
class TaroJiroGrid
{
public:
    bool check(vector <string> a)
    {
        int n = a.size();
        int maxv = 1,cnt;
        for(int j = 0;j < n;++j)
        {
            char c = a[0][j];
            cnt = 1;
            for(int i = 1;i < n;++i)
            {
                if(a[i][j] == c)
                    cnt++;
                else
                {
                    c = a[i][j];
                    cnt = 1;
                }
                maxv = max(maxv,cnt);
            }
        }
        return maxv <= n/2;
    }
    int getNumber(vector <string> grid)
    {
        int n = grid.size();
        vector<string>a;
        string black = "",white = "";
        for(int i = 0;i < n;++i)
        {
            black += "B";
            white += "W";
        }
        if(check(grid)) return 0;
        for(int k = 0;k < n;++k)
        {
            for(int i = 0;i < n;++i) a.clear();
            for(int j = 0;j < n;++j)
            {
                if(j == k) a.push_back(black);
                else a.push_back(grid[j]);
            }
            if(check(a)) return 1;
        }
        for(int k = 0;k < n;++k)
        {
            for(int i = 0;i < n;++i) a.clear();
            for(int j = 0;j < n;++j)
            {
                if(j == k) a.push_back(white);
                else a.push_back(grid[j]);
            }
            if(check(a)) return 1;
        }
        return 2;
    }
};
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    return 0;
}
