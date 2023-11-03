```js
Function.prototype.myCall = function (that, ...args) {
    that = that || window;
    let symbol = Symbol();
    that[symbol] = this;
    var result = that[symbol](...args);
    delete that[symbol]
    return result
};


Function.prototype.myApply = function (that, args) {
    that = that || window
    if (!Array.isArray(args)) {
        console.error('error');
    }
    let symbol = Symbol();
    that[symbol] = this;
    var result = that[symbol](...args);
    delete that[symbol]
    return result;
};

Function.prototype.myBind = function (context, ...args) {
    let that = this;
    return function () {
        that.apply(context, args.concat(arguments));
    }
};
```

