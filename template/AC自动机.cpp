int ch[20010][26],val[20010],size,lastv[20010],next[20010];
void Init()
{
    memset(ch[0],0,sizeof(ch[0]));
    val[0]=0;size=0;
}
void insert(const char * s,int v)
{
    int u=0,n=strlen(s);
    for(int i=0;i<n;++i)
    {
        int c=s[i]-'a';
        if(!ch[u][c])
        {
            ch[u][c]=++size;
            memset(ch[size],0,sizeof(ch[size]));
            val[size]=0;
        }
        u=ch[u][c];
    }
    val[u]=v;
}
void build()
{
    queue<int>q;
    memset(lastv,0,sizeof(lastv));
    memset(next,0,sizeof(next));
    for(int i=0;i<26;++i)
        if(ch[0][i]) {q.push(ch[0][i]);}
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int c=0;c<26;++c)
        {
            int v=ch[u][c];
            if(!v) {ch[u][c]=ch[next[u]][c];continue;}
            q.push(v);
            int j=next[u];
            while(j&&!ch[j][c]) j=next[j];
            next[v]=ch[j][c];
            lastv[v]=val[next[v]]?next[v]:lastv[next[v]];
        }
    }
}
void find(const char * s)
{
    int n=strlen(s);
    int j=0;
    for(int i=0;i<n;++i)
    {
        int c=s[i]-'a';
        j=ch[j][c];
        if(val[j]||lastv[j])
        {
            int u=val[j]?j:lastv[j];
            while(u)
            {
                cnt[val[u]]++;
                maxv=max(maxv,cnt[val[u]]);
                u=lastv[u];
            }
        }
    }
}