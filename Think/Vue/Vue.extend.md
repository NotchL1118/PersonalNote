# Vue.extend

> 转自作者：土豆君
> 链接：https://juejin.cn/post/6890072682864476168

## Vue.extend原理解析：

作用：**Vue.extend返回的是一个扩展实例构造器**,也就是预设了部分选项的Vue实例构造器(即VueComponent构造器)，但未曾实例化，可以理解为创建一个子类，然后让它继承Vue身上的一些功能。

```scss
创建一个Vue的子类。

let cid = 1； // 用以进行特殊标记
function extend(extendOptions){
    extendOptions = extendOptions || {}
    // this->vue
    const Super = this
    const SuperId = Super.cid
    // 使用父类的id作为缓存的key
    // 只要父类id相同，每次调用会返回相同的子类

    const cachedCtors = extendOptions._Ctor || (extendOptions._Ctor = {})
    //如果存在缓存,可直接返回。 为了性能考虑，增加缓存策略
    if (cachedCtors[SuperId]) {
      return cachedCtors[SuperId]
    }   
    // 对name命名方式进行校验
    // /^[a-zA-Z][\w-]*/
    const name = extendOptions.name || Super.options.name
    if (process.env.NODE_ENV !== 'production' && name) {
      validateComponentName(name)
    }

    const Sub = function VueComponent (options) {
      // vue._init 此函数的解析会在下面有解析
      this._init(options)
    }
    // 继承父类构造函数
    Sub.prototype = Object.create(Super.prototype)
    Sub.prototype.constructor = Sub
    Sub.cid = cid++
    // 合并父类的options
    Sub.options = mergeOptions(
      Super.options,
      extendOptions
    )
    Sub['super'] = Super

    // For props and computed properties, we define the proxy getters on
    // the Vue instances at extension time, on the extended prototype. This
    // avoids Object.defineProperty calls for each instance created.
    // 初始化props
    // 将props挂载在原型对象的_props属性下
    if (Sub.options.props) {
      initProps(Sub)
    }
    // 初始化computed
    // 将初始化computed挂载在原型对象下
    if (Sub.options.computed) {
      initComputed(Sub)
    }

    // allow further extension/mixin/plugin usage
    // 复制父类的静态方法
    // 子类继承Vue的能力
    Sub.extend = Super.extend
    Sub.mixin = Super.mixin
    Sub.use = Super.use

    // create asset registers, so extended classes
    // can have their private assets too.
    ASSET_TYPES.forEach(function (type) {
      Sub[type] = Super[type]
    })
    // enable recursive self-lookup
    if (name) {
      Sub.options.components[name] = Sub
    }

    // keep a reference to the super options at extension time.
    // later at instantiation we can check if Super's options have
    // been updated.
    Sub.superOptions = Super.options
    Sub.extendOptions = extendOptions
    Sub.sealedOptions = extend({}, Sub.options)
    // cache constructor
    cachedCtors[SuperId] = Sub
    return Sub
  }
复制代码
```

1、为了性能考虑，在Vue.extend方法内增加了缓存策略。反复调用Vue.extend其实应该返回同一个结果。

2、只要返回结果是固定的，就可以将计算结果缓存，再次调用extend方法时，只需要从缓存中取出结果即可。

3、使用父类的id作为缓存的key，将子类缓存在cachedCtors中。

4、对name的校验，如果发现name选项不合格，会在开发环境下发出警告。

5、**最后，创建子类并将它返回，这一步并没有继承的逻辑，此时子类是不能用的，它还不具备Vue的能力。**

6、所以extend返回的都是一个个全新的VueComponent构造函数！所以全局事件总线不能使用VueComponent构造函数来当中间件