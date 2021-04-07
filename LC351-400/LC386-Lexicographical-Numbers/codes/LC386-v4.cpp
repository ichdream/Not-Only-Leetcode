class Solution {
public:
    vector<int> lexicalOrder(int n) {
        if(n <= 0) return {};
        vector<int> res;
        stack<int> s;
        for(int i = min(n, 9); i >= 1; i--) s.push(i);
        while(!s.empty()) {
            int num = s.top();
            s.pop();
            res.emplace_back(num);
            for(int i = 9; i >= 0; i--) {
                int tmp = num * 10 + i;
                if(tmp > n) continue;
                s.push(tmp);
            }
        }
        return res;
    }
};