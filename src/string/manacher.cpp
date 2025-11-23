string s;

string t="~#";
for(int i=0;i<n;i++)t+=s[i], t+='#';
vector<int> d(t.size());
// r 是最远的右边界加 1
// 每个位置在 [i-d[i]+1, i+d[i]-1] 是回文的
for(int i=1,r=0,mid=0;i<t.size();i++){
    d[i] = r>i ? min(d[2*mid-i], r-i):1;
    while(t[i+d[i]]==t[i-d[i]])++d[i];
    if(i+d[i]>r)r=i+d[i],mid=i;
}