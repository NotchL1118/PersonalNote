# new操作符

```js
function myNew(fn, ...args) {
    if (typeof fn !== "function") {
        return;
    }
    const obj = Object.create(fn.prototype);
    const result = fn.apply(obj, args);
    if (result !== null && typeof result === "object") return result;
    if (typeof result === "function") return result;
    return obj;
}
```

1. 创建一个对象
2. 使新创建的对象的原型指向构造函数的原型对象
3. 更改this执行构造函数给对象增加属性
4. 判断构造函数返回的是否是引用属性和函数，是的话返回，不是的返回新建的对象