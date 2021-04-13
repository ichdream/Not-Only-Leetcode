#include<vector>
//quick_union.h
class UF {
public:
  UF(int N) {
    cnt = N;
    id.resize(N);
    for(int i = 0; i < N; i++) {
      id[i] = i;
    }
  }
  int count() { return cnt;}
  bool connected(int p, int q) {
    return find(p) == find(q);
  }
  int find(int p) {
    // 寻找p节点所在的根节点
    // 根节点的特点是id[p]=p
    while(p != id[p]) p = id[p];
    return p;
  }
  void merge(int p, int q) {
    int pRoot = find(p), qRoot = find(q);
    if(pRoot == qRoot) return;
    // 将树qRoot的父节点设置为pRoot
    // 两颗树合并为一颗
    id[pRoot] = qRoot;
    if(cnt) cnt--;
  }
private:
  std::vector<int> id;
  int cnt;
};