#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=10000+10;
pair<int,int>pii[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,A0,B0,A,B;
    cin>>n>>A0>>B0;
    int i=1,cnt=0;
    A0%=n;B0%=n;
    A=A0;B=B0;
    while(true)
    {
        A=(A+A0)%n;B=(B+B0)%n;
        pii[cnt].first=A;pii[cnt++].second=B;
        i++;
        if(A==A0&&B==B0) break;
    }
    sort(pii,pii+cnt);
    printf("%d\n",cnt);
    for(int j=0;j<cnt;++j)
      printf("%d %d\n",pii[j].first,pii[j].second);
    return 0;
}
