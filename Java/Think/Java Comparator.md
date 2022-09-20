# Java Comparator

> 可能不对，因为还没看到太底层的代码，只是方便自己记忆

学习Arrays类时不明白为什么这么写是对的

```java
        //降序排序
		Integer[] ages = {10,20,30,40,50};
        Arrays.sort(ages, new Comparator<Integer>()
        {
            @Override
            public int compare(Integer o1, Integer o2)
            {
//                if(o1 < o2) return 1;
//                else if(o2 > o1) return -1;
//                return 0;
                return o2-o1; //简写版本，如果想要升序排序，写成 o1 - o2 即可
            }
        });
```

**sort默认是升序排序**，也就是会将"大"的数排到后面(这个大不是数值大，而是比重)。而我们重写的compare类，官方文档是这么说的

```java
int compare(T o1,T o2)
Compares its two arguments for order. Returns a negative integer, zero, or a positive integer as the first argument is less than, equal to, or greater than the second.
根据顺序比较两个参数，当第一个参数小于第二个参数时返回负数，等于第二参数时返回0，大与第二参数时返回正数
```

可见，**这个方法主体是第一个参数o1**，第二个数只是用来比较的

- 当o1 < o2时候，o1是数值上的较小数，但我们返回的是正数，相当于告诉程序，两者中o1是比重"大"的那个数，然后程序将"大"的数排到后面，这样数值小的数会就会到后面去了，就完成了降序排序