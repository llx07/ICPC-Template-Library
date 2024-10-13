struct edge {
    int a, b, next, f, v;
} e[M << 1];
int n, m, s, t, cnt = 1, flow, cost, head[N], dis[N], inq[N], pre[N], f[N];
queue<int> q;

void add_edge(int a, int b, int f, int v) {
    e[++cnt] = {a, b, head[a], f, v};
    head[a] = cnt;
} // cnt 的初值为 1 ，head[] 的初值为 0 。即从 2 开始编号，以保证异或 1 得到反向边。
void add(int a, int b, int f, int v) {
    add_edge(a, b, f, v), add_edge(b, a, 0, -v);
}

bool spfa() {
    for (int i = 1; i <= n; i++) f[i] = dis[i] = inf, inq[i] = 0, pre[i] = -1;
    q.push(s), inq[s] = 1, dis[s] = 0, pre[s] = -1;
    while (!q.empty()) {
        int x = q.front(); q.pop();
        inq[x] = 0;
        for (int i = head[x]; i; i = e[i].next) {
            if (e[i].f > 0 && dis[e[i].b] > dis[x] + e[i].v) {
                dis[e[i].b] = dis[x] + e[i].v;
                pre[e[i].b] = i;
                f[e[i].b] = min(e[i].f, f[x]);
                if (!inq[e[i].b]) inq[e[i].b] = 1, q.push(e[i].b);
            }
        }
    }
    return pre[t] != -1;
}
void mcmf() {
    while (spfa()) {
        flow += f[t], cost += f[t] * dis[t];
        int x = t;
        while (x != s) {
            e[pre[x]].f -= f[t], e[pre[x] ^ 1].f += f[t];
            x = e[pre[x]].a;
        }
    }
}