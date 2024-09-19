// 洛谷 P3690
struct LCT {
    struct node {
        int rv, ch[2], fa, sm, val;
        #define ls(x) nod[x].ch[0]
        #define rs(x) nod[x].ch[1]
        #define fa(x) nod[x].fa
        #define sm(x) nod[x].sm
        #define rv(x) nod[x].rv
        #define val(x) nod[x].val
    } nod[N];
    // 根节点的父亲：链顶节点的树上父亲。
    // 其余节点的父亲：splay 中的父亲。

    bool chk(int x) { return rs(fa(x)) == x; }
    bool isroot(int x) { return nod[fa(x)].ch[chk(x)] != x; }
    void pushup(int x) { sm(x) = sm(ls(x)) ^ val(x) ^ sm(rs(x)); }
    void reverse(int x) { rv(x) ^= 1, swap(ls(x), rs(x)); }
    void pushdown(int x) {
        if (rv(x)) reverse(ls(x)), reverse(rs(x)), rv(x) = 0;
    }
    void connect(int x, int fa, int son) { fa(x) = fa, nod[fa].ch[son] = x; }
    void rotate(int x) {
        int y = fa(x), z = fa(y), ys = chk(x), zs = chk(y), u = nod[x].ch[!ys];
        if (isroot(y)) fa(x) = z;
        else connect(x, z, zs);
        connect(u, y, ys), connect(y, x, !ys), pushup(y), pushup(x);
    }
    void pushall(int x) { if (!isroot(x)) pushall(fa(x)); pushdown(x); }
    void splay(int x) {
        pushall(x);
        while (!isroot(x)) {
            if (!isroot(fa(x))) rotate(chk(x) == chk(fa(x)) ? fa(x) : x);
            rotate(x);
        }
    }
    void access(int x) { for (int y = 0; x; y = x, x = fa(x)) splay(x), rs(x) = y, pushup(x); }
    void makeroot(int x) { access(x), splay(x), reverse(x); }
    int findroot(int x) { access(x), splay(x); while (ls(x)) pushdown(x), x = ls(x); return splay(x), x; }
    void link(int x, int y) { makeroot(y); if (findroot(x) != y) fa(y) = x;}
    void split(int x, int y) { makeroot(y), access(x), splay(x); }
    void cut(int x, int y) { split(x, y); if (ls(x) == y) ls(x) = fa(y) = 0, pushup(x); }
    void modify(int x, int val) { splay(x), val(x) = val, pushup(x); }
    int sum(int x, int y) { split(x, y); return sm(x); }
    // 任何操作过后都应该立即 splay 以保证均摊复杂度。
} lct;