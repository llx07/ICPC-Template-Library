/*** Dinic 最大流 ***/
struct Dinic
{
	#define Maxn 点数
	#define Maxm 边数
	int tot=1;
	int hea[Maxn],nex[Maxm<<1],ver[Maxm<<1];
	int tmphea[Maxn],dep[Maxn];
	ll edg[Maxm<<1],sum;
	inline void init()
		{ tot=1,memset(hea,0,sizeof(hea)); }
	inline void add_edge(int x,int y,ll d)
	{
		ver[++tot]=y,nex[tot]=hea[x],hea[x]=tot,edg[tot]=d;
		ver[++tot]=x,nex[tot]=hea[y],hea[y]=tot,edg[tot]=0;
	}
	inline bool bfs(int s,int t)
	{
		memset(dep,0,sizeof(dep)),dep[s]=1;
		memcpy(tmphea,hea,sizeof(hea));
		queue<int> q; q.push(s);
		while(!q.empty())
		{
			int cur=q.front(); q.pop();
			if(cur==t) return true;
			for(int i=hea[cur];i;i=nex[i]) if(edg[i]>0 && !dep[ver[i]])
				dep[ver[i]]=dep[cur]+1,q.push(ver[i]);
		}
		return false;
	}
	ll dfs(int x,ll flow,int t)
	{
		if(x==t || !flow) return flow;
		ll rest=flow,tmp;
		for(int i=tmphea[x];i && rest;i=nex[i])
		{
			tmphea[x]=i;
			if(dep[ver[i]]==dep[x]+1 && edg[i]>0)
			{
				if(!(tmp = dfs(ver[i],min(edg[i],rest),t))) dep[ver[i]]=0;
				edg[i]-=tmp,edg[i^1]+=tmp,rest-=tmp;
			}
		}
		return flow-rest;
	}
	inline ll solve(int s,int t)
	{
		sum=0;
		while(bfs(s,t)) sum+=dfs(s,inf,t);
		return sum;
	}
	#undef Maxn
	#undef Maxm
}G;