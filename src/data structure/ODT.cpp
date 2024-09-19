// 珂朵莉树的本质是颜色段均摊。若保证数据随机，可以证明其期望时间复杂度为 O(nlogn) 。
struct ODT {
    struct node {
        int l, r;
        mutable int val;
        node(int L, int R, int V) { l = L, r = R, val = V; }
        bool operator < (const node &rhs) const { return l < rhs.l; }
    };
    set<node> s;
    auto split(int x) {
        auto it = s.lower_bound(node(x, 0, 0));
        if (it != s.end() && it->l == x) return it;
        it--;
        int l = it->l, r = it->r, val = it->val;
        s.erase(it), s.insert(node(l, x - 1, val));
        return s.insert(node(x, r, val)).first;
    }
    void assign(int l, int r, int val) {
        // 此处须先 split(r + 1) 。因为若先 split(l) ，则后来的 split(r + 1) 可能致使 itl 失效。
        auto itr = split(r + 1), itl = split(l);
        s.erase(itl, itr), s.insert(node(l, r, val));
    }
    void perform (int l, int r) {
        auto itr = split(r + 1), itl = split(l);
        while (itl != itr) {
            // do something...
            itl++;
        }
    }
} odt;