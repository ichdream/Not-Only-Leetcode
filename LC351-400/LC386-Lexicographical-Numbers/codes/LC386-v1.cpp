class Solution {
public:
    vector<int> lexicalOrder(int n) {
        vector<int> res;
        if(n <= 0) return res;
        for(int i = 1; i <= 9; i++) {
            dfs(i, n, res);
        }
        return res;
    }
    void dfs(int num, int n, vector<int>& res) {
        if(num > n) return;
        res.emplace_back(num);
        for(int i = 0; i <= 9; i++) {
            dfs(num * 10 + i, n, res);
        }
    }
};