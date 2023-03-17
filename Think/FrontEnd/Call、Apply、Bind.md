> 三个都是改变指针指向，call和apply都会执行一遍函数，区别在于call可以传多个形参，而apply需要传一个数组进去。而bind就是永久改变函数指针，返回一个改变了指针指向的函数,且不会执行一次函数。

# call

```javascript
let dog = {
    name:"旺财",
    sayFood(food1,food2){
        console.log(this.name + "喜欢吃" + food1 + food2)
    }
}

let cat = {
    name:"喵喵"
}
// 第一个参数是要改变的this指向，第二个是传入的参数
dog.sayFood.call(cat,"鱼","肉") 
// 喵喵喜欢吃鱼肉
```

# apply

```javascript
let dog = {
    name:"旺财",
    sayFood(food1,food2){
        console.log(this.name + "喜欢吃" + food1 + food2)
    }
}

let cat = {
    name:"喵喵"
}

dog.sayFood.call(cat,["鱼","肉"]) 
// 喵喵喜欢吃鱼肉
```

# bind

```javascript
let dog = {
    name:"旺财",
    sayFood(food1,food2){
        console.log(this.name + "喜欢吃" + food1 + food2)
    }
}

let cat = {
    name:"喵喵"
}

let fun = dog.sayFood.bind(cat,"鱼","肉") 
fun()
// 喵喵喜欢吃鱼肉
```

