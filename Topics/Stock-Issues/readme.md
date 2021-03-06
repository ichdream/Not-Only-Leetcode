## 买卖股票问题

买卖股票系列问题是动态规划研究中的经典问题， Leetcode有6道股票买卖问题，我们层层递进，抽丝剥茧进行讨论。



### 1 入门级

#### ==**LC121 买卖股票最佳时机**==

【**题目描述**】：

>给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。
>
>你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票。设计一个算法来计算你所能获取的最大利润。
>
>返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 0 。
>
>示例 1：
>
>> 输入：[7,1,5,3,6,4]
>> 输出：5
>> 解释：在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
>> 注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格；同时，你不能在买入前卖出股票。
>
>来源：力扣（LeetCode）
>链接：https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock
>著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
>
>

【**受欢迎程度**】：

👏，very popular

【**难易程度**】：

简单

【题目多视角分析】

每只股票有两个状态：（1）买入，（2）卖出；对应的决策有：（1）买入，（2）卖出，（3）无任何操作，且买入决策要排在卖出前。

要使用动态规划，重要在于定义状态和状态转移方程.  

**状态定义**：dp[i]表示从0到i能获得的最大价值，但是我们发现这个状态定义无法实现状态之间的转移，因为当我们处在i位置时，可以有几种结果：

（1）i之前无任何股票买卖操作

（2）i之前买入某一种股票；

（3）i之前买入且卖出某一种股票

我们发现一维状态数组已经无法表示和区分出不同位置的状态了，增加一个纬度，用$dp[i][0]$表示在$0～i$天之间有买入和卖出操作股票可以获取的最大利润；用$dp[i][1]$表示在$[0...i]$天之间的某天只买入股票可以获取的最大利润。  


**状态转移方程**

有了状态定义，我们很自然可以写出状态转移方程$dp[i][j]$只和前一个状态$dp[i][j']$有关系，其中$j$和$j'$只取值0和1。

对于$dp[i][0]$，$[0...i]$之间有股票买入和卖出，股票卖出可以在发生在前$i-1$天，也可以发生在第$i$天，因此对应着两种情况，我们取两种情况下的最大值；

$$
dp[i][0] = max(dp[i-1][0], dp[i-1][0]+prices[i])
$$

对于$dp[i][1]$，$[0...i]$之间只有股票买入，买入可以发生在前$[0...i-1]$天，也可以发生在第$i$天，因此也对应两种情况，我们也取两种情况的最大值；

$$
dp[i][1] = max(dp[i-1][1], -prices[i])
$$

**初始状态**

有了转移方程，初始状态比较好定义了。

$$
dp[0][0]=0, dp[0][1]=-prices[0]
$$

**代码实现**

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n <= 0) return 0;
        vector<vector<int>> dp(n, vector<int>(2, 0));
        dp[0][1] = -prices[0];
        for(int i = 1; i < n; i++) {
            dp[i][1] = max(dp[i - 1][1], -prices[i]);
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
        }
        return dp[n-1][0];
    }
};
```



**复杂度分析**

- 时间复杂度：O(n)
- 空间复杂度：O(n)

