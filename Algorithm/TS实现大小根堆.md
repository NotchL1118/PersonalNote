插入元素：插入到最后，然后上浮操作

删除元素：用最后一个元素替换首元素，然后删除最后一个元素，第一个元素再下沉操作

```ts
class Heap {
    arr: number[]
    compare: Function
    constructor(compare: Function) {
        this.arr = [0];
        this.compare = compare ? compare : (a: number, b: number) => a > b; // 默认大根堆
    }
    // 加入元素
    push(item: number) {
        this.arr.push(item);
        this.up(this.arr.length - 1);
    }
    // 弹出堆顶元素,将最后一个元素和首元素交换，然后第一个元素下沉即可
    pop() {
        if (this.arr.length <= 1) return null;
        this.swap(1, this.size);
        let head = this.arr.pop(); // 原栈顶
        this.down(1);
        return head;
    }
    // 上浮
    up(k: number) {
        let { arr, compare, parentIndex } = this;
        while (k > 1 && compare(arr[k], arr[parentIndex(k)])) {
            this.swap(k, parentIndex(k));
            k = parentIndex(k);
        }
    }
    //下潜
    down(k: number) {
        let { arr, compare, parentIndex, leftSonIndex, rightSonIndex, size } = this;
        let t = k;
        // 注意，compare顺序不可调换，如果子节点比父节点更符合条件，才需要交换，也就是子节点是第一个参数
        if (leftSonIndex(k) <= size && compare(arr[leftSonIndex(k)], arr[t])) t = leftSonIndex(k);
        if (rightSonIndex(k) <= size && compare(arr[rightSonIndex(k)], arr[t])) t = rightSonIndex(k);
        if (t != k) {
            this.swap(t, k);
            this.down(t);
        }
    }

    // 获取父索引
    parentIndex(k: number) {
        return k >>> 1;
    }
    leftSonIndex(k: number) {
        return k * 2;
    }
    rightSonIndex(k: number) {
        return k * 2 + 1;
    }
    peek() {
        return this.arr[1];
    }
    swap(i: number, j: number) {
        [this.arr[i], this.arr[j]] = [this.arr[j], this.arr[i]];
    }
    get size() {
        return this.arr.length - 1; // -1是因为索引0无效
    }
}
```

