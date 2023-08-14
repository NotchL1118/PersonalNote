# 1.Vue2和Vue3的区别

> 被面试问到了太多次了
>
> [链接](https://juejin.cn/post/7204844328111308855#heading-1)

1. **数据双向绑定原理变化(`proxy`替代`defineProperty`)**

因为`defineProperty`无法监听对象或者数组新增、删除的元素，Vue2是对数组常用方法`push、pop、shift、unshift、splice、sort、reverse`进行hack处理，提供`Vue.set`来新增属性。

Vue3使用Proxy，Proxy是ES6的新特性，通过第二个参数handler拦截目标对象的行为，提供更强的响应式能力。还支持了`Map、Set、WeakMap、WeakSet`

2. **生命周期函数的更改**

生命周期整体上大部分是周期钩子上+“on”，功能上不变；

且Vue3组合式API中使用生命周期钩子需要事先引入，而Vue2可以直接使用

| Vue2           | Vue3(组合式)    |
| -------------- | --------------- |
| beforeCreate   | setup           |
| created        | setup           |
| beforeMount    | onBeforeMount   |
| mounted        | onMounted       |
| beforeUpdate   | onBeforeUpdate  |
| updated        | onUpdated       |
| breforeDestroy | onBeforeUnmount |
| destroyed      | onUnmounted     |
| activated      | onActivated     |
| deactived      | onDeactived     |
| errorCaptured  | onErrorCaptured |

3. **多根节点**

在vue2中只能使用一个根节点，而Vue3支持多个根节点，也就是fragment

4. Composition API 组合式API

Vue2是选项式API，一个逻辑会散落在文件不同位置(data、props、computed、watch、生命周期钩子)，可读性差

Vue3是组合式API解决了这个问题，可以将同一逻辑内容写到一处，增强可读性。

5. **异步组件(Suspense)**

Vue3 提供 Suspense 组件，允许程序在等待异步组件加载完成前渲染兜底的内容，如 loading ，使用户的体验更平滑。使用它，需在模板中声明，并包括两个命名插槽：default 和 fallback。Suspense 确保加载完异步内容时显示默认插槽，并将 fallback 插槽用作加载状态。

```javascript
<tempalte>
  <suspense>
    <template #default>
      <List />
    </template>
    <template #fallback>
      <div>
        Loading...      
     </div>
    </template>
  </suspense>
</template>
```

在 List 组件（有可能是异步组件，也有可能是组件内部处理逻辑或查找操作过多导致加载过慢等）未加载完成前，显示 Loading...（即 fallback 插槽内容），加载完成时显示自身（即 default 插槽内容）。

6. **Teleport**

Vue3提供了Teleport组件可将部分DOM移动到Vue app之外的位置，比如项目中常见的Dialog弹窗

```vue
<button @click=dialogVisible = true">显示弹窗</button>
<teleport to="body">
   <div v-if="dialogVisible">
	弹窗，移动到body标签下
   </div>
</teleport>
```

7. **虚拟DOM**

Vue3在虚拟DOM上增加了`patchFlag`字段类型

8. **Diff算法优化**

patchFlag 帮助 diff 时区分静态节点，以及不同类型的动态节点。一定程度地减少节点本身及其属性的比对。

9. **TS支持**

Vue3由TypeScript重写，相对比Vue2对TS有了更好的支持

10. **打包优化**

11. **传值更改**

- vue2 父传子，直接props，子传父，采用Emitting Events，this.$emit(‘事件’,参数)
- vue3 父传子，直接props，子传父，采用Emitting Events，但需要从Vue之中解构出defineEmits，再defineEmits(['事件名称‘])

## 个人总结

API方面

- composition api 组合式API
- 以及setup语法糖
- Fragment节点，多根节点
- Teleport传送门组件，还有异步组件
- 自定义渲染器
- SFC状态驱动CSS，可以在css中使用v-bind

框架方面

- 性能更快
  - 使用Proxy重写响应式机制，推出ref和reactive
  - 编译器优化：在虚拟DOM里塞入`patchFlag`来加快patch性能
- 更小：vue3将各个模块拆分，利于插件的开发，也利于tree-shaking，没使用到的模块不进行打包
- Vue整个用TS重写，对TS的支持性更好

使用方面

- 删除了一些api，比如`$children，$on`之类的
- 使用Emit触发事件需要用`defineEmits`函数
- 声明周期钩子函数名称更改，beforeCreated和created被setup取代，其他的前面都加了on，destory钩子改名为unmounted，更加形象化。

# 2.虚拟DOM

Vue是数据驱动的框架，数据发生变化，会全量更新一次。Vue也是一个声明式的框架，声明式框架的更新性能消耗 = 找出差异的性能消耗 + 直接修改的性能消耗，虚拟DOM的意义就是使得找出差异的性能消耗最小。采用虚拟DOM的更新技术**理论上**不可能比原生JS操作DOM性能更高。(但仅仅是理论上，因为项目一旦大起来，一直写出高效的原生JS代码太耗时了)但是经过可维护性和开发效率方面的考虑，虚拟DOM是一个很不错的选择。通过DIFF算法可以找出需要修改的节点再进行更新，尽可能避免多余的DOM操作，规范优化了操作DOM的方式。

第二点就是虚拟DOM可以方便跨平台应用，因为虚拟DOM就是个描述真实节点的JS对象，各个平台都能认识，再根据平台不同的渲染函数渲染成不同的真实节点。

第三点就是，Vue3是各个模块组件的有机整体，比如渲染器和编译器，虚拟DOM可以成为两个模块之间信息交流的媒介，通过往虚拟DOM里放一些属性字段来提高模块的执行效率(如果要问例子，比如一个元素标签只有class是动态的，就可以在编译阶段给虚拟DOM添加一个字段，然后渲染器就知道了，就可以省去查找变化点的计算量，提高性能)。

Vue的虚拟DOM一般包含三个子项

- tag属性，标签项，也可以是一个组件，函数或者对象
- props：标签上的属性和方法
- children：子节点或者标签的内容，如果是文本节点就是字符串，如果是数组就是有子节点

像在Vue里面写的template最后被编译器编译成render函数，或者手写的render函数，最后返回的就是虚拟DOM，最后会被渲染器patch成真实DOM

# 3.DIFF算法

Vue是一个声明式的框架，声明式框架的更新性能消耗 = 找出差异的性能消耗 + 直接修改的性能消耗；DIFF算法的出现就是为了配合虚拟DOM使得找出差异的性能消耗降到最低。

最初Vue1.X版本时候，每个属性都有一个对应的Watcher实例，可以做到精确更新，没必要使用DIFF算法，但是这样没法承载较大的应用。Vue2之后就降低颗粒化程度，一个组件只有一个Watcher实例，这时候就需要DIFF算法了，配合DOM操作精确的找到需要变化的节点然后精确更新，减少DOM操作次数。

DIFF算法是一个深度优先，同层比较的算法。

- 首先判断两个节点是否为相同同类节点，不同则删除重新创建

- 如果双方都是文本则更新文本内容

- 如果双方都是元素节点则递归更新子元素，同时更新元素属性

- 更新子节点时又分了几种情况：

  - 新的子节点是文本，老的子节点是数组则清空，并设置文本；
  - 新的子节点是文本，老的子节点是文本则直接更新文本；
  - 新的子节点是数组，老的子节点是文本则清空文本，并创建新子节点数组中的子元素；
  - 新的子节点是数组，老的子节点也是数组，那么比较两组子节点，更新细节如下

  vue2用的是双端对比算法。通过比较两组子节点的四端来进行对比，找到可以复用的节点。第一步是对比两个首部，第二步是两个尾部，第三步是旧节点组的首部和新节点组的尾部，第四步是旧节点组的尾部和新节点组的首部。再增加两个额外的逻辑处理一下新增和删除的场景。

  vue3采用的是快速DIFF算法。

# 4.响应式

数据响应式是检测数据变化并作出响应的一种机制。在Vue中需要解决的一个问题就是实现数据变化驱动视图变化，为了做到这点就需要对数据进行响应式处理。之后配合虚拟DOM和diff算法，就可以只关心数据而不用命令式的操作DOM，提高开发效率。

Vue2里响应式系统主要的核心策略就是数据拦截+观察者模式。数据拦截让我们知道数据什么时候发生变化，观察者模式实现发生变化之后执行一系列副作用函数。数据拦截使用`Object.defineProperty`方法，重写get方法来收集依赖，重写set方法触发依赖。观察者模式主要依靠三个类，Dep类和Wachter类，还有一个Observer类把这两个类串联起来。用Observer类使用`defineProperty`递归实现data的数据劫持，为每一个响应式对象都创建一个Dep实例闭包，然后在编译模板的时候创建Watcher实例，并把`Dep.target`设为当前实例，然后在首次渲染的时候触发每一个数据的getter来进行依赖收集。之后数据数据变化触发setter，就会调用Dep实例的notify方法通知Watcher实例更新DOM，但是实际使用起来也有问题，初始化递归操作造成性能损失，也无法新增和删除属性。vue2的数组也需要用API方法来进行数据添加和删除，vue2文档里也写了可以做到不用这种方法，但是性能方面就得不偿失。然后也不支持Set，Map这种新的数据结构。

Vue3核心原理和vue2差不多，也是数据劫持+依赖收集和依赖更新，不过Vue3用的是Proxy实现对整个对象的代理。响应式的核心操作是Proxy+Reflect继续数据劫持，用track函数依赖收集，用trigger函数进行依赖触发。

Vue3使用了Proxy来进行整个对象的代理，没有办法像vue2那样创建闭包来保存属性对应的Dep实例，就用了一个全局的`targetMap`依赖管理器来进行所有的依赖管理。这样做还有个好处就是Proxy类似于懒加载，不需要的数据就不添加依赖了。只有副作用函数用到的数据才进行依赖收集。之后数据变化的时候触发setter，就从targetMap全局依赖管理器里一层一层的找到依赖(首先是根据对象找到DepsMap，然后再根据属性找到对应的依赖集合，也就是一个Set集合)。

我觉得Vue3的这种机制是目前比较好的一种解决方式，缺点就是向下的兼容，Proxy是ES6才新增的属性。

(track函数收集依赖的方式和vue2差不多，会有一个全局的activeEffect属性来记录当前的副作用函数，然后从targetMap里面找到依赖集合，然后添加。)

# 5.computed和watch的区别

**对于Computed：**

- 它支持缓存，只有依赖的数据发生了变化，才会重新计算
- 不支持异步，当Computed中有异步操作时，无法监听数据的变化
- computed的值会默认走缓存，计算属性是基于它们的响应式依赖进行缓存的，也就是基于data声明过，或者父组件传递过来的props中的数据进行计算的。
- 如果一个属性是由其他属性计算而来的，这个属性依赖其他的属性，一般会使用computed
- 如果computed属性的属性值是函数，那么默认使用get方法，函数的返回值就是属性的属性值；在computed中，属性有一个get方法和一个set方法，当数据发生变化时，会调用set方法。

**对于Watch：**

- 它不支持缓存，数据变化时，它就会触发相应的操作
- 支持异步监听
- 监听的函数接收两个参数，第一个参数是最新的值，第二个是变化之前的值
- 当一个属性发生变化时，就需要执行相应的操作
- 监听数据必须是data中声明的或者父组件传递过来的props中的数据，当发生变化时，会触发其他操作，函数有两个的参数：
  - immediate：组件加载立即触发回调函数
  - deep：深度监听，发现数据内部的变化，在复杂数据类型中使用，例如数组中的对象发生变化。需要注意的是，deep无法监听到数组和对象内部的变化。

当想要执行异步或者昂贵的操作以响应不断的变化时，就需要使用watch。

**总结：**

- computed 计算属性 : 依赖其它属性值，并且 computed 的值有缓存，只有它依赖的属性值发生改变，下一次获取 computed 的值时才会重新计算 computed 的值。
- watch 侦听器 : 更多的是**观察**的作用，**无缓存性**，类似于某些数据的监听回调，每当监听的数据变化时都会执行回调进行后续操作。

## 5.1个人小总结

computed是计算属性，他的值依赖于其他的值，可以传入一个必须返回参数的函数或者一个对象设置getter和setter，不支持异步操作。且内部有一个_dirty属性来进行缓存，多次使用计算属性的时候会走缓存，只有依赖的值发生变化了才会进行更新。

watch是监听属性。监听一个属性值发生变化的时候执行回调，没有缓存性，支持异步监听，可以用deep属性设置深度监听，和immediate属性立即执行回调函数。

vue3有了功能更强大的`watchEffect`，会立即执行一遍回调函数来收集依赖。

# 6.如何实现一个vue-router

## 7. key的作用

1. key就像是虚拟节点的身份证号，作用是为了更高效的对比虚拟DOM
2. key是对比时判断两个节点是否相同的必要条件。渲染一组列表时，key往往是唯一标识，如果不定义key的话，值为undefined，vue只能是认为两个节点是同一个。就会导致更新出错。还会影响性能。
3. 实际使用渲染一组列表的时候key一定要设置，而且必须是唯一标识，也应该避免使用数组索引作为key，可能会出现一些隐蔽bug，一般可能使用后端传过来的id值什么的。

# 8.mutation和action的区别

mutation和action非常类似，mutation可以变更状态，但不能有异步操作，action可以有异步操作，但不能修改状态，需要用mutation才能更改状态。

如果在项目中使用vuex，一般调用API接口和一些复杂业务组合使用dispatch触发action，直接修改状态才用commit触发mutation。

mutation的回调函数参数是state对象，action函数参数为上下文context对象，可以结构为dispatch、commit、state方便使用。dispatch也会返回Promise实例便于使用异步结果。

commit方法相当于调用`options.mutation[type](state)`，而dispatch相当于`options.actions[type](stroe)`

在Pinia里面取消了两者的区别，合并为在一起了actions

# 9.ref和reactive的区别

1. 两者都能返回响应式对象，从语法使用上来说，一般使用ref来创建基础数据类型的响应式数据，使用reactive创建对象类型的响应式数据。ref也可以用来创建对象类型的，但是底层调的还是reactive
2. 使用的时候ref的对象需要.value使用，而reactive不需要。
3. ref返回一个设置了getter和setter的RefImpl对象，这也就是为什么需要.value使用的原因。而reactive返回的是一个Proxy代理对象。
4. ref对象收集的依赖都保存在自身`RefImpl`内部的dep属性里，所以ref有点类似于vue2的响应式原理，而reactive的依赖都保存在targetMap全局依赖管理器。需要层层找才能找到。

> 其实ref对象底层完全可以用reactive来实现，包装一下然后用reactive包装返回。但是尤大的意思是两个方法最好各司其职，ref的定义应该只暴露一个属性，就是值本身，而用reactive就会附加一些属性，违背了ref的目的:为一个内部值而服务，而不是被当做一个一般的响应式对象。还有性能问题，reactive做了很多ref里没有做的事，比如检查对象是不是有只读副本什么的，而用一个对象字面量来创建ref可以节约性能。
