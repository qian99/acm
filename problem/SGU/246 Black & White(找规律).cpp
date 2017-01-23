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
#include<set>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
//int n,N,K;
//int a[22],b[22],flag;
//bool check()
//{
//    int tot=0;
//    for(int i=0;i<N;++i)
//        if(a[i]) b[tot++]=i;
//    for(int i=0;i<tot;++i)
//        for(int j=i;j<tot;++j)
//        {
//            int tmp=b[j]-b[i]-1;
//            if(tmp==n) return true;
//            tmp=b[j]-b[i]+1;
//            if(N-tmp==n) return true;
//        }
//    return false;
//}
//void dfs(int pos,int x)
//{
//    if(pos==N)
//    {
//        if(x) return ;
//        flag&=check();
//        return ;
//    }
//    if(!flag) return ;
//    if(x)
//    {
//        a[pos]=1;
//        dfs(pos+1,x-1);
//        a[pos]=0;
//        dfs(pos+1,x);
//    }
//    else
//    {
//        for(int i=pos;i<N;++i)
//            a[i]=0;
//        dfs(N,0);
//    }
//}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
//    while(cin>>n)
//    {
//        N=2*n-1;
//        for(K=2;K<10;++K)
//        {
//            flag=true;
//            dfs(0,K);
//            if(flag) break;
//        }
//        cout<<K<<endl;
//    }
    int n;
    cin>>n;
    if(n%3==0) cout<<n/2<<endl;
    else cout<<n/2+1<<endl;
    return 0;
}
