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
class CatsOnTheLineDiv1
{
public:
    pair<int,int>x[1010];
    int getNumber(vector <int> position, vector <int> count, int time)
    {
        int n = position.size();
        for(int i = 0;i < n;++i)
            x[i] = make_pair(position[i],count[i]);
        sort(x,x+n);
        int ans = 0,flag = 0;
        int left = -inf;
        for(int i = 0;i < n;++i)
        {
            if(left < x[i].first - time)
                left = x[i].first - time,flag = 0;
            if(flag) continue;
            int num = x[i].first + time - left + 1;
            if(num >= x[i].second)
            {
                left += x[i].second;
            }
            else
            {
                left = x[i].first + time;
                ans++;
                flag = 1;
            }
        }
        return ans;
    }
};