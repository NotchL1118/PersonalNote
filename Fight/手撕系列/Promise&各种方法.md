# 手写Promise A+规范

> 背吧就😀

```js
const PENDING = 'PENDING';
const FULFILLED = 'FULFILLED';
const REJECTED = 'REJECTED';

function resolvePromise(promise2, x, resolve, reject) {
    if (promise2 === x) {
        return reject(new TypeError('Chaining cycle detected for promise #<Promise>'));
    }
    if (x instanceof myPromise) {
        x.then(resolve, reject);
    } else {
        resolve(x);
    }
}

class myPromise {
    constructor(excutor) {
        this.status = PENDING;
        this.value = null;
        this.reason = null;
        this.onFulfilledCallbacks = [];
        this.onRejectedCallBacks = [];
        try {
            excutor(this.resolve, this.reject);
        } catch (err) {
            this.reject(err);
        }
    }
    resolve = (value) => {
        if (this.status === PENDING) {
            this.status = FULFILLED;
            this.value = value;
            while (this.onFulfilledCallbacks.length) {
                this.onFulfilledCallbacks.shift()(value);
            }
        }
    }
    reject = (reason) => {
        if (this.status === PENDING) {
            this.status = REJECTED;
            this.reason = reason;
            while (this.onRejectedCallBacks.length) {
                this.onRejectedCallBacks.shift()(reason);
            }
        }
    }
    then = (onFulfilled, onRejected) => {
        onFulfilled = typeof onFulfilled === 'function' ? onFulfilled : value => value;
        onRejected = typeof onRejected === 'function' ? onRejected : reason => { throw reason };
        const promise2 = new myPromise((promise2_resolve, promise2_reject) => {
            const fulFilledCallback = () => {
                queueMicrotask(() => {
                    try {
                        const x = onFulfilled(this.value);
                        resolvePromise(promise2, x, promise2_resolve, promise2_reject);
                    } catch (err) {
                        promise2_reject(err);
                    }
                });
            }
            const rejectedCallback = () => {
                queueMicrotask(() => {
                    try {
                        const x = onRejected(this.reason)
                        resolvePromise(promise2, x, promise2_resolve, promise2_reject);
                    } catch (err) {
                        promise2_reject(err);
                    }
                })
            }
            if (this.status === FULFILLED) {
                fulFilledCallback();
            } else if (this.status === REJECTED) {
                rejectedCallback();
            } else if (this.status === PENDING) {
                this.onFulfilledCallbacks.push(fulFilledCallback)
                this.onRejectedCallBacks.push(rejectedCallback);
            }
        });
        return promise2;
    }


    static resolve(param) {
        if (param instanceof myPromise) {
            return param;
        }
        return new Promise((resolve, _) => {
            resolve(param);
        })
    }

    static reject(reason) {
        return new myPromise((_, reject) => {
            reject(reason);
        });
    }
}

module.exports = myPromise;
```

# Promise.all

```js
MyPromise.prototype.all = (cbs) => new Promise((resolve, reject) => {
    try {
        let count = 0;
        let fulfilledCount = 0;
        const results = [];
        for (let cb of cbs) {
            let i = count++;
            Promise.resolve(cb).then((data) => {
                results[i] = data;
                fulfilledCount++;
                if (fulfilledCount === count) {
                    resolve(results);
                }
            }, reject)
        }
        if (count === 0) {
            resolve(results);
        }
    } catch (err) {
        reject(err);
    }
})
```

# Promise.allSettled

```js
MyPromise.prototype.allSettled = (promises) => new Promise((resolve, reject) => {
    let settledCount = 0;
    let count = 0;
    let results = [];
    const setData = (index, data) => {
        settledCount++;
        results[index] = data;
        if (settledCount === count) {
            resolve(results);
        }
    }
    for (let p of promises) {
        let i = count++;
        Promise.resolve(p).then((data) => {
            setData(i, {
                status: 'fulfilled',
                value: data
            });
        }, (err) => {
            setData(i, {
                status: 'rejected',
                value: err
            });
        })
    }
    if (count === 0) {
        resolve(results);
    }
})
```

# Promise.race

```js
MyPromise.prototype.race = (promises) => {
    return new Promise((resolve, reject) => {
        let count = 0;
        for (let p of promises) {
            count++;
            Promise.resolve(p).then(resolve, reject);
        }
        if (count === 0) {
            return;
        }
    })
}

```

# Promise.finally

```js
MyPromise.prototype.finnally = (cb) => {
    return this.then(
        value => MyPromise.resolve(cb()).then(() => value),
        err => MyPromise.reject(cb()).then(() => { throw err })
    )
}
```

