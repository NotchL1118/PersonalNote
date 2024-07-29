# 用两个栈实现队列

> 难度：简单

## 题目

用两个栈实现一个队列。队列的声明如下，请实现它的两个函数 `appendTail` 和 `deleteHead` ，分别完成在队列尾部插入整数和在队列头部删除整数的功能。(若队列中没有元素，`deleteHead` 操作返回 -1 )

**示例 1：**

```
输入：
["CQueue","appendTail","deleteHead","deleteHead","deleteHead"]
[[],[3],[],[],[]]
输出：[null,null,3,-1,-1]
```

> **注意：**这里的输入的意思，第一行是要进行的操作，第二行对应每一次操作所需的参数，`CQueue`表示新建一个CQueue对象，所需的参数为[]，即表示此操作不需要参数；`appendTail`表示执行一个`appendTail()`操作，**被操作的元素为3**，`deleteHead`表示执行一个`deleteHead()`操作，对应的所需参数为[]，即此操作不需要参数，最后一个同理。



## 思路

队列是先进先出，栈是后进后出，使用两个栈来实现队列，就是用两个栈进行一下元素顺序调转。一个栈用于输入，一个栈用于输出。

当插入元素时，直接插入到插入栈A。

当删除元素时，先判断输出栈B是否有元素，有的话直接输出，没有的话，将输入栈元素依次入栈到输出栈B，这样输出栈B栈顶元素就是之前先进入的元素，然后再将输出栈栈顶元素弹出即可。

1. 声明两个栈

2. `appendTail`操作，直接向输入栈中添加元素
3. `deleteHead`操作，不需要每次都将输入栈A元素放入到输出栈B，当输出栈B不为空时，直接弹出栈顶元素，没有返回-1；为空时，将输入栈A元素依次出栈，放入输出栈B，最后弹出输出栈B的栈顶元素即可，没有就返回-1。

## 代码：TypeScript

```typescript
class CQueue {
    private stackA:number[]
    private stackB:number[]
    constructor() {
        this.stackA = []
        this.stackB = []
    }

    appendTail(value: number): void {
        this.stackA.push(value)
    }

    deleteHead(): number {
        if(!this.stackB.length){
            while(this.stackA.length){
                this.stackB.push(this.stackA.pop())
            }
        }
        return this.stackB.pop() ?? -1
    }
}
```

## JavaScript

```javascript
    var CQueue = function() {
        this.stackA = []
        this.stackB = []
    };

    /** 
     * @param {number} value
     * @return {void}
     */
    CQueue.prototype.appendTail = function(value) {
        this.stackA.push(value)
    };

    /**
     * @return {number}
     */
    CQueue.prototype.deleteHead = function() {
        if(!this.stackB.length){
            while(this.stackA.length){
                this.stackB.push(this.stackA.pop())
            }
        }
        if(this.stackB.length){
            return this.stackB.pop()
        } else {
            return -1
        }
    };
```

## 复杂度分析

时间复杂度：插入删除操作，时间复杂度均是O(1)。删除操作，虽然看起来是O(n)的复杂度，但是每个元素只会「至多被插入和弹出一次」，所以均摊下来每个元素被删除的时间复杂度为O(1)。

空间复杂度：O(n)，需要两个栈存储已有的元素。

## 额外知识

TypeScript中的`??`是什么意思，`??`和`||`的用法类似，只有一点点区别，例如A||B时，如果A的值为0时会直接排除A，但是`??`不会

```typescript
	console.log(null || 5 ) // 5
	console.log(null ?? 5 ) // 5

	console.log(undefined || 5 ) // 5
	console.log(undefined ?? 5 ) // 5

	console.log(0 || 5 ) // 5
	console.log(0 ?? 5 ) // 0
```



# 包含min函数的栈

> 难度：简单

## 题目

定义栈的数据结构，请在该类型中实现一个能够得到栈的最小元素的 min 函数在该栈中，调用 min、push 及 pop 的时间复杂度都是 O(1)。

**示例:**

```javascript
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.min();   --> 返回 -3.
minStack.pop();
minStack.top();      --> 返回 0.
minStack.min();   --> 返回 -2.
```

## 思路

要理解栈先进后出的性质，对于栈来说，如果一个元素`a`在入栈时，栈中已经有元素`b,c,d`那么无论这个栈在之后经历了什么操作，只要`a`还在栈中，那么`b,c,d`已经在栈中，`a`在弹出之前，`b,c,d`一定不会被弹出。因此在任意时刻，只要栈顶的元素是`a`，那么我们就可以确定栈中现在的元素一定是`a,b,c,d`。

基于此，我们在每个元素(例如`a`)入栈时，将当前栈的最小值(例如`m`)存储起来，之后无论何时只要栈顶元素是`a`，那么就可以直接返回最小值`m`。

<img src='https://assets.leetcode-cn.com/solution-static/jianzhi_30/jianzhi_30.gif'/>

## 代码:TypeScript

按照思路，我们需要使用**辅助栈**，使得每个元素可以和其相应的最小值m时刻保持一一对应。使用**辅助栈**与元素栈同步插入和弹出操作，用于存储每个元素对应的最小值。

1. 当一个元素`x`入栈时，我们取`x`和辅助栈的栈顶元素(即插入前的元素栈中的最小值)做对比，取最小者插入辅助栈。
2. 当一个元素出栈时，辅助栈也同时执行出栈操作。
3. 最小值即为辅助栈的栈顶元素。

```typescript
class MinStack {
    private x_stack:Array<number>
    private min_stack:Array<number>
    constructor() {
        this.x_stack = []
        this.min_stack = [Infinity]
    }

    push(x: number): void {
        this.x_stack.push(x)
        let minNum = Math.min(x,this.min_stack[this.min_stack.length - 1])
        this.min_stack.push(minNum)
    }

    pop(): void {
        this.x_stack.pop()
        this.min_stack.pop()
    }

    top(): number {
        return this.x_stack[this.x_stack.length - 1]
    }

    min(): number {
        return this.min_stack[this.min_stack.length - 1]
    }
}
```

## 复杂度分析

时间复杂度：栈的插入、删除、读取都是O(1)

空间复杂度：O(n)，其中n为总操作数，最坏情况下，连续插入n哥元素，此时两个栈占用的空间为O(n)

## 额外知识

1. JavaScript中的[Infinity](https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Reference/Global_Objects/Infinity)代表一个数值，表示无穷大

2. TS中数组定义有两种方式

- 元素类型后面加上[]

```typescript
	let arr:number[]
```

- 数组泛型,`Array[元素类型]`

```typescript
	let arr:Array<number>
```

3. JS中数组方法的效率

- `pop()` `push()`在数组尾部操作的方法为`O(1)`
- `forEach()`、`map()`、`shift()`、`unshift()`、等需要遍历或者在数组头部操作的方法的时间复杂度为`O(n)`
- `splice()`、`concat()`、`find()`等方法的时间时间复杂度为`O(n)`，但最优情况可能为`O(1)`，如`splice()`在数组尾部操作、`find()`第一个元素就符合条件。
