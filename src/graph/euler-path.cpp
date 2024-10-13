int s[N], top, head[N], now[N], used[M << 1], cnt;
struct edge {
    int a, b, next;
} e[M << 1];
void add(int a, int b) {
    e[++cnt] = {a, b, head[a]};
    head[a] = cnt;
} // cnt 的初值为 1 ，head[] 的初值为 0 。即从 2 开始编号，以保证异或 1 得到反向边。
void dfs(int x) {
    while (now[x]) { // now[] 的初值为 head[] 。
        int i = now[x];
        now[x] = e[now[x]].next;
        if (!used[i]) {
            used[i] = used[i ^ 1] = 1;
            dfs(e[i].b);
        }
    }
    s[++top] = x;
} // s[] 存储了反向的欧拉路。