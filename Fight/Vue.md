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
  

# 2. 

