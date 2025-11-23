struct PAM {
    // tot: 字符串长度，cnt: 节点个数
    int fail[N], ch[N][26], len[N], s[N], tot, cnt, lst;
    // fail : 当前节点的最长回文后缀。
    // ch : 在当前节点的前后添加字符，得到的回文串。
    PAM() {
        len[0] = 0, len[1] = -1, fail[0] = 1;
        tot = lst = 0, cnt = 1, s[0] = -1;
    }
    int get_fail(int x) {
        while (s[tot-1-len[x]] != s[tot]) x = fail[x];
        return x;
    }
    void insert(char c) {
        s[++tot] = c - 'a';
        int p = get_fail(lst);
        if(!ch[p][s[tot]]) {
            len[++cnt] = len[p] + 2;
            int t = get_fail(fail[p]);
            fail[cnt] = ch[t][s[tot]];
            ch[p][s[tot]] = cnt;
        }
        lst=ch[p][s[tot]];
    }
} pam;