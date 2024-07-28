# 一些特点

- 有自己的标签，如`<View/>, <Text/>`
- 样式必须使用camelCase，额米有className，取而代之的是styleSheet
- 文本必须标明文本节点
- 所有的布局元素都是`flex-box`，一般不用直接声明是`dispalay:flex`
- image必须给定宽高
- flex默认方向变成了column
- 滚动需要`scollView`
- `transform`有特殊的配置方式
- 像素
  - `PixelRatio.getPixelSizeForLayoutSize(200)`
  - `PixelRatio.get() ===> 2.75`
  - RN的数值的计算方式，按照大小/2.75来计算
- 首行缩进上，没有`text-indent`，需要自己用字符实现
- 表单: `e.targetvalue` -> `e.nativeEvent.text`

# 图片像素

比如说手机屏幕一行有375px，375个像素点，那么一张图片20px，需要20个像素点显示。另一个厂商说自己手机更牛逼，一行可以显示750个像素点，那么同一张图片在这个手机上就会缩小一倍。所以大家为了规避这种情况，有了物理像素(比如说手机一行375px，750px)和逻辑像素(比如我们规定350px)。而`devicePixelRatio`就等于物理像素/逻辑像素。

# Think

[1.视频]([React Native Tutorial - 1 - Introduction - YouTube](https://www.youtube.com/watch?v=hzzCveeczSQ&t=11s))

- React itself is a library designed for building user interfaces

> React本身是一个用于构建用户界面的库

- react-dom for web apps and react-native for native mobile apps

> 与react-dom配合构建Web应用，和react-native配合构建原生移动端应用
>
> 这两个库的作用是将虚拟DOM转换为具体平台的实际UI元素：
>
> - `react-dom`用于将虚拟DOM转换为浏览器中的实际DOM元素。
> - `react-native`用于将虚拟DOM转换为移动设备上的原生组件。

