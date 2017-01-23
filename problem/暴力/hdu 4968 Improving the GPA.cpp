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
int maxpt[5] = {100,84,79,74,69};
int minpt[5] = {85,80,75,70,60};
double Gpa[5] = {4.0,3.5,3.0,2.5,2.0};
bool check(int a[5],int val)
{
    int n = 0;
    for(int i = 0;i < 5;++i) n += a[i];
    int maxsum = 0 , minsum = 0;
    for(int i = 0;i < 5;++i)
    {
        maxsum += a[i] * maxpt[i];
        minsum += a[i] * minpt[i];
    }
    val *= n;
    return val >= minsum && val <= maxsum;
}
double getGpa(int a[5])
{
    int n = 0;
    for(int i = 0;i < 5;++i) n += a[i];
    double res = 0;
    for(int i = 0;i < 5;++i)
        res += Gpa[i]*a[i];
    return res/n;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int avg,n;
        scanf("%d%d",&avg,&n);
        double maxgpa = 0, mingpa = 5,gpa;
        int a[5];
        for(a[0] = 0;a[0] <= n;++a[0])
        for(a[1] = 0;a[0] + a[1]<= n;++a[1])
        for(a[2] = 0;a[0] + a[1] + a[2] <= n;++a[2])
        for(a[3] = 0;a[0] + a[1] + a[2] + a[3] <= n;++a[3])
        {
            a[4] = n - a[0] - a[1] - a[2] - a[3];
            if(check(a,avg))
            {
                gpa = getGpa(a);
                maxgpa = max(maxgpa,gpa);
                mingpa = min(mingpa,gpa);
            }
        }
        printf("%.4lf %.4lf\n",mingpa,maxgpa);
    }
    return 0;
}
