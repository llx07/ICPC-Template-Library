void tarjan(int x)
{
	dfn[x]=low[x]=++Time,sta[++tp]=x,ins[x]=true;
	for(int i=hea[x];i;i=nex[i])
	{
		if(!dfn[ver[i]]) tarjan(ver[i]),low[x]=min(low[x],low[ver[i]]);
		else if(ins[ver[i]]) low[x]=min(low[x],dfn[ver[i]]);
	}
	if(dfn[x]==low[x])
	{
		do
		{
			x=sta[tp],tp--,ins[x]=false;
		} while (dfn[x]!=low[x]);
	}
}
