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
class CatsOnTheLineDiv2
{
public:
    pair<int,int>x[55];
    string getAnswer(vector <int> position, vector <int> count, int time)
    {
       int n = position.size();
       for(int i = 0;i < n;++i)
       {
           x[i] = make_pair(position[i],count[i]);
       }
       sort(x , x + n);
       int left = - inf;
       for(int i = 0 ;i < n;++i)
       {
           if(left < x[i].first - time)
              left = x[i].first - time;
           int num = x[i].first + time - left + 1;
           if(num < x[i].second) return "Impossible";
           left += x[i].second;
       }
       return "Possible";
    }
};
