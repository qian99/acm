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
const int maxn=1000;
int num[maxn][maxn];
struct Item
{
    int s,b;
    bool operator < (const Item &a) const
    {
        return a.s<s;
    }
};
void Uion(int A[maxn],int B[maxn],int C[maxn],int n)
{
    priority_queue<Item>pq;
    Item tp;
    for(int i=0;i<n;++i)
    {
        tp.s=A[i]+B[0];
        tp.b=0;
        pq.push(tp);
    }
    for(int i=0;i<n;++i)
    {
        tp=pq.top();
        pq.pop();
        C[i]=tp.s;
        if(tp.b<n-1)
        {
            tp.s=tp.s-B[tp.b]+B[tp.b+1];
            tp.b++;
            pq.push(tp);
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(cin>>n)
    {
        for(int i=0;i<n;++i)
        {
            for(int j=0;j<n;++j)
                cin>>num[i][j];
            sort(num[i],num[i]+n);
        }
        for(int i=1;i<n;++i)
        {
            Uion(num[0],num[i],num[0],n);
        }
        bool first=true;
        for(int i=0;i<n;++i)
        {
            if(!first) cout<<" ";
            first=false;
            cout<<num[0][i];
        }
        cout<<endl;
    }
    return 0;
}

