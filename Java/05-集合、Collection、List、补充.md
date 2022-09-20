# 【05-集合概述、Collection、List、泛型深入】

> 对磊老师视频的总结

# 十七、集合

## 17.1 为什么用集合而不是数组

- 数组的特点
  - 数组定义完成并使用后，**类型确定，长度固定**
  - 不适合元素个数和类型不确定、需要增删数据操作的场景
  - 数组功能较单一，处理数据能力不是很强
- 集合特点
  - 集合大小不固定，使用后可以动态变化，类型也可以选择不固定
  - 适合元素个数和类型不确定，且需要增删数据的操作的场景
  - 集合种类丰富，功能强大



## 17.2 集合类体系结构

![image-20220825165216637](https://pic.lsyfighting.cn/img/image-20220825165216637.png)

- Collection单列集合，每个元素(数据)只含有一个值
- Map双列集合，每个元素包含两个值(键值对)



# 十八、Collection系

> Collection只是集合的一种，还有另一种Map，如上图

## 18.1 Collection集合体系

![image-20220825165753641](https://pic.lsyfighting.cn/img/image-20220825165753641.png)

## 18.2 泛型

- 集合都是泛型的形式，可以在编译阶段约束集合只能操作某种数据类型

```java
Collection<String> lists = new ArrayList<String>();
Collection<String> lists = new ArrayList<>(); //JDK 1.7后泛型类型申明可以省略不写
```

- 集合和泛型都只支持引用数据类型，**不支持基本数据类型**，所以集合中存储的元素都被认为是对象

```java
Collection<int> lists = newArrayList<>() 这么写是错误的!
```

- 如果要存储基本类型的数据，使用包装类

```java
Collection<Integer> lists = newArrayList<>() 正确写法✔！
```



## 18.3 Collection常见API

**Collection是单列集合的祖宗接口，它的功能是所有单列集合都可以继承使用的**

| 方法                                | 说明                             |
| ----------------------------------- | -------------------------------- |
| public boolean add(E e)             | 将给定的对象添加到当前集合中     |
| public void clear()                 | 清空集合中所有的元素             |
| public boolean remove(E e)          | 把给定的对象在当前集合中删除     |
| public boolean contains(Object obj) | 判断当前集合中是否包含给定的对象 |
| public boolean isEmpty()            | 判断当前集合是否为空             |
| public int size()                   | 返回集合中元素的个数             |
| public Object[] toArray()           | 把集合中的元素，存储到数组中     |



## 18.4 Collection集合的遍历方式

### 18.4.1 迭代器

迭代器在Java中的代表是**`Interator`**，迭代器是集合的专用遍历方式(指针HHHH😆)

- Collection集合获取迭代器：

| 方法                   | 说明                                                         |
| ---------------------- | ------------------------------------------------------------ |
| Iterator<E> iterator() | 返回集合中的迭代器对象，该迭代器对象默认值想当前集合的0索引，即第一个值 |

- Iterator中的常用方法

| 方法              | 说明                                                         |
| ----------------- | ------------------------------------------------------------ |
| boolean hasNext() | 询问当前位置是否有元素存在，存在返回true ,不存在返回false    |
| E next()          | 获取当前位置的元素，并同时将迭代器对象移向下一个位置，注意防止取出越界。 |

- Collection遍历示例：

```java
        Iterator<String> it = list.iterator();
        while(it.hasNext()){
            String ele = it.next(); //越界会出现NoSuchElementException异常
            ...
        }
```

### 18.4.2 增强for循环

格式:

```java
for(元素数据类型 变量名:数组或者Collection集合)
{
    ...
}
```

示例:

```java
Collection<String> list = new ArrayList<>();
...
for(String ele:list)
{
    ...//可以使用ele表示当前元素，但是不会影响到集合中的元素
}
```

**注意：增强for循环不会影响到集合中的元素**

### 18.4.3 Lambda表达式遍历

Collection结合Lambda遍历的API：

| 方法                                             | 说明               |
| ------------------------------------------------ | ------------------ |
| default void forEach(Consumer<? super T> action) | 结合Lambda遍历集合 |

示例：

```java
Collection<String> lists = new ArrayList<>();
...
lists.forEach(new Consumer<String>() {
    @Override
    public void accept(String s) {
        System.out.println(s); 
    }
});
```

​	简写为:

```java
lists.forEach(s -> {
    System.out.println(s);
});
//list.forEach( s -> System.out.println(s) );
```



## 18.5 集合在程序中的表示

- 集合中存储的都是元素对象的地址

![image-20220825173611674](https://pic.lsyfighting.cn/img/image-20220825173611674.png)



# 十九、数据结构(简单介绍)

> 简单介绍，不展开讨论

- 队列：先进先出，后进后出
- 栈：后进先出，先进后出。
- 数组：内存连续区域，查询快，增删慢。
- 链表：元素是游离的，查询慢，首尾操作极快。
- 二叉树：永远只有一个根节点, 每个结点不超过2个子节点的树。
- 查找二叉树：小的值永远在在左子树，大则在右边，但是可能树很高，查询性能变差。又称二叉排序树或者二叉搜索树
- 平衡查找二叉树：让树的高度差不大于1，增删改查都提高了。
- 红黑树（就是基于红黑规则实现了自平衡的排序二叉树）



# 二十、Collection下的List系列

## 20.1 List系列集合特点

- 有序：存储和取出的元素顺序一致
- 有索引：可以通过索引操作元素
- 可重复：存储的元素可以重复

## 20.2 List的实现类的底层原理

- ArrayList底层是基于数组实现，查询元素快，增删相对慢
- LinkedList底层基于双链表实现，查询元素慢，增删首尾非常快

## 20.3 List集合特有方法

- List集合因为支持索引，所以多了很多索引操作的独特api，Collection的功能也继承了

| 方法名称                      | 说明                                   |
| ----------------------------- | -------------------------------------- |
| void add(int index,E element) | 在此集合的指定位置插入指定的元素       |
| E remove(int index)           | 删除指定索引处的元素，返回被删除的元素 |
| E set(int index,E element)    | 修改指定索引处的元素，返回被修改的元素 |
| E get(int index)              | 返回指定索引处的元素                   |

## 20.4 List集合遍历

1. 迭代器
2. 增强for循环
3. Lambda表达式
4. for循环(因为List集合存在索引)

## 20.5 ArrayList集合底层原理

- ArrayList底层基于数组实现
- 第一次创建集合并添加第一个元素的时候，在底层创建一个默认长度为10的数组

![image-20220902105657575](https://pic.lsyfighting.cn/img/image-20220902105657575.png)

## 20.6 LinkedList的特点和特有功能

- 底层数据结构是双链表，查询慢，首尾操作快

| 方法名称                  | 说明                             |
| ------------------------- | -------------------------------- |
| public void addFirst(E e) | 在列表开头插入指定的元素         |
| public void addLast(E e)  | 将指定的元素插入到列表末尾       |
| public E getFirst()       | 返回此列表中的第一个元素         |
| public E getLast()        | 返回此列表中的最后一个元素       |
| public E removeFirst()    | 从此列表中删除并返回第一个元素   |
| public E removeLast()     | 从此列表中删除并返回最后一个元素 |

​	

## 20.7 并发修改异常

- 存在问题
  - 迭代器遍历集合并且直接用集合删除元素的可能出现
  - 增强for循环遍历集合且直接用集合删除元素的时候可能出现
- 不出问题
  - 迭代器遍历集合用迭代器自己的删除方法
  - 使用for循环遍历并删除元素

# 二十一、泛型深入

## 21.1 泛型的概述和好处

- 概述
  - 泛型是JDK5中引入的特性，可以在编译阶段约束操作的数据类型并检查
  - 泛型格式: <数据类型>; **泛型只支持引用数据类型**
  - 集合体系的全部接口和实现类都是支持泛型使用的
- 好处
  - 统一数据类型
  - 把运行时期的问题提前到了编译期间，避免了强制类型转换可能出现的异常，因为编译阶段类型就能确定下来



泛型可以在很多地方定义

- 类后面 -> 泛型类
- 方法申明上 -> 泛型方法
- 接口后面 -> 泛型接口

## 21.2 泛型类

- 定义类的同时定义了泛型的类就是泛型类

- 泛型类的格式: 修饰符 class 类名 <泛型变量>{}
  - 范例:public class MyArrayList \<T> {}
- 此处泛型变量T可以随便写任意标识，例如 E 、T、K、V等
- 作用：编译阶段指定数据类型，类似于集合的作用
- 原理：把出现泛型变量的地方全部替换成传输的真实数据类型



## 21.3 泛型方法

- 定义方法的同时定义了泛型的方法就是泛型方法

- 泛型类的格式: 修饰符 <泛型变量> 方法返回值 方法名称(形参列表){}

  - 范例:public \<T> void show(T t) {} 

- 作用:方法中可以使用泛型接口一切实际类型的参数，方法更具备通用性



## 21.4 泛型接口

