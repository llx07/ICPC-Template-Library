int dfn[N], low[N], idx;
void tarjan(int x, int fa) {
    dfn[x] = low[x] = ++idx;
    for (int to : v[x]) {
        if (!dfn[to]) {
            tarjan(to, x);
            low[x] = min(low[x], low[to]);
            if (dfn[x] < low[to]) {
                // (x, to) 是桥。
            }
        } else if (to != fa) {
            low[x] = min(low[x], dfn[to]);
        }
    }
} // 要求无重边。