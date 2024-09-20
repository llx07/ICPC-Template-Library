// 声明 line 类
struct SMT {
    // 定义 mid
    struct node {
        line f;
        int ch[2];
        #define f(x) nod[x].f
        #define ls(x) nod[x].ls
        #define rs(x) nod[x].rs
    } nod[N];
    // 实现 insert 与 query
    int merge(int x, int y, int l, int r) {
        if (!x || !y) return x | y;
        if (l < r) {
            ls(x) = merge(ls(x), ls(y), l, mid);
            rs(x) = merge(rs(x), rs(y), mid + 1, r);
        }
        insert(x, l, r, f(y));
        // 注意此处的 insert 为全局插入。
        return x;
    } // 理论上李超树的合并是 O(nlog^2n) 的，但是我并不知道怎么证明。
}