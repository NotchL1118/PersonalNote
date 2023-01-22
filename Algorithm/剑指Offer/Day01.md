# 用两个栈实现队列

> 难度：简单

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

