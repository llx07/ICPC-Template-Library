int dfn[N], low[N], cut[N], idx;
void tarjan(int x, int fa) {
    dfn[x] = low[x] = ++idx;
    int cnt = 0;
    for (int to : v[x]) {
        if (!dfn[to]) {
            tarjan(to, x), cnt++;
            low[x] = min(low[x], low[to]);
            if (rt != x && low[to] >= dfn[x]) cut[x] = 1;
        } else if (to != fa) {
            low[x] = min(low[x], dfn[to]);
        }
    }
    if (rt == x && cnt >= 2) cut[x] = 1;
}