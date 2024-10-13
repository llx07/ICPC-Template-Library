int dfn[N], low[N], idx, sta[N], top, dcc;
void tarjan(int x, int fa) {
    dfn[x] = low[x] = ++idx, sta[++top] = x;
    for (int to : v[x]) {
        if (!dfn[to]) {
            tarjan(to, x);
            low[x] = min(low[x], low[to]);
            if (low[to] == dfn[x]) {
                dcc++;
                do {
                    // connect(sta[top], dcc);
                } while (sta[top--] != to);
                // connect(x, dcc);
            }
        } else {
            low[x] = min(low[x], dfn[to]);
        }
    }
}