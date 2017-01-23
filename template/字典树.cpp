#include <iostream>

#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
const int maxn=1<<21;
int size;
struct Trie
{
    int ch[26];
    int val;
    void clear()
    {
        val=0;
        for(int i=0;i<26;++i) ch[i]=0;
    }
};
Trie trie[maxn];
void Insert(char *str)
{
    int len=strlen(str);
    int s=0;
    for(int i=0;i<len;++i)
    {
        int k=str[i]-'a';
        if(trie[s].ch[k]==0)
        {
            size++;
            trie[s].ch[k]=size;
            //trie[s].val[k]=size;
            trie[size].clear();
        }
        s=trie[s].ch[k];
        trie[s].val++;
    }
}
int Find(char *str)
{
    int len=strlen(str);
    int k,s=0;
    for(int i=0;i<len;++i)
    {
        k=str[i]-'a';
        if(trie[s].ch[k]==0)
        {
            return 0;
        }
        else
        {
            s=trie[s].ch[k];
        }
    }
    return trie[s].val;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    size=0;
    char a[20];
    trie[0].clear();
    while(gets(a))
    {
        if(strlen(a)==0) break;
        Insert(a);
    }
    while(gets(a))
    {
        int ans=Find(a);
        printf("%d\n",ans);
    }
    return 0;
}