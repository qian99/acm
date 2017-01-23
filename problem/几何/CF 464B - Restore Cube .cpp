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
inline double dis(int *a,int *b)
{
    double res = 0;
    for(int i = 0; i < 3;++i)
        res += (double)(a[i] - b[i])*(a[i] - b[i]);
    return sqrt(res);
}
inline int dcmp(double x)
{
    if(fabs(x) < eps) return 0 ;
    return x < 0 ? -1 : 1;
}
int pt[8][3];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    for(int i = 0;i < 8;++i)
    {
        scanf("%d%d%d",&pt[i][0],&pt[i][1],&pt[i][2]);
        sort(pt[i],pt[i] + 3);
    }
    do
    {
        do
        {
            do
            {
                do
                {
                    do
                    {
                        do
                        {
                            do
                            {
                                do
                                {
                                    double d = dis(pt[0],pt[1]),tmp;
                                    for(int i = 2;i < 8;++i)
                                        d = min(d,dis(pt[0],pt[i]));
                                    int a = 0,b = 0,c = 0;
                                    for(int i = 0;i < 8;++i)
                                        for(int j = i + 1;j < 8;++j)
                                        {
                                            tmp = dis(pt[i],pt[j]);
                                            if(dcmp(tmp - d) == 0) a++;
                                            else if(dcmp(sqrt(2.0)*d - tmp) == 0) b++;
                                            else if(dcmp(sqrt(3.0)*d - tmp) == 0) c++;
                                        }
                                    if(a == 12 && b == 12 && c == 4)
                                    {
                                        puts("YES");
                                        for(int i = 0;i < 8;++i)
                                            printf("%d %d %d\n",pt[i][0],pt[i][1],pt[i][2]);
                                        return 0;
                                    }
                                }while(next_permutation(pt[7],pt[7] + 3));
                            }while(next_permutation(pt[6],pt[6] + 3));
                        }while(next_permutation(pt[5],pt[5] + 3));
                    }while(next_permutation(pt[4],pt[4] + 3));
                }while(next_permutation(pt[3],pt[3] + 3));
            }while(next_permutation(pt[2],pt[2] + 3));
        }while(next_permutation(pt[1],pt[1] + 3));
    }while(next_permutation(pt[0],pt[0] + 3));
    puts("NO");
    return 0;
}
