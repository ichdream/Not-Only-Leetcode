class Solution {
public:
    vector<int> lexicalOrder(int n) {
        vector<int> res;
        if(n <= 0) return res;
        for(int i = 1; i <= n; i++) {
            res.emplace_back(i);
        }
        sort(res.begin(), res.end(), [](int c1, int c2){
            string s1 = to_string(c1);
            string s2 = to_string(c2);
            int i = 0;
            while(i < s1.size() && i < s2.size()) {
                if(s1[i] == s2[i]) i++;
                else return s1[i] < s2[i];
            }
            return i == s1.size();
        });
        return res;
    }
};