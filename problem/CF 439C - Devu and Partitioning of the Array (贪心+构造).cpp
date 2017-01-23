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
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100000+10;
vector<int>vt[maxn];
vector<int>odd,even;
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,k,p;
    cin>>n>>k>>p;
    int tmp;
    for(int i=0;i<n;++i)
    {
        cin>>tmp;
        if(tmp&1)
            odd.push_back(tmp);
        else
            even.push_back(tmp);
    }
    bool flag=true;
    int x=0,y=0;
    int size1=odd.size();
    int size2=even.size();
    for(int i=0;i<k-p;++i)
    {
        if(x<size1) vt[i].push_back(odd[x]);
        else {flag=false;break;}
        x++;
    }
    for(int i=0;i<p;++i)
    {
        if(y<size2) vt[k-p+i].push_back(even[y]),y++;
        else
        {
            if(size1-x>=2)
            {
                vt[k-p+i].push_back(odd[x]);
                vt[k-p+i].push_back(odd[x+1]);
                x+=2;
            }
            else {flag=false;break;}
        }
    }
    if((size1-x)&1) flag=false;
    else
    {
        for(;x<size1;++x)
            vt[0].push_back(odd[x]);
        for(;y<size2;++y)
            vt[0].push_back(even[y]);
    }
    if(flag)
    {
        puts("YES");
        for(int i=0;i<k;++i)
        {
            int size=vt[i].size();
            printf("%d",size);
            for(int j=0;j<size;++j)
                printf(" %d",vt[i][j]);
            printf("\n");
        }
    }
    else puts("NO");
    return 0;
}