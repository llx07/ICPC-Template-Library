int n, m, flow, S, T, now[N], head[N], cnt = 1, dep[N];
queue<int> q;
struct edge {
    int a, b, next, f;
} e[M << 1];
void add_edge(int a, int b, int f) {
    e[++cnt] = {a, b, head[a], f};
    head[a] = cnt;
} // cnt 的初值为 1 ，head[] 的初值为 0 。即从 2 开始编号，以保证异或 1 得到反向边。
void add(int a, int b, int f) { add_edge(a, b, f), add_edge(b, a, 0); }

bool bfs() {
    for (int i = 1; i <= n; i++) dep[i] = 0;
    while (!q.empty()) q.pop();
    dep[S] = 1, q.push(S), now[S] = head[S];
    while (!q.empty()) {
        int x = q.front(); q.pop();
        if (x == T) return 1;
        for (int i = head[x]; i; i = e[i].next) {
            if (e[i].f && !dep[e[i].b]) {
                dep[e[i].b] = dep[x] + 1;
                now[e[i].b] = head[e[i].b];
                q.push(e[i].b);
            }
        }
    }
    return 0;
}
int dfs(int x, int mn) {
    if (x == T) return mn;
    int res = 0;
    for (int i = now[x]; i && mn; i = e[i].next) {
        now[x] = i;
        if (e[i].f && dep[e[i].b] == dep[x] + 1) {
            int k = dfs(e[i].b, min(mn, e[i].f));
            if (!k) dep[e[i].b] = 0;
            res += k, mn -= k;
            e[i].f -= k, e[i ^ 1].f += k;
        }
    }
    return res;
}
void dinic() {
    while (bfs()) flow += dfs(S, inf);
}