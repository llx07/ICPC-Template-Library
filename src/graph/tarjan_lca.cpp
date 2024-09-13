inline void add_edge(int x,int y){ ver[++tot]=y,nex[tot]=hea[x],hea[x]=tot; }
inline void add_query(int x,int y,int d)
	 { qver[++qtot]=y,qnex[qtot]=qhea[x],qhea[x]=qtot, qid[qtot]=d; }
int Find(int x){ return (fa[x]==x)?x:(fa[x]=Find(fa[x])); }
void tarjan(int x,int F)
{
	 vis[x]=true;
	 for(int i=hea[x];i;i=nex[i])
	 {
	 	 if(ver[i]==F) continue;
	 	 tarjan(ver[i],x),fa[ver[i]]=x;
	 }
	 for(int i=qhea[x];i;i=qnex[i])
	 {
	 	 if(!vis[qver[i]]) continue;
	 	 ans[qid[i]]=Find(qver[i]);
	 }
}
for(int i=1;i<=n;i++) fa[i]=i;
for(int i=1,x,y;i<n;i++) x=rd(),y=rd(),add_edge(x,y),add_edge(y,x);
for(int i=1,x,y;i<=m;i++)
	 x=rd(),y=rd(),add_query(x,y,i),add_query(y,x,i);
tarjan(s,s);
for(int i=1;i<=m;i++) printf("%d\n",ans[i]);