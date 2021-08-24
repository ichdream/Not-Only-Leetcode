## 排序算法

### 概述

为什么排序如此重要？
因为很多场景都需要对数据进行排序的需求。数据经过排序之后，我们可以从中找出规律，方便分析。

那么，常用的排序算法有哪些？试着想想：
- 快速排序
- 冒泡排序
- 选择排序
- 归并排序
- 插入排序
- 希尔排序
- 堆排序

我们最常接触到的排序算法是什么？think a while...
嗯，那就是glibc库中的sort排序了。

有没有认真想过sort具体是哪一种排序算法，它很可能是快速排序，因为快排性能很棒。然而，这是真实的情况吗？

我们认真研究下STL源码sort的原型，来一探究竟。

 ```cpp
   /**
   *  @brief Sort the elements of a sequence using a predicate for comparison.
   *  @ingroup sorting_algorithms
   *  @param  __first   An iterator.
   *  @param  __last    Another iterator.
   *  @param  __comp    A comparison functor.
   *  @return  Nothing.
   *
   *  Sorts the elements in the range @p [__first,__last) in ascending order,
   *  such that @p __comp(*(i+1),*i) is false for every iterator @e i in the
   *  range @p [__first,__last-1).
   *
   *  The relative ordering of equivalent elements is not preserved, use
   *  @p stable_sort() if this is needed.
  */
  template<typename _RandomAccessIterator, typename _Compare>
    inline void
    sort(_RandomAccessIterator __first, _RandomAccessIterator __last,
	 _Compare __comp)
    {
      // concept requirements
      __glibcxx_function_requires(_Mutable_RandomAccessIteratorConcept<
	    _RandomAccessIterator>)
      __glibcxx_function_requires(_BinaryPredicateConcept<_Compare,
	    typename iterator_traits<_RandomAccessIterator>::value_type,
	    typename iterator_traits<_RandomAccessIterator>::value_type>)
      __glibcxx_requires_valid_range(__first, __last);
      __glibcxx_requires_irreflexive_pred(__first, __last, __comp);

      std::__sort(__first, __last, __gnu_cxx::__ops::__iter_comp_iter(__comp));
    }
 ```
sort其实是最外一层wrapper，里面调用的是__sort函数，我们再看

```cpp
    // sort

  template<typename _RandomAccessIterator, typename _Compare>
    inline void
    __sort(_RandomAccessIterator __first, _RandomAccessIterator __last,
	   _Compare __comp)
    {
      if (__first != __last)
	{
	  std::__introsort_loop(__first, __last,
				std::__lg(__last - __first) * 2,
				__comp);
	  std::__final_insertion_sort(__first, __last, __comp);
	}
    }
```
__sort函数也是一层wrapper，内部先后顺序调用了__introsort_loop和__final_insertion_sort这两个函数。

__introsort_loop
```cpp
  /// This is a helper function for the sort routine.
  template<typename _RandomAccessIterator, typename _Size, typename _Compare>
    void
    __introsort_loop(_RandomAccessIterator __first,
		     _RandomAccessIterator __last,
		     _Size __depth_limit, _Compare __comp)
    {
      while (__last - __first > int(_S_threshold))
	{
	  if (__depth_limit == 0)
	    {
	      std::__partial_sort(__first, __last, __last, __comp);
	      return;
	    }
	  --__depth_limit;
	  _RandomAccessIterator __cut =
	    std::__unguarded_partition_pivot(__first, __last, __comp);
	  std::__introsort_loop(__cut, __last, __depth_limit, __comp);
	  __last = __cut;
	}
    }
```
__introsort_loop内部其实又调用了__partial_sort
我们再看其内部的两个helper function
```cpp
  /// This is a helper function...
  template<typename _RandomAccessIterator, typename _Compare>
    inline _RandomAccessIterator
    __unguarded_partition_pivot(_RandomAccessIterator __first,
				_RandomAccessIterator __last, _Compare __comp)
    {
      _RandomAccessIterator __mid = __first + (__last - __first) / 2;
      std::__move_median_to_first(__first, __first + 1, __mid, __last - 1,
				  __comp);
      return std::__unguarded_partition(__first + 1, __last, __first, __comp);
    }

  template<typename _RandomAccessIterator, typename _Compare>
    inline void
    __partial_sort(_RandomAccessIterator __first,
		   _RandomAccessIterator __middle,
		   _RandomAccessIterator __last,
		   _Compare __comp)
    {
      std::__heap_select(__first, __middle, __last, __comp);
      std::__sort_heap(__first, __middle, __comp);
    }
```



__final_insertion_sort 是一个插入排序，我们看其源码实现。它内部主要包含两个函数：
- __insertion_sort 很明显这是个插入排序的实现
- _unguarded_insertion_sort 这个是什么作用呢？

```cpp
  /// This is a helper function for the sort routine.
  template<typename _RandomAccessIterator, typename _Compare>
    void
    __final_insertion_sort(_RandomAccessIterator __first,
			   _RandomAccessIterator __last, _Compare __comp)
    {
      if (__last - __first > int(_S_threshold))
	{
	  std::__insertion_sort(__first, __first + int(_S_threshold), __comp);
	  std::__unguarded_insertion_sort(__first + int(_S_threshold), __last,
					  __comp);
	}
      else
	std::__insertion_sort(__first, __last, __comp);
    }
```

__insertion_sort
```cpp
  /// This is a helper function for the sort routine.
  template<typename _RandomAccessIterator, typename _Compare>
    void
    __insertion_sort(_RandomAccessIterator __first,
		     _RandomAccessIterator __last, _Compare __comp)
    {
      if (__first == __last) return;

      for (_RandomAccessIterator __i = __first + 1; __i != __last; ++__i)
	{
	  if (__comp(__i, __first))
	    {
	      typename iterator_traits<_RandomAccessIterator>::value_type
		__val = _GLIBCXX_MOVE(*__i);
	      _GLIBCXX_MOVE_BACKWARD3(__first, __i, __i + 1);
	      *__first = _GLIBCXX_MOVE(__val);
	    }
	  else
	    std::__unguarded_linear_insert(__i,
				__gnu_cxx::__ops::__val_comp_iter(__comp));
	}
    }
```


_unguarded_insertion_sort, 它内部又调用了_unguarded_linear_insert这个函数，好，快到顶峰了，继续。
```cpp
  /// This is a helper function for the sort routine.
  template<typename _RandomAccessIterator, typename _Compare>
    inline void
    __unguarded_insertion_sort(_RandomAccessIterator __first,
			       _RandomAccessIterator __last, _Compare __comp)
    {
      for (_RandomAccessIterator __i = __first; __i != __last; ++__i)
	std::__unguarded_linear_insert(__i,
				__gnu_cxx::__ops::__val_comp_iter(__comp));
    }
```


_unguarded_linear_insert
```cpp
  /// This is a helper function for the sort routine.
  template<typename _RandomAccessIterator, typename _Compare>
    void
    __unguarded_linear_insert(_RandomAccessIterator __last,
			      _Compare __comp)
    {
      typename iterator_traits<_RandomAccessIterator>::value_type
	__val = _GLIBCXX_MOVE(*__last);
      _RandomAccessIterator __next = __last;
      --__next;
      while (__comp(__val, __next))
	{
	  *__last = _GLIBCXX_MOVE(*__next);
	  __last = __next;
	  --__next;
	}
      *__last = _GLIBCXX_MOVE(__val);
    }
```

直至此处，层层嵌套调用结束。
看来，我们得先从最内部的函数__unguarded_linear_insert入手，然后层层往外扩展，才能吃透全部。

_unguarded_linear_insert到底做了什么事情呢？从名称来看，它似乎做得是某种线形的插入排序。
其中： 
- _GLIBCXX_MOVE的定义，它是移动语义，只有在g++版本2014以上才支持，低于这个版本还是原来的复制
  ```cpp 
  #define _GLIBCXX_MOVE(__val) std::move(__val) 
  ```

因此，我们看到sort并不是一个单纯的快速排序，而是快速排序和插入排序的混合体。
当容器中元素个数超过阈值的部分采用快速排序，对于阈值以下的部分则采用插入排序。

为什么这样设计？
这是结合两个排序算法的优缺点来的，当容器中元素接近几乎有序的时候，快速排序的性能会下降，而插入排序倒变得很适合。因此，两个排序算法相互补充。

---


### 分类

按照是否使用内存来分类，可划分为：

- 内排序
- 外排序

按照排序过程中是否需要元素间比较：

- 基于元素间比较的排序：

- 不需要元素间比较排序：



#### 快速排序

- 选择一个pivot，将数组中所有小于pivot所指值的元素都放置到pivot的左边，将所有大于pivot所指值的右边。

- 对pivot左边的子数组重复上述操作，知道数组中元素个数为1

- 对pivot右边的子数组重复上述操作，直到数组中元素个数为1

快速排序对数据的分布比较敏感，由于采用分治思想，每次通过pivot将数据分为两份，对于如果把pivot左右两边分别看成一个整体，用pivotL和pivotR表示，那么pivotL, pivot, pivotR三项可以看成是排好序列的。接下来的步骤只需要分别对pivotL和pivotR分别进行同样的操作即可，直到pivotL和pivotR只有一个元素为止。

所以，需要多少次拆分影响整体的时间效率，如果数据均衡分布，可以发现拆分次数接近log(n), n为原始数组中元素个数。如果原始数据基本有序，可以发现拆分次数接近n。

所以，为了提升算法的效率，应该在每次通过pivot拆分数据时，应使得拆分后两部分数据量尽可能想等。那么，有哪些因素影响这个呢？

- Pivot的值

  这个比较容易想到，但每次在选pivot前，我们并不知道怎么选择pivot才能使得拆分后，两部分的数据量接近。根据数学性质，中位数可以，但获取一个数组中的中位数，复杂度是O(n)，除非这个数组已经排好序，复杂度太高，这个思路不行🙅‍♂️。随机选择一个pivot的做法被实践证明效率还不错，比较具有可行性。另外一个做法是，随机选择三个值，取三个值中的中位数，这个是抽样近似的方法。

- 等于Pivot的元素怎么划分

  真实的环境中，这个很常见，按照上面优化的思路，应该是将等于pivot的元素均匀的分给左右两部分。

 注意事项⚠️：

