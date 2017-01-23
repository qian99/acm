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
const int maxn=100000+10;
struct Trie
{
    int ch[10];
    int val;
    void clear()
    {
        for(int i=0;i<10;++i)
          ch[i]=0;
        val=0;
    }
};
int size;
Trie trie[maxn];
bool Insert(char *str)
{
    int len=strlen(str);
    int s=0;
    for(int i=0;i<len;++i)
    {
        int k=str[i]-'0';
        if(trie[s].ch[k]==0)
        {
            size++;
            trie[size].clear();
            trie[s].ch[k]=size;
        }
        s=trie[s].ch[k];
        if(trie[s].val>0) return false;
        if(i==len-1&&trie[s].ch[k]!=0) return false;
        if(i==len-1)
          trie[s].val++;
    }
    return true;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        bool flag=true;
        char ss[50];
        size=0;
        trie[0].clear();
        for(int i=0;i<n;++i)
        {
            scanf("%s",ss);
            if(!Insert(ss))
              flag=false;
        }
        if(flag)
          printf("YES\n");
        else
          printf("NO\n");
    }
    return 0;
}
