vector<int> G[N];
int dep[N],fa[N],hson[N],sz[N],top[N],dfn[N],d;
void dfs1(int u,int f){
    dep[u]=dep[f]+1;
    fa[u]=f;sz[u]=1;
    for(int v:G[u]){
        if(v==f)continue;
        dfs1(v,u);sz[u]+=sz[v];
        if(sz[v]>sz[hson[u]])hson[u]=v;
    }
}
void dfs2(int u,int t){
    dfn[u]=++d;top[u]=t;
    if(hson[u])dfs2(hson[u],t);
    for(int v:G[u]){
        if(v==fa[u]||v==hson[u])continue;
        dfs2(v,v);
    }
}
void operate_path(int u,int v){ // 维护路径
    while(top[u]!=top[v]){
        if(dep[top[u]] < dep[top[v]]) swap(u,v);
        OPERATE(dfn[top[u]],dfn[u]); // 对这一区间执行任意操作
        u = fa[top[u]];
    }
    if(dep[u]>dep[v])swap(u,v); 
    OPERATE(dfn[u],dfn[v]); // 跳到同一条重链上了
}
void operate_tree(int u){ // 维护子树
    OPERATE(dfn[u],dfn[u]+sz[u]-1);
}
int lca(int u,int v){ // 求最近公共祖先
    while(top[u]!=top[v]){
        if(dep[top[u]] < dep[top[v]]) swap(u,v);
        u = fa[top[u]];
    }
    if(dep[u]>dep[v])swap(u,v);
    return u;
}