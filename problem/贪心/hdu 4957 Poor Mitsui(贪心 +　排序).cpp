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
const int maxn = 55;
struct Node
{
    int A,B;
    Node(int A = 0,int B = 0):A(A),B(B){}
}node[maxn];
double times[maxn];
int n,V;
bool cmp(Node a,Node b)
{
    double tmp = (double)b.B/(V-b.A);
    double t1 = tmp + tmp*a.A/(V-a.A) + (double)a.B/(V-a.A);
    tmp = (double)a.B/(V-a.A);
    double t2 = tmp + tmp*b.A/(V-b.A) + (double)b.B/(V-b.A);
    return t1 < t2;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int N = 0;
        scanf("%d%d",&n,&V);
        bool flag = true;
        for(int i = 0;i < n;++i)
        {
            scanf("%d",&node[i].A);
        }
        for(int i = 0;i < n;++i)
        {
            scanf("%d",&node[i].B);
            if(node[i].B == 0) continue;
            if(node[i].A >= V) flag = false;
            node[N++] = node[i];
        }
        if(!flag)
        {
            puts("-1");
            continue;
        }
        if(N == 0)
        {
            puts("0");
            continue;
        }
        sort(node,node + N,cmp);
        double sum = 0,tmp;
        for(int i = N - 1;i >= 0;--i)
        {
            tmp = sum*node[i].A/(V - node[i].A) + (double)node[i].B/(V-node[i].A);
            sum += tmp;
        }
        printf("%.0f\n",sum);
    }
    return 0;
}
