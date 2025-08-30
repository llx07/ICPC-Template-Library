int tp,sta[N];
int tot,hea[N],tmphea[N],used[M<<1],ver[M<<1],nex[M<<1];
void add(int x,int y) { ver[++tot]=y,nex[tot]=hea[x],hea[x]=tot; }
// tot 初值为 1 ; tmphea 初值为 hea
void dfs(int x)
{
    while (tmphea[x])
    {
        int i=tmphea[x];
        tmphea[x]=nex[i];
        if(!used[i]) used[i]=used[i^1]=1,dfs(ver[i]);
    }
    sta[++tp]=x;
} // sta[] 存储了反向的欧拉路。