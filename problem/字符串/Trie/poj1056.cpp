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
    int ch[2];
    int val;
    void clear()
    {
        for(int i=0;i<2;++i)
          ch[i]=0;
        val=0;
    }
};
int size;
Trie trie[maxn];
void Insert(char *str)
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
        trie[s].val++;
        s=trie[s].ch[k];
    }
}
bool find(char *str)
{
    int len=strlen(str);
    int s=0;
    for(int i=0;i<len;++i)
    {
        int k=str[i]-'0';
        if(trie[s].ch[k]==0&&i>0)
        {
            for(int j=0;j<2;++j)
              if(trie[s].ch[j]!=0) return false;
            return true;
        }
        if(trie[s].ch[k]==0) return false;
        s=trie[s].ch[k];
    }
    return true;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    char ss[50];
    int tcase=0;
    while(~scanf("%s",ss))
    {
        bool flag=false;
        tcase++;
        size=0;
        trie[0].clear();
        Insert(ss);
        while(~scanf("%s",ss))
        {
            if(ss[0]=='9') break;
            if(find(ss))
              flag=true;
            if(!find(ss))
              Insert(ss);
        }
        if(!flag)
          printf("Set %d is immediately decodable\n",tcase);
        else
          printf("Set %d is not immediately decodable\n",tcase);
    }
    return 0;
}
