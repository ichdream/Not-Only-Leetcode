# 专题研究


## C++ STL源码剖析

### 1 萃取器traits的研究

我们用萃取器来获取容器中元素的类型，为什么？
因为，容器是模版范型的，在实例化之前，我们是没有办法知道其内部元素倒地是什么类型的？
但是呢，我们还是要对范型的容器设计相应的算法来操作容器内的元素，那么这时候，我们就需要知道元素的类型。即算法内操作元素的类型要和容器类的类型保持一致，怎么才能做到呢？
就是通过萃取技术，在STL库中被广泛用到的技术，是范型编程的基石。
详细的介绍可以看右面的👉的链接：[萃取器traits的研究](./STL/traits.md)

- 股票系列问题
- 字符串系列
- 排序
- 栈
- 树
- 数组
- 堆
- BFS & DFS
- 