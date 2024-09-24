int siz[N], rt, tot, dfa[N], mxp[N], vis[N], mxd;
// rt: 当前重心，tot: 联通块大小，dfa: 点分树父亲，mxp: 最大子树大小，mxd: 最大深度。
void find(int x, int fa) {
    siz[x] = 1, mxp[x] = 0;
    for (int i = head[x]; i; i = e[i].next)
    {
        if (e[i].b != fa && !vis[e[i].b])
        {
            find(e[i].b, x);
            siz[x] += siz[e[i].b];
            mxp[x] = max(mxp[x], siz[e[i].b]);
        }
    }
    mxp[x] = max(mxp[x], tot - siz[x]);
    rt = mxp[rt] > mxp[x] ? x : rt;
}
void get_dis(int x, int fa, int dep) {
    mxd = max(mxd, dep);
    for (int i = head[x]; i; i = e[i].next)
        if (e[i].b != fa && !vis[e[i].b])
            get_dis(e[i].b, x, dep + 1);
}
// bit[x][0]: 存储了以 x 为重心时 x 的子树内的信息。
// bit[x][1]: 存储了以 dfa[x] 为重心时 x 的子树内的信息。
void divide(int x, int lim) {
    vis[x] = 1, mxd = 0, get_dis(x, 0, 0);
    bit[x][0].build(mxd);
    if (dfa[x]) bit[x][1].build(lim);
    for (int i = head[x]; i; i = e[i].next) {
        if (!vis[e[i].b]) {
            rt = 0, tot = siz[e[i].b] < siz[x] ? siz[e[i].b] : lim - siz[x];
            find(e[i].b, x);
            dfa[rt] = x, divide(rt, tot);
        }
    }
}
void modify(int ct, int v) {
    int x = ct;
    while (x) {
        bit[x][0].add(dis(x, ct), v); // dis(x, y): 返回 x 到 y 的距离。
        if (dfa[x]) bit[x][1].add(dis(dfa[x], ct), v);
        x = dfa[x];
    }
} // 将点 ct 的值加上 v 。
int query(int ct, int k) {
    int x = ct, res = 0, lst = 0;
    while (x) {
        int d = dis(x, ct);
        if (d <= k) {
            res += bit[x][0].query(k - d);
            if (lst) res -= bit[lst][1].query(k - d);
        }
        lst = x, x = dfa[x];
    }
    return res;
}
void init() {
    // dis 的预处理。
    mxp[rt = 0] = tot = n, find(1, 0), divide(rt, tot);
}