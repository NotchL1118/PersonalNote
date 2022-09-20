# 【时间常见API、正则表达式、Lambda】

# 十一、日期与时间

## 11.1 Date

- Date类代表当前所在系统的日期时间信息

### 11.1.1 Date的构造器：

| 名称                   | 说明                                             |
| ---------------------- | ------------------------------------------------ |
| public Date()          | 创建一个Date对象，代表的是系统当前此刻的日期时间 |
| public Date(long time) | 把时间毫秒值转换成Date日期对象                   |

### 11.1.2 Date的常用方法:

| 名称                           | 说明                                            | 返回值 |
| ------------------------------ | ----------------------------------------------- | ------ |
| public long getTime()          | 返回从1970年1月1日 00:00:00走到此刻的总的毫秒数 | 毫秒值 |
| public void setTime(long time) | 设置日期对象的时间为当前时间毫秒值对应的时间    | 无     |

### 11.1.3 示例:

```java
        Date date = new Date();
        System.out.println(date);

        long time = date.getTime();
        System.out.println(time);
```

结果：

![image-20220824151826440](https://pic.lsyfighting.cn/img/image-20220824151826440.png)

## 11.2 SimpleDateFormat

### 11.2.1 意义和作用

- 简单日期格式化对象
- 可以把日期对象(Date)和时间毫秒值(time)格式化成我们需要的字符串形式
- 可以把字符串的时间形式解析成Date日期对象

### 11.2.2 构造器

| 构造器                                    | 说明                                           |
| ----------------------------------------- | ---------------------------------------------- |
| `public SimpleDateFormat(String pattern)` | 创建简单日期格式化对象，并封装格式化的形式信息 |

**时间格式：xxxx-xx-xx xx:xx:xx**

![image-20220824152309936](https://pic.lsyfighting.cn/img/image-20220824152309936.png)

### 11.2.3 格式化方法

| 格式化方法                              | 说明                          | 返回值 |
| --------------------------------------- | ----------------------------- | ------ |
| public final String format(Date date)   | 日期格式化成日期/时间字符串   | 字符串 |
| public final String format(Object time) | 时间毫秒值化成日期/时间字符串 | 字符串 |



### 11.2.4 解析字符串方法

| 解析方法                         | 说明                               | 返回值     |
| -------------------------------- | ---------------------------------- | ---------- |
| public Date parse(String source) | 从给定字符串的开始解析文本生成日期 | Date日期类 |



- 示例：

```java
        Date date = new Date();
        System.out.println(date);

        long time = date.getTime();
        System.out.println(time);

        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        System.out.println(sdf.format(date));
        System.out.println(sdf.format(time));

        Date date1 = sdf.parse("2019-01-01 00:00:00");
        System.out.println(date1);
```

结果：

![image-20220824153519672](https://pic.lsyfighting.cn/img/image-20220824153519672.png)



## 11.3 Calendar

- Calendar代表了系统此刻日期对应的日历对象
- Calendar是一个抽象类，不能直接创建对象

### 11.3.1 创建对象的方法

| 方法名                               | 说明             |
| ------------------------------------ | ---------------- |
| public static Calendar getInstance() | 获取当前日历对象 |

代码：

```java
        Calendar calendar = Calendar.getInstance();
        System.out.println(calendar);
```

返回值：

```java
java.util.GregorianCalendar[time=1661326918340,areFieldsSet=true,areAllFieldsSet=true,lenient=true,zone=sun.util.calendar.ZoneInfo[id="Asia/Shanghai",offset=28800000,dstSavings=0,useDaylight=false,transitions=31,lastRule=null],firstDayOfWeek=1,minimalDaysInFirstWeek=1,ERA=1,YEAR=2022,MONTH=7,WEEK_OF_YEAR=35,WEEK_OF_MONTH=4,DAY_OF_MONTH=24,DAY_OF_YEAR=236,DAY_OF_WEEK=4,DAY_OF_WEEK_IN_MONTH=4,AM_PM=1,HOUR=3,HOUR_OF_DAY=15,MINUTE=41,SECOND=58,MILLISECOND=340,ZONE_OFFSET=28800000,DST_OFFSET=0]
```

可见，会返回非常多的信息

### 11.3.2 常见方法

| 方法名                                | 说明                         | 示例                         |
| ------------------------------------- | ---------------------------- | ---------------------------- |
| public int get(int field)             | 取日期中的某个字段信息       | calendar.get(Calendar.YEAR); |
| public void set(int field,int value)  | 修改日历的某个字段信息       |                              |
| public void add(int field,int amount) | 为某个字段增加、减少指定的值 |                              |
| public final Date getTime()           | 拿到此刻日期对象             |                              |
| public long getTimeInMillis()         | 拿到此刻时间毫秒值           |                              |

**注意：calendar是可变日期对象，一旦修改后，其对象本身表示的时间将发生变化**

# 十二、JDK8新增日期类

- JADK8新增日期类
  - LocalDate：不包含具体时间的日期
  - LocalTime：不包含日期的时间
  - LocalDateTime：包含了日期及时间
  - Instant：代表的是时间戳
  - DateTimeFormatter：用于时间的格式化和解析
  - Duration：用于计算两个“时间”间隔
  - Period：用于计算两个“日期”间隔

- 新的API严格区分了 时刻、本地日期、本地时间，并且对日期和时间进行运算更加方便
- 新的API的类型几乎全是**不变类型**(类似于String)



## 12.1 三个Local~类

**LocalDate、LocalTime、LocalDateTime**

- 分别表示 日期、时间、日期时间 对象
- **三个类的实例是不可变的对象**
- 三者构建对象和API通用

### 12.1.1 构建器

| 方法名                     | 说明                            | 示例                                                         |
| -------------------------- | ------------------------------- | ------------------------------------------------------------ |
| public static XXXX now()   | 静态方法，根据当前时间创建对象  | LocaDate localDate = LocalDate.now();<br/>LocalTime llocalTime = LocalTime.*now*();<br/>LocalDateTime localDateTime = LocalDateTime.*now*(); |
| public static XXXX of(...) | 静态方法，指定日期/时间创建日期 | LocalDate localDate1 = LocalDate.*of*(2099,11,11); <br/>LocalTime localTime1 = LocalTime.*of*(11,11,11);<br/>LocalDateTime localDateTime1 = LocalDateTime.*of*(2020, 10,6,13,23,43); |

### 12.1.2 获取信息的API

| 方法名                          | 说明                              |
| ------------------------------- | --------------------------------- |
| public int getYear()            | 获取年                            |
| public int getMonthValue()      | 获取月份(1-12)                    |
| public int getDayOfMonth()      | 获取月中第几天                    |
| public int getDayofYear()       | 获取年中第几天                    |
| public DayOfWeek getDayOfWeek() | 获取星期几，DayOfWeek是一个枚举类 |

### 12.1.3 三者互相转换API

![image-20220824163754437](https://pic.lsyfighting.cn/img/image-20220824163754437.png)



- LocalDateTime的转换API

| 方法名                         | 说明                    |
| ------------------------------ | ----------------------- |
| public LocalDate toLocalDate() | 转化成一个LocalDate对象 |
| public LocalTime toLocalTime() | 转化成一个LocalTime对象 |

### 12.1.4 修改相关的API

- LocalDateTime综合了LocalDate和LocalTime

里面的方法

- 这些方法返回的是一个新的实例引用，因为三者对象都是不可变的

| 方法名                                             | 说明                                                         |
| -------------------------------------------------- | ------------------------------------------------------------ |
| plusDays、plusWeeks、plusMonths、plusYears         | 向当前LocalDate对象添加几天、几周、几月、几年                |
| minuDays、minusWeeks、minusMonths、minusYears      | 向当前LocalDate对象减去几天、几周、几月、几年                |
| withDayOfMonth、withDayOfYear、withMonth、withYear | 将月份天数、年份天数、月份、年份修改为指定的值并返回新的LocalDate对象 |
| isBefor、isAfter                                   | 比较两个LocalDate                                            |

**注：这里只拿LocalDate举例，其他两个同理**

## 12.2 Instant时间戳

- Instant类由一个静态的工厂方法now()可以返回当前时间戳
- 时间戳包含日期和时间的，与java.util.Date很类似，事实上Instant就是类似JDK8以前的Date
- Instant和Date两个类可以互相转换

示例：

```java
        Instant instant = Instant.now();
        System.out.println("当前时间戳是" + instant);

        Date date = Date.from(instant);
        System.out.println("当前时间是" + date);

        instant = date.toInstant();
        System.out.println("当前时间戳是" + instant);
```

结果：

![image-20220825112609185](https://pic.lsyfighting.cn/img/image-20220825112609185.png)

## 12.3 DateTimeFormatter

- JDK8引入一个全新的日期与时间格式器 DateTimerFormatter
- 正反豆能调用format方法

示例：

```java
        LocalDateTime ldt = LocalDateTime.now();
        System.out.println(ldt);

        DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy-MM-dd hh-mm-ss");
        String ldtStr = ldt.format(dtf);
        System.out.println(ldtStr);

        String ldtStr2 = dtf.format(ldt);
        System.out.println(ldtStr2);
```

结果：

![image-20220825113114056](https://pic.lsyfighting.cn/img/image-20220825113114056.png)

## 12.4 Period

- 用于计算**日期间隔**差异
- 主要是Period类方法getYears()，getMonths()和getDays()来计算，只能精确到年月日
- 用于**LocalDate**之间的比较

示例：

```java
        LocalDate today = LocalDate.now();
        System.out.println(today);
        LocalDate birthday = LocalDate.of(2002,3,10);
        System.out.println(birthday);

        Period period = Period.between(birthday, today);// 两个不能反，小的在前面
        System.out.println(period);
        System.out.println(period.getYears()+"年"+period.getMonths()+"月"+period.getDays()+"日");
```

结果：

![image-20220825115925214](https://pic.lsyfighting.cn/img/image-20220825115925214.png)

## 12.5 Duration

- 用于计算**时间间隔**差异
- 提供了基于时间的值测量时间量的方法
- 用于**LocalDateTime**之间的比较，也可以用于Instance之间的比较

示例：

```java
        LocalDateTime today = LocalDateTime.now();
        System.out.println(today);
        LocalDateTime birthday = LocalDateTime.of(2002,3,10,12,0,0);
        System.out.println(birthday);

        Duration duration = Duration.between(birthday,today);
        System.out.println(duration);
        System.out.println("天数 "+duration.toDays());
        System.out.println("小时数 "+duration.toHours());
        System.out.println("分钟数 "+duration.toMinutes());
        System.out.println("毫秒数 "+duration.toMillis());
        System.out.println("纳秒数 "+duration.toNanos());
```

示例：

![image-20220825120848566](https://pic.lsyfighting.cn/img/image-20220825120848566.png)

## 12.6 ChronoUnit

- 用于在单个时间单位内测量一段时间，这个工具类最全，可以用于比较所有时间单位

示例：

```java
        LocalDateTime today = LocalDateTime.now();
        System.out.println(today);
        LocalDateTime birthDate = LocalDateTime.of(2002,3,10,12,10,30);
        System.out.println(birthDate);
        
        System.out.println("1.相差的年数：" + ChronoUnit.YEARS.between(birthDate, today));
        System.out.println("2.相差的月数：" + ChronoUnit.MONTHS.between(birthDate, today));
        System.out.println("3.相差的周数：" + ChronoUnit.WEEKS.between(birthDate, today));
        System.out.println("4.相差的天数：" + ChronoUnit.DAYS.between(birthDate, today));
        System.out.println("5.相差的时数：" + ChronoUnit.HOURS.between(birthDate, today));
        System.out.println("6.相差的分数：" + ChronoUnit.MINUTES.between(birthDate, today));
        System.out.println("7.相差的秒数：" + ChronoUnit.SECONDS.between(birthDate, today));
        System.out.println("8.相差的毫秒数：" + ChronoUnit.MILLIS.between(birthDate, today));
        System.out.println("9.相差的微秒数：" + ChronoUnit.MICROS.between(birthDate, today));
        System.out.println("10.相差的纳秒数：" + ChronoUnit.NANOS.between(birthDate, today));
        System.out.println("11.相差的半天数：" + ChronoUnit.HALF_DAYS.between(birthDate, today));
        System.out.println("12.相差的十年数：" + ChronoUnit.DECADES.between(birthDate, today));
        System.out.println("13.相差的世纪（百年）数：" + ChronoUnit.CENTURIES.between(birthDate, today));
        System.out.println("14.相差的千年数：" + ChronoUnit.MILLENNIA.between(birthDate, today));
        System.out.println("15.相差的纪元数：" + ChronoUnit.ERAS.between(birthDate, today));
```

结果：

![image-20220825121334311](https://pic.lsyfighting.cn/img/image-20220825121334311.png)



# 十三、包装类

- 包装类就是8种基本数据类型对应的引用类型

| 基本数据类型 | 引用数据类型 |
| ------------ | ------------ |
| byte         | Byte         |
| short        | Short        |
| int          | Integer      |
| long         | Long         |
| char         | Character    |
| float        | Float        |
| double       | Double       |
| boolean      | Boolean      |

- 提供包装类的原因：
  - 为了实现一切皆对象，为8种基本类型提供了对应的引用类型
  - 后面的集合和泛型其实也只能支持包装类型，不支持基本数据类型

## 13.1 自动装箱＆自动拆箱

基本数据类型和包装类可以自动转化

- **自动装箱:** 基本类型的数据和变量可以直接赋值给包装类型的变量
  - (例如: int x = 10; Integer y = x;)

- **自动拆箱:** 包装类型的变量可以直接赋值给基本数据类型的变量
  - (例如: Integer x = 10; int y = x;)

## 13.2 包装类的特有功能

- 包装类的变量默认值是null，容错率更高
- 可以把基本类型的数据转化成字符串类型(用处不大)
  - 调用toString()方法
  - 调用Integer.toString(基本类型的数据)
- 可以把字符串类型的数值转换成真是的数据类型(有用)
  - Integer.parseInt("字符串类型的整数")
  - Double.parseDouble("字符串类型的小数")

# 十四、正则表达式

- 正则表达式可以用一些规定的字符来制定规则，并用来检验数据格式的合法性
- 字符串对象提供了匹配正则表达式的方法
  - public boolean matches(String regex) 判断是否匹配正则表达式，匹配返回true,不匹配返回false

## 14.1 规则集

![image-20220825130332557](https://pic.lsyfighting.cn/img/image-20220825130332557.png)

示例:

手机号检测正则表达式: `"1[3-9]\\d{9}"` (1开头，然后第二位只能是3-9中的数字，然后剩下9位随意数字，两个反斜杠是转义字符)

邮箱格式检测:`"\\w{1,}@\\w{2,10}(\\.\\w{2,10}){1,2})"`( lsy123456@pp.com.cn 英文数字下划线开头加一个@，然后2-10个字符,后面可能会出现.com.cn这种，所以(\\.\\w{2，10})可以出现1或2次)

## 14.2 字符串相关方法

| 方法名                                               | 说明                                                     |
| ---------------------------------------------------- | -------------------------------------------------------- |
| public String replaceAll(String regex,String newStr) | 按正则表达式匹配的内容进行替换                           |
| public String[] split(String regex);                 | 按正则表达式匹配的内容进行分割字符串，返回一个字符串数组 |

## 14.3 爬取信息

例子：

```java
        String rs = "学习Java,电话020-43422424，或者联系邮箱itcast@itcast.cn,电话18762832633，0203232323 邮箱bozai@itcast.cn，400-100-3233 ，4001003232";
        // 需求：从上面的内容中爬取出 电话号码和邮箱。
        // 1.定义爬取规则
         String regex = "(\\w{1,}@\\w{2,10}(\\.\\w{2,10}){1,2})|" +
                 "(1[3-9]\\d{9})|(0\\d{2,5}-?\\d{5,15})|400-?\\d{3,8}-?\\d{3,8}";
         // 2.编译正则表达式成为一个匹配规则对象
        Pattern pattern = Pattern.compile(regex);
        // 3.通过匹配规则对象得到一个匹配数据内容的匹配器对象
        Matcher matcher = pattern.matcher(rs);
        // 4.通过匹配器去内容中爬取出信息
         while(matcher.find()){
         System.out.println(matcher.group());
         }
```

结果：

![image-20220825151438074](https://pic.lsyfighting.cn/img/image-20220825151438074.png)



# 十五、Arrays类

- 数组操作工具类，专门用来操作数组元素

## 15.1 常用API

| 方法名                                                       | 说明                                             |
| ------------------------------------------------------------ | ------------------------------------------------ |
| public static String toString(类型[] a)                      | 返回数字的内容(字符串形式)                       |
| public static void sort(类型[] a)                            | 对数组进行默认升序排序                           |
| public static\<T> void sort(类型[] a,Comparator\<?super T> c) | 使用比较器对象自定义排序                         |
| public static int binarySearch(int[] a,int key)              | 二分搜索数组中的数据，存在返回索引，不存在返回-1 |

## 15.2 自定义排序规则

> 所想在Java Comparator文档中

- 设置Comparrator接口对应的比较器对象，来定制比较规则，会把大的数据往后排
  - 如果认为左边数据 > 右边数据 返回正整数
  - 如果认为左边数据 < 右边数据 返回负整数
  - 如果认为左边数据 = 右边数据 返回0

例子:

```java
        //默认升序
		Integer[] ages = {10,20,30,40,50};
        Arrays.sort(ages, new Comparator<Integer>()
        {
            @Override
            public int compare(Integer o1, Integer o2)
            {
//                if(o1 > o2) return 1;
//                else if(o1 < o2) return -1;
//                return 0;
                return o1-o2; //简写版本，如果想要降序排序，写成 o2 - o1 即可
            }
        });
```

结果:

![image-20220825153933781](https://pic.lsyfighting.cn/img/image-20220825153933781.png)



# 十六、Lambda表达式

- Lambad是JDK8开始后的一种新语法形式,作用是 简化匿名内部类的代码写法
- 简化格式：

```java
(匿名内部类被重写方法的形参列表)->{
	被重写方法的方法体代码;
}
注意：->是语法形式，无实际含义
```

**注意：** Lambda表达式只能简化**函数式接口(@Functionallnterface)**的匿名内部类写法

**函数式接口:** 首先**必须是接口**，其次接口中**有且仅有一个**抽象方法的形式



例子:

```java
		Integer[] ages = {10,20,30,40,50};
        Arrays.sort(ages, new Comparator<Integer>()
        {
            @Override
            public int compare(Integer o1, Integer o2)
            {
                return o2-o1; 
            }
        });
```

​	可以简化为

```java
		Integer[] ages = {10,20,30,40,50};
        Arrays.sort(ages,(o1,o2)->{ //参数类型可以省略不写
            return o2-o1;
        });
        System.out.println(Arrays.toString(ages));
```



## 16.1 再次省略写法

示例代码:

```java
		btn.addActionListener( (ActionEvent e) -> {
    		System.out.println("点击");
		});
```

- **参数类型可以省略不写**

​	可以简化为：

```java
		btn.addActionListener( (e) -> {
    		System.out.println("点击");
		});
```

- **如果只有一个参数，参数类型可以省略，并且()也可以省略**

​	可以简化为：

```
		btn.addActionListener( e -> {
    		System.out.println("点击");
		});
```

- **如果Lambd表达式的方法体代码只有一行代码，可以省略大括号不写，同时省略分号！**

​	上式继续简化为：

```java
		btn.addActionListener( e -> System.out.println("点击") );
```

- **如果Lambda表达式的方法体代码只有一行代码。可以省略大括号不写。如果这行代码是return语句，必须省略return不写，同时也必须省略分号不写**

```java
        Arrays.sort(ages,(o1,o2)->{
            return o2-o1;
        });
```

​	可以简化为：

```java
		Arrays.sort(ages, (o1, o2) -> o2 - o1);
```
