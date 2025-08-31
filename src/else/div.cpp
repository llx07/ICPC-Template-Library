int ceil(int x, int y) {
  return (x>0 ? (x+y-1)/y : x/y);
}
int floor(int x, int y) {
  return (x>0 ? x/y : (x-y+1)/y);
}
