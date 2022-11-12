# [Flex布局]

- Flex布局/弹性布局
  - 是一种浏览器提倡的布局模型
  - 布局网页更加简单、灵活
  - 避免浮动脱标的问题
- 作用：
  - 基于Flex精确灵活控制块级盒子的布局方式，避免浮动布局中脱离文档流现象产生
  - Flex布局非常适合结构化布局
- 设置方式：
  - **父元素**添加`display:flex`，子元素可以自动的挤压或拉伸

- 组成部分：
  - 弹性容器
  - 弹性盒子
  - 主轴
  - 侧轴/交叉轴

![image-20220901155127922](https://pic.lsyfighting.cn/img/image-20220901155127922.png)

# 一、主轴对齐方式justify-content

在Flex布局中，调节主轴或侧轴的对齐方式来设置盒子之间的间距

- 主轴对齐方式属性: justify-content

| 属性值        | 作用                                               |
| ------------- | -------------------------------------------------- |
| flex-start    | 默认值，起点开始依次排列                           |
| flex-end      | 终点开始依次排列                                   |
| center        | 沿主轴居中排列                                     |
| space-around  | 弹性盒子沿主轴均匀排列，空白间距均分在弹性盒子两侧 |
| space-between | 弹性盒子沿主轴均匀排列，空白间距均分在相邻盒子之间 |
| space-evenly  | 弹性盒子沿主轴均匀排列，弹性盒子和容器之间间距相等 |

## 1.1 均匀对齐，两边靠边space-between

```css
.box {
	display: flex;
	justify-content: space-between;
	/* 这里省略原有其它属性，下面例子同 */
}
```

![image-20210907212244548](https://pic.lsyfighting.cn/img/image-20210907212244548.png)

## 1.2 末端对齐flex-end

```css
.box {
	display: flex;
	justify-content: flex-end;
}
```

![image-20210907212325001](https://pic.lsyfighting.cn/img/image-20210907212325001.png)

## 1.3 行均匀分配space-around

```css
.box {
	display: flex;
	justify-content: space-around;
}
```

![image-20210907212354499](https://pic.lsyfighting.cn/img/image-20210907212354499.png)

## 1.4 全部间距相同的行均匀分配space-evenly

```css
.box {
	display: flex;
	justify-content: space-evenly;
}
```

![image-20210907212432435](https://pic.lsyfighting.cn/img/image-20210907212432435.png)

## 1.5 水平居中center

```css
.box {
	display: flex;
	justify-content: center;
}
```

![image-20210907212459425](https://pic.lsyfighting.cn/img/image-20210907212459425.png)



# 二、侧轴对齐方式align-items

- 修改侧轴对齐方式属性：
  - align-items(添加到弹性容器)
  - align-self：控制某个弹性盒子在侧轴的对齐方式(添加到弹性盒子)

| 属性值     | 作用                                     |
| ---------- | ---------------------------------------- |
| flex-start | 默认值，起点开始依次排列                 |
| flex-end   | 重点开始依次排列                         |
| center     | 沿侧轴居中排列                           |
| stretch    | 默认值，弹性盒子沿着主轴被拉伸至铺满容器 |

## 2.1 起始排列

```css
.box {
	display: flex;
	justify-content: center;
	align-items: flex-start;
}
```

![image-20210907212545682](https://pic.lsyfighting.cn/img/image-20210907212545682.png)

## 2.2 末端排列

```css
.box {
	display: flex;
	justify-content: center;
	align-items: flex-end;
}
```

![image-20210907212637913](https://pic.lsyfighting.cn/img/image-20210907212637913.png)

## 2.3 垂直居中

```css
.box {
	display: flex;
	justify-content: center;
	align-items: center;
}
```

![image-20210907212709776](https://pic.lsyfighting.cn/img/image-20210907212709776.png)

## 2.4 与子元素第一行文字对齐

```css
.box {
	display: flex;
	justify-content: center;
	align-items: baseline;
}
```

![image-20210907212742633](https://pic.lsyfighting.cn/img/image-20210907212742633.png)

# 三、伸缩比

- 属性：
  - flex：值
- 取值分类
  - 数值(整数)
- 例子：
  - 默认填充剩余空间：`flex:1`

注意：只占用父盒子剩余尺寸



# 四、弹性盒子换行

默认情况下若一行元素太多是不会换行的，我们在上诉例子中多加几个子元素试试：

![image-20210907212810401](https://pic.lsyfighting.cn/img/image-20210907212810401.png)

元素会被挤压，宽度会减小，但是字可能就会换行，导致不合适的效果。

可以设定父元素的`flex-wrap`属性设定换行方式，其值：

- `nowrap` 不换行
- `wrap` 换行，第一行在上面
- `wrap-reverse` 换行，第一行在下面

设定上述父元素为换行：

```css
.box {
	display: flex;
	justify-content: center;
	flex-wrap: wrap;
}
```

![image-20210907212924897](https://pic.lsyfighting.cn/img/image-20210907212924897.png)

- 调整行对齐方式：align-content
  - 取值与justify-content基本相同



# 五、主轴方向

- 主轴默认是水平方向，侧轴默认是垂直方向
- 修改主轴方向属性：flex-direction

| 属性值         | 作用             |
| -------------- | ---------------- |
| row            | 行，水平(默认值) |
| column         | 列，垂直         |
| row-reverse    | 行，从右向左     |
| column-reverse | 列，从下向上     |

