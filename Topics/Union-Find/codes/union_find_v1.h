#include<vector>
class UF {
public:
  UF(int N) {
    cnt = N;
    id.resize(N);
    for(int i = 0; i < id.size(); i++) {
      id[i] = i;
    }
  }
  int count() { return cnt;}
  bool connected(int p, int q) {
    return find(p) == find(q);
  }
  int find(int p) {return id[p];}
  void merge(int p, int q) {
    int pId = find(p), qId = find(q);
    if(pId == qId) return;
    for(int i = 0; i < id.size(); i++) {
      if(id[i] == qId) id[i] = pId;
    }
    if(cnt) cnt--;
  }
private:
  std::vector<int> id;
  int cnt;
};