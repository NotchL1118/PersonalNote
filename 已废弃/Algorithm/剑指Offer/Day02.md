# 从尾到头打印链表

> 难度：简单

## 题目

输入一个链表的头节点，从尾到头反过来返回每个节点的值（用数组返回）

**示例 1：**

```
输入：head = [1,3,2]
输出：[2,3,1]
```

## 思路

1. 用一个数组依次遍历下去，最后反转一下数组，时间复杂度和空间复杂度都是O(n)

2. 使用递归

## 代码：Typescript

```typescript
/**
 * Definition for singly-linked list.
 * class ListNode {
 *     val: number
 *     next: ListNode | null
 *     constructor(val?: number, next?: ListNode | null) {
 *         this.val = (val===undefined ? 0 : val)
 *         this.next = (next===undefined ? null : next)
 *     }
 * }
 */

function reversePrint(head: ListNode | null): number[] {
    let res:number[] = new Array<number>()
    dfs(head,res)
    return res
};

function dfs(head: ListNode | null,list :number[] ): void {
    if(head === null ) return 
    dfs(head.next,list)
    list.push(head.val)
}
```

# 反转链表

> 难度：简单

## 题目

定义一个函数，输入一个链表的头节点，反转该链表并输出反转后链表的头节点。

**示例:**

```
输入: 1->2->3->4->5->NULL
输出: 5->4->3->2->1->NULL
```

## 思路

1. 迭代法，在遍历链表时，将当前节点的`next`指针改为指向前一个节点。由于节点没有引用其前一个节点，因此必须事先存储其前一个节点。在更改引用之前，还需要存储后一个节点指针。最后返回新的头引用。
2. 递归法。

## 代码TypeScript

迭代法

```typescript
/**
 * Definition for singly-linked list.
 * class ListNode {
 *     val: number
 *     next: ListNode | null
 *     constructor(val?: number, next?: ListNode | null) {
 *         this.val = (val===undefined ? 0 : val)
 *         this.next = (next===undefined ? null : next)
 *     }
 * }
 */

function reverseList(head: ListNode | null): ListNode | null {
    let prev = null
    let curr = head
    while(curr) {
        const next = curr.next
        curr.next = prev
        prev = curr
        curr = next
    }
    return prev
}; 
```

时间复杂度O(n)，空间复杂度O(1)

# 复杂链表的复制

> 难度：中等 第一个中等题目，直接看答案了

## 题目

请实现 `copyRandomList` 函数，复制一个复杂链表。在复杂链表中，每个节点除了有一个 `next` 指针指向下一个节点，还有一个 `random` 指针指向链表中的任意节点或者 `null`。

<img src='https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/01/09/e1.png'/>

```typescript
输入：head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
输出：[[7,null],[13,0],[11,4],[10,2],[1,0]]
```

```
输入：head = []
输出：[]
解释：给定的链表为空（空指针），因此返回 null。
```

## 思路

这道题需要对一个特殊链表进行**深拷贝**，如果是普通的链表，可以直接遍历拷贝，这题难在有一个`random`随机指针，当拷贝节点时，可能`random`随机节点指向的是一个还没有复制过的节点。

**所以我们可以先进行所有节点拷贝，这样之后就不会出现指向一个还没有复制过的节点的情况。**重点就是这个了。然后原节点和复制节点的联系有两种方式

1. 迭代+哈希表，使得原节点和复制节点一对一照应，这个简单，就不讲了

2. 迭代+节点拆分法，这里就是使用这个，在原节点的后面续接一个复制节点，随机节点先空着；让复制节点指向原节点的下一个节点，复制完所有的节点后，所有原节点都有一个对应的复制节点了，再遍历一次，使得所有的复制节点的random指针指向对应的节点的复制节点(让复制节点和复制节点串起来)，最后再遍历一次，复原原链表，使得复制链表分离出来。

## 代码

1. 迭代+哈希表

```javascript
//  使用map，空间复杂度O(n)
var copyRandomList = function(head) {
    if(!head) return head;
    let node = head;
    let map = new Map();

    // 复制节点，将新节点放入map中
    while(node){
        map.set(node, new Node(node.val));
        node = node.next;
    }
    node = head;

    //对map里的新节点进行遍历操作
    while(node){
        map.get(node).next = map.get(node.next) === undefined ? null : map.get(node.next);
        map.get(node).random = map.get(node.random);
        node = node.next;
    }
    return map.get(head);
};
```

2. 迭代+节点拆分法

   1. 在原链表的每一个节点后，续接一个新节点。
   2. 再为每一个新节点的random属性赋值
   3. 将当前链表，按照一个间隔一个的顺序拆分，再将新节点，串成一个新链表，将原链表的节点，拆分出来复原成原链表
   4. 将原链表的最后一个节点的next指针，重新指向null

   ```javascript
   /**
    * // Definition for a Node.
    * function Node(val, next, random) {
    *    this.val = val;
    *    this.next = next;
    *    this.random = random;
    * };
    */
   
   /**
    * @param {Node} head
    * @return {Node}
    */
   var copyRandomList = function(head) {
       if(!head) return null
       let node = head
   
       // 每一个节点新建复制节点
       while(node) {
           node.next = new Node(node.val,node.next,null)
           node = node.next.next
       }
   
       // 每一个复制节点的random节点指向对应的复制节点
       node = head
       while(node) {
           if(node.random) node.next.random = node.random.next
           node = node.next.next
       }
   
       // 进行分割复原
       node = head
       let newNode = head.next
       let res = newNode
       while(newNode.next) {
           node.next = newNode.next
           newNode.next = newNode.next.next
           node = node.next
           newNode = newNode.next
       }
       node.next = null
       return res
   };
   ```

   ## 复杂度分析

   一、哈希法时间复杂度O(n),空间复杂度O(n)

   二、迭代+节点拆分法，时间O(n)，空间复杂度O(1)，因为返回值是不计入空间复杂度的