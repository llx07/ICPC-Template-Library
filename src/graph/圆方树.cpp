void tarjan(int u)
{
	dfn[u]=low[u]=++Time,sta[++tp]=u;
	for(int v:G[u])
	{
		if(!dfn[v])
		{
			tarjan(v),low[u]=min(low[u],low[v]);
			if(low[v]==dfn[u])
			{
				int hav=0; ++All;
				for(int x=0;x!=v;tp--) x=sta[tp],T[x].pb(All),T[All].pb(x),hav++;
				T[u].pb(All),T[All].pb(u),;
				siz[All]=++hav;
			}
		}
		else low[u]=min(low[u],dfn[v]);
	}
}