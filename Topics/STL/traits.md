# C++ traits技法

> email: ichdream@foxmail.com
> date: 2021-08-25

---

这一讲来谈谈C++ 模版元编程中的traits技法。
STL库使用的都是C++ Template元编程技术，它是C++对范型编程模式的支撑。

我们来先看看这个traits技法，很基础，也很重要，这个概念不理解，后面再深入研究STL库中就会受阻。所以，最好一步到位，将这个技术研究🧐透彻。

## traits技法用来解决什么问题🤔

我们先来看下 C++ 之父的回答：

> Think of a trait as a small object whose main purpose is to carry information used by another object or algorithm to determine “policy” or “implementation details”. - Bjarne Stroustrup

Bjarne Stroustrup将traits看作一个携带其它对象信息的对象，这部分信息用于在具体的策略或者实现上帮助下决定。
traits的具体实现是什么样子的呢？思考下，专门用来存储信息的对象，最好具备专用性，以类的形式实现最好。实际上，C++的操作也是如此。traits总是以```struct```的形式实现，被称之为```traits classes```，它专门用来为使用者提供类型信息。

在研究模版的traits这项技术之前，我们先来打个基础，研究一下相关的技术：模版特化和偏特化。

### 模版特化Template Specialization
我们先来定义一个通用模版
```cpp
template<typename>
struct info_pool 
{
    static const bool value = false;
};
```

针对T是```void```的类型，再定一个特化版本
```cpp
template<>
struct info_pool
{
    static const bool value = true;
};
```

再来写一个测试代码：

```cpp
info_pool<bool> t1;
cont << t1.value << endl; // 输出 0
info_pool<void> t2;
cout << t2.value << endl; // output 1
```

可以看出，当我们声明```info_pool<void> t2;```时，使用的是特化版本的模版。

### 偏特化Patial Specialization

为什么加个“偏”字呢？模版特化时，我们可以指定模版的一部分参数。必须清醒地意识到一个模版的偏特化本身还是一个模版，使用它时使用者必须在特例化版本中为未指定的模版参数提供实参。

我们举一个例子来看👀模版的偏特化：
先看通用版本

我们再来看一个迭代器的例子

```cpp
// 容器
template<typename T>
class List
{
public:
    void insert_front(T value);
    void insert_end(T value);
    void display(ostream& os = cout) const;
private:
    ListItem<T>* _end;
    ListItem<T>* _front;
    long _size;
};
// 容器中元素
template<typename T>
class ListItem
{
public:
    T value() const { return _value; }
    ListItem* next() const { return _next; }
private:
    T _value;
    ListItem* _next;
};

// 迭代器
template<class Item>
struct ListIter
{
    Item* ptr;

    ListIter(Item* p = 0): ptr(p) {}
    Item& operator*() const { return *ptr; }
    Item* operator->() const { return ptr; }

    ListIter& operator++()
    { ptr = ptr->next; return *this; }
    ListIter operator++(int)
    { ListIter tmp = *this; ++*this; return tmp; }

    bool operator==(const ListIter& i) const
    { return ptr == i.ptr; }
    bool operator!=(const ListIter& i) const
    { return ptr != i.ptr; }
};
```

```List```是容器，其内部的元素是```ListItem```类型，我们用```ListIter```来访问```List```中的元素。
可以看出```ListIter```是单向移动的，只能往前移动，没有办法回退。
另外，我们还重载了操作符```*```和```->```

### 迭代器相应型别

试想一下，如果算法中要声明一个变量，以“迭代器所指的对象的类型”为类型，怎么设计才能实现？
一种解决方法：通过function template的参数推到机制。
比如：

```cpp
template<class I, class T>
void func_impl(I iter, T t)
{
    T tmp;      // 这里解决了我们的问题。T就是迭代器所指的对象的类型
    // ... 这里做原本func() 应该做的工作
}

template<class T>
inline void func(I iter)
{
    func_impl(iter, *iter);
}

int main()
{
    int i;
    func(&i);
    return 0;
}
```

我们来分析下上面这个例子，func其实是对func_impl的一层wrapper，我们在func中给func_impl的第二个参数T传递的是I所指的对象，编译器自动根据我们传递对象推导出T的类型。
而我们在main中传递给func的是i本身，并非i的copy。

所以，我们在func_impl中的确通过编译器在编译期推倒出了类型T。
缺点是什么呢？
T只是迭代器众多类型中的一种，最常用的有5种。并非任何情况下，都可以通过函数参数推到机制来获取。

所以，traits来帮忙。

我们将迭代器所指对象的类型，统一称作为迭代器的value_type。
上面例子中虽然可以推到出value_type，但它并非具有普遍意义，即适用于所有的场景。例如，如果函数返回值的value_type的推导，上面的方法就不行🙅。因为，函数模版的参数推导机制只能适用于参数，不能用于推导函数的返回值。

那么，还有什么方法呢🤔？
声明一种内嵌类型呢？
试试看。

```cpp
template<class T>
struct MyIter
{
    typedef T value_type;
    T* ptr;
    MyIter(T* p = 0): ptr(p) {}
    T& operator*() const { return *ptr; }
    // ...
};

template<class T>
typename I::value_type
func(I ite)
{ 
    return *ite; 
}

MyIter<int> ite(new int(8));
cout << func(ite) << endl;  // output: 8
```

```MyIter<int> ite(new int(8));```这一行代码中，我们先创建了一个类型位int的匿名对象，将它作为参数传递给了```MyIter```的初始化构造函数。
此时，在```MyIter```对象内部，```value_type```是```int```类型，所以func的返回值通过```template<class T> typename I::value_type```确定为```int```，
当然，这是在编译期计算的。


我们需要知道模版的通用版本和特化版本的关系和区别：

```cpp
template<typename T>
class C{...};	//这个泛华版本允许T为任何型别
 
template<typename T>	
class C<T*>{...};	//这个偏特化版本只适用于"T为原声指针"情况
```

所以，我们还需要位迭代器template的参数是原生指针设计特化的版本。
我们可以设计如下的class template专门萃取迭代器的特性，而value_type只是迭代器的其中一个特性。

```cpp
template<class T>
struct iterator_traits
{
    typedef typename I::value_type value_type;
};
```

设计相应的特化版本：

```cpp
template<class T>
struct iterator_traits<T*>
{
    typedef typename T value_type;
};

template<class T>
struct iterator_traits<const T*>
{
    typedef typename T value_type;
};
```

大功告成了，现在我们的类型萃取器```iterator_traits```不论迭代器是何种类型，即便是原生指针这种类型，都可以正确地萃取出其vaoue_type.

