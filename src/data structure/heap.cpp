struct heap {
    struct node {
        int val, dis, ch[2];
        #define val(x) nod[x].val
        #define ls(x) nod[x].ch[0]
        #define rs(x) nod[x].ch[1]
        #define dis(x) nod[x].dis
    } nod[N]; // dis : 节点到叶子的最短距离。
    int merge(int x, int y) {
        if (!x || !y) return x | y;
        if (val(x) > val(y)) swap(x, y);
        rs(x) = merge(rs(x), y);
        if (dis(ls(x)) < dis(rs(x))) swap(ls(x), rs(x));
        dis(x) = dis(rs(x)) + 1;
    } // 若根的 dis 为 d ，则左偏树至少包含 O(2^d) 个节点，因此 d=O(logn) 。
} hp;