// 洛谷 P3391
// 理论上 splay 的每次操作以后都应该立刻做 splay 操作以保证均摊时间复杂度，但是某些地方又不能立刻做，例如下面的 kth 。
int rt;
struct Splay {
    struct node {
        int val, siz, fa, ch[2], rv;
        #define ls(x) nod[x].ch[0]
        #define rs(x) nod[x].ch[1]
        #define val(x) nod[x].val
        #define siz(x) nod[x].siz
        #define fa(x) nod[x].fa
        #define rv(x) nod[x].rv
    } nod[N];
    int cnt;
    bool chk(int x) { return x == rs(fa(x)); }
    void reverse(int x) { rv(x) ^= 1, swap(ls(x), rs(x)); }
    void pushup(int x) { siz(x) = siz(ls(x)) + 1 + siz(rs(x)); }
    void pushdown(int x) { if (rv(x)) reverse(ls(x)), reverse(rs(x)), rv(x) = 0; }
    void connect(int x, int fa, int son) { fa(x) = fa, nod[fa].ch[son] = x; }
    void rotate(int x) {
        int y = fa(x), z = fa(y), ys = chk(x), zs = chk(y), u = nod[x].ch[!ys];
        connect(u, y, ys), connect(y, x, !ys), connect(x, z, zs), pushup(y), pushup(x);
    }
    void pushall(int x) { if (fa(x)) pushall(fa(x)); pushdown(x); }
    void splay(int x, int to) {
        pushall(x);
        while (fa(x) != to) {
            int y = fa(x);
            if (fa(y) != to) rotate(chk(x) == chk(y) ? y : x);
            rotate(x);
        }
        if (!to) rt = x;
    } // 将 x 伸展为 to 的儿子。
    void append(int val) {
        if (!rt) nod[rt = ++cnt] = {val, 1};
        else {
            int x = rt;
            while (rs(x)) pushdown(x), x = rs(x);
            splay(x, 0), nod[rs(x) = ++cnt] = {val, 1, x}, pushup(x);
        }
    }
    int kth(int k) {
        int x = rt;
        while (x) {
            pushdown(x);
            if (siz(ls(x)) + 1 == k) return x;
            else if (k <= siz(ls(x))) x = ls(x);
            else k -= siz(ls(x)) + 1, x = rs(x);
        }
        return -1;
    } // kth 做完以后不能立刻 splay ，因为需要提取区间。
    void reverse(int l, int r) {
        splay(kth(r + 2), 0), splay(kth(l), rt);
        reverse(rs(ls(rt))), pushup(ls(rt)), pushup(rt);
    } // 这里添加了前后两个哨兵，以避免额外的分类讨论。
} spl;