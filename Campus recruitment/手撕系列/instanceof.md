# instanceof

## 作用

instanceof 是 JavaScript 中的一个二元操作符，顾名思义，它用来检测某个对象是否是某个构造函数的实例，或者说，用于检查一个对象是否属于某个特定的 Class。

顺带一提，instanceof 是会考虑继承关系的，也就是说，如果用它来检测一个对象是否是某个 Class 的实例，那么，如果这个对象是这个 Class 的子类的实例，instanceof 也会返回 true。

## 原理

1. 如果 Class 存在静态方法 `Symbol.hasInstance`，那么调用它去判断 obj 是否是 Class 的实例，instanceof 的结果就是它的返回值；假如 `Symbol.hasInstance` 方法的返回值不是 boolean 类型，会被转换成 boolean 类型

2. 如果 Class 不存在静态方法 `Symbol.hasInstance`，那么就会去判断 obj 的原型链上是否存在 Class.prototype，如果存在，那么 obj 就是 Class 的实例，instanceof 的结果就是 true，否则就是 false

根据第一个规则，如下图

```js
class MyArray {
  static [Symbol.hasInstance](instance) {
    return Array.isArray(instance);
  }
}
console.log([] instanceof MyArray); // true
```

## 手写

```js
function myInstanceof(obj, Class) {
    if (typeof Class !== 'function') {
        throw new Error('Right Hand Must Be Fcuntion');
    }

    if (typeof obj !== 'object' || obj === null) return false;

    let proto = Object.getPrototypeOf(obj);

    while (true) {
        if (proto === null) return false;
        if (proto === Class.prototype) return true;
        proto = Object.getPrototypeOf(proto);
    }
}
```