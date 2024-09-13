struct ACAM {
    int ch[N][26], cnt, fail[N], vis[N];
    queue <int> q;
    void insert(char *s, int n, int id) {
        int x = 0;
        for (int i = 1; i <= n; i++) {
            int nw = s[i] - 'a';
            if (!ch[x][nw]) ch[x][nw] = ++cnt;
            x = ch[x][nw];
        }
        vis[x]++;
    }
    void build() {
        for (int i = 0; i < 26; i++) {
            if (ch[0][i]) q.push(ch[0][i]);
        }
        while (!q.empty()) {
            int x = q.front(); q.pop();
            for (int i = 0; i < 26; i++) {
                if (ch[x][i]) {
                    fail[ch[x][i]] = ch[fail[x]][i];
                    q.push(ch[x][i]);
                } else ch[x][i] = ch[fail[x]][i];
            }
        }
    }
    void match(char *s, int n) {
        int x = 0;
        for (int i = 1; i <= n; i++) {
            int nw = s[i] - 'a';
            x = ch[x][nw];
        }
    }
} AC;