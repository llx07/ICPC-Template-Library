// 0-下标的！
int minpos(const string& s){
    int n = s.size();
    int k = 0, i = 0, j = 1;
    while (k < n && i < n && j < n) {
        if (s[(i+k)%n]==s[(j+k)%n])++k;
        else{
            if(s[(i + k) % n]>s[(j + k) % n]) i+=k+1;
            else j+=k+1;
            k = 0;
            if(i==j)i++;
        }
    }
    return min(i,j);
}