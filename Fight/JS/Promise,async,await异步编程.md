# [Promise，async，await]

> 一直忘，一直忘，😡这次记下来，取自[这里](https://www.bilibili.com/video/BV1WP4y187Tu/?spm_id_from=..search-card.all.click&vd_source=7dcb6c648b7faefd7170d0fc0494d4ad) [还有这里](https://www.bilibili.com/video/BV1WP4y187Tu/?spm_id_from=333.880.my_history.page.click&vd_source=7dcb6c648b7faefd7170d0fc0494d4ad)

## 前言，何为异步编程

最简单的理解，异步编程允许我们执行一个长时间任务时，程序不许等待，而是继续执行之后的代码，直到这些任务完成之后再回来通知你，通常以回调函数callback的形式，这种模式可以避免程序的阻塞

JavaScript是单线程的编程语言，有两种实现异步的方式

### 1. 传统回调函数


我们可以使用`setTimeout`函数让一个回调函数在指定时间后执行，`setTimerout`函数会立即返回，并继续执行之后的代码，而我们传入的回调函数则会在预定的时间才会执行
```javascript
	setTimeout(()=>{
		console.log("你会第二时间看到我")
	},1000);
	console.log("你会立刻看到我")
```

当时当我们想执行多个异步操作，代码可能就会变成下面这样，即产生回调地狱(Callback Hell😈)

```javascript
	setTimeout(()=>{
		console.log("等一秒");
        
        setTimeout(()=>{
            console.log("等两秒")
            
            setTimeout(()=>{
                console.log("等三秒")
            
            },1000)
        },1000)
	},1000);
```

### 2. Promise

为解决回调地狱问题，Promise孕育而生，语法上Promise是一个构造函数，用来封装异步操作并可以获取其成功或失败的结果。字面意思上，Promise代表一个承诺，承诺会在未来的某个时刻执行一些操作

#### 2.1 Promise的状态

Promise有三个状态：

- pending (等待态)
- fulfilled 或 resolved (成功态)
- rejected (失败态)

Promise必须要接受一个回调函数，这个回调函数有两个参数，两个参数也是两个函数: `(resolve,reject) => {}` 这俩函数可以传参的，下面再讲

> 这里的resolve和reject只是一个形参，名字任意的，但是约定俗成的都是写成resolve和reject😀
>
> 也可以把resolve和reject当作信使，给下面的then方法传参数用的，妥妥的工具人罢了

```javascript
	new Promise((resolve,reject) => {
        .....
    })
```

- 实例化Promise后，默认是等待状态
- 执行`resolve()`函数后，Promise从等待态 -> 成功状态
- 执行`reject()`函数后，Promise从等待态 -> 失败状态

当Promise的状态一旦从等待转变为某一个状态后，后续的转变自动忽略，例如:先resolve()再调用reject()，那么Promise的最终结果还是成功态。

#### 2.2 then方法

实例化Promise后得到的Promise对象具有then方法。

then方法具有两个回调函数作为参数： `()=>{},()=>{}`

```javascript
	const p = new Promise((resolve,reject) => {
        .....
    })
    p.then(()=>{},()={})
```

- Promise对象为**成功状态**时就会自动执行then方法的**第一个**回调函数
- Promise对象为**失败状态**时就会自动执行then方法的**第二个**回调函数

#### 2.3 catch方法

大多数使用Promise的时候，大部分情况，只会使用resolve方法，所以Promise回调函数中常常省略reject函数，在then中常常省略第二个回调函数，但我们还是得处理异步中的一场，所以ES6提供了一个`catch()`方法专门来处理异常部分(失败态)

> catch就是专门用来处理reject失败态的，本质就是then的特例

```javascript
    new Promise((resolve, reject) => {
        reject("失败");
    }).then(res => {
        console.log(res);
    }).catch(err => {
        console.log(err);   // 失败
    });

	//其实上面的代码本质等同于
	new Promise((resolve,reject) => {
        reject("失败")
    }).then(res => {
        console.log(res);
    }).then(null,err => {
        console.log(err) //失败
    })
```

在Promise中，一旦出现了错误状态，错误不会消失，会一直向下传递，直到遇到可以处理错误的函数

#### 2.4 finally()方法

当Promise状态发生变化时，不论如何变化都会执行，不变化不执行

- finally()不接收参数
- finally()也是then的特例
- 主要用来处理一些必做操作，比如在操作数据库之后(无论成不成功)都要关闭数据库链接

```javascript
    new Promise(resolve => {
        resolve("测试01");
    }).finally(data => {
        console.log(data + " finally01");
        return new Promise((resolve, reject) => {
            reject("测试02");
        })
    }).finally(data => {
        console.log(data + " finally02")
    }).catch(err => {
        console.log("catch: " + err);
    });

    /*
    undefined finally01
    undefined finally02
    catch: 测试02
    */
```

从上面例子也可以看出来，finally可以正常接受状态，但是不能接受参数

#### 2.5 resolve和reject函数传参

- `resolve()`的参数会传递给then方法的第一个回调函数

- `reject()`的参数会传递给then方法的第二个回调函数

通常不仅仅会传递一个基本数据类型的值，会传递对象，再比如传递一个错误错误对象`reject(new Error("出错啦!"))`

#### 2.6 最简单的小案例

这里来个最简单的Promise封装Ajax请求来演示

```javascript
	const p = new Promise((resolve,reject) => {
        //封装一下异步操作
        const xhr = new XMLHttpRequset();
        xhr.open("GET","https://api......");
        xhr.send();
        xhr.onreadystatechange = ()=>{
            if(xhr.readyState === 4){
                if(xhr.status >= 200 && xhr.status < 300){
                    // 这里就成功请求了
                    resolve(xhr.response); // resolve传参，p变为成功态
                }else{
                    // 如果失败
                    reject(xhr.status); //reject传参，p变为失败态
                }
            }
        }
    })
    
    p.then((value) => {
        console.log(value) // 这里的value就是上面resolve的传参，即为xhr.response
    }，（err) => {
        console.log(err); // 这里同理，这里的err就是上面reject的传参，为xhr.status
    })
```

#### 2.7 链式调用

看到这里，如果Promise光是这样，那Promise怎么解决回调地狱？那我们就得看then方法了

**then方法执行后的返回值默认为一个新的Promise对象**，我们就可以在这个返回的Promise对象上继续调用then方法

```javascript
	p.then((value)=>{
        
    }).then((data)=>{
        
    });
```

then方法其实默认返回的是undefined，但是ES6的机制规定，当then的返回值为非Promise对象时，就会将这个返回值包装成一个Promise，并让这个Promise默认调用resolve()方法(即为成功态)，并将这个返回值作为resolve的参数，看例子：

```javascript
	const p = new Promise((resolve,reject) =>{
        resolve();
    });	
	p.then((data)=>{
        //没有返回值，默认就会返回undefined
        //就默认调用 return undefined;
        //事实上，这里就相当于
        /*
        return new Promise(resolve => {
        	resolve(undefined);
        });
        */
    },(error)=>{
        
    });
```

这也就意味着，我们可以链式调用then方法

```javascript
	const p = new Promise((resolve,reject) =>{
        resolve();
    });	
	p.then((data)=>{
        //默认return undefined
        /*相当于
        return new Promise(resolve => {
        	resolve(undefined);
        });
        */
    }).then((data)=>{
        console.log(data);   // 打印 undefined
        return 666;
        /*相当于
        return new Promise(resolve => {
        	resolve(666);
        });
        */
    }).then((data)=>{
        console.log(data);  // 打印 666
    })
```

当然了，如果我们需要让then返回一个失败状态的Promise对象，我们可以手动return一个Promise对象并执行reject()方法，因此，我们就可以解决回调地狱问题了👏

## async和await

### 1. async

`async`和`await`是ECMA17中新加入的两个关键词，简单来说，就是基于Promise之上的语法糖，可以让异步操作更加简单明了，两种语法结合可以让异步代码像同步代码一样

async可以将一个函数标记为异步函数，**该函数的返回值永远是Promise对象**；且如果我们返回的值不是一个Promise对象，则会默认包装成一个成功态的Promise对象，和上面那个then的返回值如出一辙，我们可以使用then、catch方法

```javascript
	async function fnc1(){
        return "我是返回值";
	};
	fnc1().then((data)=>{
        console.log(data); // 打印 我是返回值
    },(err)=>{
        console.log(err);
    })
```

### 2. await

在async异步函数中，我们可以调用其他的异步方法(Fetch等等)，我们也不需要再使用then方法，而是使用**await** 语法，await是等待的意思，且基于Promise，引擎在遇到await的时候会等待，直到Promise状态完成并返回结果

- await必须写在async函数中
- await右侧的表达式一般为promise对象
- **await返回的是promise成功的值**(就这个地方，当时卡了好久都没接受，js真是太神奇了)
- 如果await旁边的promise失败了，就会抛出异常，**需要用try...catch捕获处理**

简单使用

```javascript
	async function fnc(){
        console.log(1);
        let two = await Promise.resolve(2); // 这里变量two的值就是promise成功的值，这里是2
        console.log(two);
        console.log(3);
        return 4;
    }
	fnc().then((value)=>{
        console.log(value);
    })
	/*输出为
	1
	2
	3
	4
	*/
	//在这里，异步代码就很像同步代码，阅读起来很方便
```

async和await很大的作用就是在于优化`Fetch`的语法

举一个例子

![image-20221022165309069](https://pic.lsyfighting.cn/img/image-20221022165309069.png)

这么一坨代码，由于Fetch的异步性，每次打印出来的结果都不会相同

我们就可以使用`async`和`await`来改善代码

```javascript
const fnc = async ()=>{
	const url = 'https://gorest.co.in/public/v1/users';
	let response1 = await fetch(`${url}/1/`);
	let josn1 = await response1.json();  // json()方法返回的也是一个promise对象
	let name1 = json1.data.name;

	let response2 = await fetch(`${url}/2/`);
	let josn2 = await response2.json();  // json()方法返回的也是一个promise对象
	let name2 = json2.data.name;

	let response3 = await fetch(`${url}/3/`);
	let josn3 = await response3.json();  // json()方法返回的也是一个promise对象
	let name3 = json3.data.name;

	console.log(name1);
	console.log(name2);
	console.log(name3);
}
fnc();
```

经过最简单的改造，每次执行`fnc()`函数得到的结果都会是一样的，再也不会像最开始一样不确定了

### 3. 注意

还是上面那个例子，我们注意到，这么写会有问题，太累赘了，而且这么写，打破了3个fetch()操作的并行，因为只有第一个任务执行完了才会执行第二，第二个完第三个，因此我们可以使用`Promise.all`方法再一次改造

```javascript
const fnc = async ()=>{
	try{
        const url = 'https://gorest.co.in/public/v1/users';
        
        let responses = await Promise.all([fetch(`${url}/1/`),fetch(`${url}/2/`),fetch(`${url}/3/`)]);
        let jsons = responses.map(response => response.json());
        let values = await Promise.all(jsons);
        
        values.map(value => {
            console.log(value.data.name);
        }) 
    } catch(err) {
            console.log(error)
    }
}
fnc();
```
### 4. 面试题补充
```js
async function async1(){
  console.log('async1 start')
  await async2()
  console.log('async1 end')
}
async function async2(){
  console.log('async2')
}
console.log('script start')
setTimeout(function(){
  console.log('setTimeout') 
},0)  
async1();
new Promise(function(resolve){
  console.log('promise1')
  resolve();
}).then(function(){
  console.log('promise2')
})
console.log('script end')
```

```js
// script start
// async1 start
// async2
// promise1
// script end
// async1 end
// promise2
// setTimeout
```

**在async中的，await之后内容，相当于promise.then里的内容，放到微任务队列里。**

`script start`直接输出，然后是setTimeout注册函数到宏任务Event Queen里，等到同步任务和微任务都执行完了才执行。然后是async1执行，输出`async1 start`，然后是执行async2()函数，输出`async2`相当于执行了

```js
new Promise(function(resolve){
	console.log('async2')
}).then(()=>{
    console.log('async1 end')
})
```

这里之后的console.log('async1 end')就相当于放到了promise.then里面，会放到微任务队列，所以接下来继续执行同步任务，接下来遇到new Promise，输出`promise1`，再把回调函数放到微任务队列里，接下来是同步任务输出`script end`，最后先执行微任务队列,依次输出`async 1 end` `promise2` 最后执行宏任务队列`setTimeout`

## 手写Promise

