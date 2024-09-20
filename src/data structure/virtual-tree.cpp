int dfn[N];
vector<int> v, w; // v 为关键点，w 为虚树上的点。
bool cmp(int x, int y) { return dfn[x] < dfn[y]; }
void build() {
    sort(v.begin(), v.end(), cmp);
    w.push_back(v[0]);
    for (int i = 1; i < v.size(); i++) {
        w.push_back(lca(v[i - 1], v[i]));
        w.push_back(v[i]);
    } // 提取虚树中的所有点。
    sort(w.begin(), w.end(), cmp);
    w.erase(unique(w.begin(), w.end()), w.end());
    for (int i = 1; i < w.size(); i++) {
        connect(lca(w[i - 1], w[i]), w[i]);
    } // 构建虚树。即对于每一个虚树中的非根节点，向其父亲连边。
}