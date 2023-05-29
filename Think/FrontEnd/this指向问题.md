# this

> this指向最后一次调用这个方法的对象

## 1.在浏览器中，this指代或者指向什么

1. 在全局作用域下，指向的就是window对象

2. 在方法体中，this的指向：**谁调用它，this就指向谁**

```js
function fun1(){
    console.log(this) // window
}

let obj = {
    name:"lsy",
    fun2(){
        console.log(this) // obj
    }
}

fun1() // window  这个就相当于window.fun1()
obj.fun2() // obj
```

3.如果方法体用的是箭头函数()=>{}:默认情况下，指向调用者的父级作用域,因为回调函数是由浏览器来执行的

```js
let fun1 = ()=>{
    console.log(this) // window
}
let obj = {
    name:'lsy',
    fun2:()=>{
        console.log(this)
    }
}
fun1() // window
obj.fun2() // window

```

4. 定时任务：setTimeout:this指向window，因为是由window来调用回调函数，不论是普通函数还是箭头函数

5. 数组的方法中，forEach、findIndex、map：this指向window

6. 一些触发方法:onclick等等，普通函数指向dom元素，箭头函数指向window

```js
<div id="demo">这是demo<div/>
let el = document.getElementById('demo');
el.onclick = function() {
    console.log(this) // <div id="demo">这是demo<div/>
}

el.onclick = () => {
    console.log(this) // window
}
```

7. 当用`new`运算符调用构造函数时，`this`指向返回的这个对象。

## 2. 改变this指向

1. call
2. apply
3. bind

## 3.优先级问题

1. 有哪几种方式可以绑定this？

   1. new方式
   2. 显式绑定-call、apply、bind
   3. 隐式绑定（默认绑定）

2. 几种方式的优先级

   new > 显式绑定 > 默认绑定