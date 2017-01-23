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
class SuffixArrayDiv2
{
public:
    pair<string,int> T[555],K[555];
    string smallerOne(string s)
    {
        int n = s.length();
        string tmp = "";
        for(int i = n-1;i >=0;--i)
        {
//            cout<<s[i]<<endl;
            tmp = s[i] + tmp;
            T[i] = make_pair(tmp,i);
        }
        sort(T,T+n);
//        for(int j = 0; j< n;++j)
//            cout<<T[j].first<<" "<<T[j].second<<endl;
//        cout<<"-------------------------------------------"<<endl;
        for(int i = 0;i < n;++i)
        {
            if(s[i] == 'a') continue;
            for(int j = 0;j < n;++j)
            {
                int k = T[j].second;
                if(k > i) K[j] = T[j];
                else
                {
                    tmp = T[j].first;
                    tmp[i - k] = tmp[i - k] - 1;
                    K[j] =make_pair(tmp,T[j].second);
                }
            }
            bool canit = true;
            sort(K,K+n);
            for(int j = 0;j < n && canit;++j)
            {
                if(K[j].second != T[j].second)
                    canit =false;
            }
            if(canit)
            {
//                for(int j = 0; j< n;++j)
//                    cout<<K[j].first<<" "<<K[j].second<<endl;
                return "Exists";
            }
        }
        return "Does not exist";
    }
};