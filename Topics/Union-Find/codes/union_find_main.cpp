#include<iostream>
#include<vector>
// #include "union_find_v1.h"
#include "quick_union_v2.h"
using namespace std;
int main() {
    int N = 0;
    cout << "input the number of nodes: N" << "\n";
    cin >> N;
    UF uf(N);
    int a = 0, b = 0;
    cout << "input the number of needed connected pairs: m" << "\n";
    int m = 0;
    cin >> m;
    for(int i = 0; i < m; i++) {
        cin >> a >> b;
        uf.merge(a, b);
        cout << "now, the number of group:  " << uf.count() << endl;
    }
}