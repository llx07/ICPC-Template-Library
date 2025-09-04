// 记得修改字符集大小和字符种类
const int SIGMA = 26;
const char BASE = 'a';
int ch[N][SIGMA],fail[N],cnt[N],tot=1;
void ins(const string& s){
    int u=1;
    for(int i=0;i<s.size();i++){
        int c=s[i]-BASE;
        if(!ch[u][c])ch[u][c]=++tot;
        u=ch[u][c];
    }
    cnt[u]++;
}
void get_fail(){
    for(int i=0;i<SIGMA;i++)ch[0][i]=1;
    fail[1]=0;
    queue<int> q;q.push(1);
    while(q.size()){
        int u=q.front();q.pop();
        for(int c=0;c<SIGMA;c++){
            int v=ch[u][c];
            if(!v)ch[u][c]=ch[fail[u]][c];
            else{
                fail[v]=ch[fail[u]][c];
                q.push(v);
            }
        }
    }
}