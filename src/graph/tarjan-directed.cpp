int dfn[N], low[N], idx, sta[N], top, ins[N], scc, bel[N];
void tarjan(int x) {
    dfn[x] = low[x] = ++idx, sta[++top] = x, ins[x] = 1;
    for (int to : v[x]) {
        if (!dfn[to]) {
            tarjan(to);
            low[x] = min(low[x], low[to]);
        } else if (ins[to]) {
            low[x] = min(low[x], dfn[to]);
        }
    }
    if (dfn[x] == low[x]) {
        scc++;
        do {
            bel[sta[top]] = scc;
            ins[sta[top]] = 0;
        } while (x != sta[top--]);
    }
}