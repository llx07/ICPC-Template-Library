struct SAM{ // 注意修改字符集！字符集是小写字母吗？
    int last = 1, tot = 1;
    map<int,int> ch[N<<1];
    int len[N<<1], f[N<<1];
    vector<int> G[N<<1];
    void ins(char c){
        c -= 'a';
        int p = last, cur = last = ++tot;
        len[cur]=len[p]+1;
        for(;p&&!ch[p].count(c);p=f[p])ch[p][c]=cur;
        if(!p){f[cur]=1;return;}
        int q=ch[p][c];
        if(len[q]==len[p]+1){f[cur]=q;return;}
        int clone=++tot;
        ch[clone]=ch[q];
        f[clone]=f[q],len[clone]=len[p]+1;
        f[q]=f[cur]=clone;
        for(;p&&ch[p].count(c)&&ch[p][c]==q;p=f[p]) ch[p][c]=clone;
    }
}sam;