nodejs出现后，前端开发开始使用nodejs环境进行开发，webpack把模块化的代码转化为浏览器可执行的代码，它提供了import、export的ES6模块化支持，通过分析代码中import导入的依赖，把需要的代码加载进来，在webpack中，任意文件都可以导入，只需要有对应的loader就行。在打包过程中还可以通过plugins干预打包过程，例如剔除不必要的代码。

> 因为是在nodejs环境配置，所有其实是没有import export这些东西的，都是最后编译出来的。
>
> 且在webpack.config.js里也是用commonjs来进行配置

## 学习过程

### 简单使用

创建一个文件夹，然后`pnpm init`初始化

`pnpm add webpack webpack-cli -D`安装两个依赖,文件目录

> pnpm add 默认是-S，也就是保存到生产依赖dependencies，而pnpm add -D 是保存到开发依赖devDependencies,而webpack之类的只在开发时候用，所以-D

![image-20230827174542688](./assets/image-20230827174542688.png)

首先在index的js中写入一些代码，具体看文件，data中export导出一个函数，然后新建一个webpack.config.js文件

```js
const path = require('path');
module.exports = {
    mode: 'development',
    entry: './src/index.js',
    output: {
        filename: 'bundle.js',
        path: path.resolve(__dirname, "dist"),
    }
}
```

配置这些简单的，比如mode为`development || production`，entry就是入口文件，output是打包选项，可以设置打包路径和文件名

然后`npx webpack`直接执行webpack包里的默认打包命令

### 引入style-loader和css-loader

这时候新建一个style.css简单写一点样式，现在打包会出错，需要`pnpm add style-loader css-loader -D`，然后配置webpack.config.js文件，添加module

```js
    module: {
        rules: [
            {
                test: /\.css$/i,
                use: ['style-loader', 'css-loader']
            }
        ]
    }
```

`test:/\.css$/i`匹配所有以.css结尾的文件，i表示忽略大小写，use表示使用哪些loader，以后scss,less,ts,vue估计也是这样配置不同的loader

**loader是从后往前执行，所以这里顺序不能错！**

### 配置图片

webpack原生支持处理图片，不需要额外的loader,只需要配置type为asset/resource

```js
    module: {
        rules: [
            {
                test: /\.css$/i,
                use: ['style-loader', 'css-loader'] // style-loader将样式通过style标签注入
            },
            {
                test: /\.(png|svg|jpg|jpeg|gif)$/i,
                type: 'asset/resource',
            }
        ]
    }
```

### 使用插件自动生成html

每次index.html还需要手动更新，用插件自动生成html文件，使用插件`html-webpack-plugin -D`,然后在webpack.config.js中添加plugins,导入的html-webpack-plugin是一个构造函数，可以传入参数设置生成的html一些属性

```js
const HtmlWebpackPlugin = require('html-webpack-plugin');
module.exports = {
    mode: 'development',
    entry: './src/index.js',
    output: {
        filename: 'bundle.js',
        path: path.resolve(__dirname, "dist"),
    },
    plugins: [
        new HtmlWebpackPlugin({
            title: '这是Blogs'
        })
    ],
}
```

### 使用babel

使用babel转义高版本JS代码使之支持低版本浏览器，对js代码使用相应的**loader**

`pnpm add babel-loader @babel/core @babel/preset-env`

在rules里面新增处理js文件

```js
    module: {
        rules: [
            {
                test: /\.js$/i,
                exclude: /node_modules/,
                use: {
                    loader: 'babel-loader',
                    options: {
                        presets: ['@babel/preset-env'],
                    }
                }
            }
        ]
    }
```

还可以在设置,方便看打包后的代码

```js
module.exports = {
    devtool: 'inline-source-map',
}
```

成功进行了转义

![image-20230827181309635](./assets/image-20230827181309635.png)

### 压缩打包后的代码

`pnpm add terser-webpack-plugin -D`

然后增加一个`optimization选项`

```js
const TerserPlugin = require('terser-webpack-plugin');
module.exports = {
    optimization: {
        minimize: true,
        minimizer: [new TerserPlugin()],
    },
}
```

成功✌

<img src="./assets/image-20230827181627823.png" alt="image-20230827181627823" style="zoom:33%;" />

### 开发服务器

`pnpm add webpack-dev-server -D`

然后在webpack里添加一个`devServer`

```js
module.exports = {
    devServer: {
        static: './dist'
    },
}
```

并且在`package.json`中添加命令

```js
	"scripts": {
		"start": "webpack-dev-server --open"
	},
```

之后就可以自动更新打包了

也可以直接`webpack-dev-server`,打包过后的文件会直接放在内存中

### 防止浏览器自动缓存

现在是写死的`bundle.js`文件名，可以每次打包给一个不同的名字,name可以自定义修改，

```js
module.exports = {
    output: {
        filename: '[name].[contenthash].js',
        path: path.resolve(__dirname, "dist"),
    },
}
```

成功

![image-20230827182442539](./assets/image-20230827182442539.png)

### 给导入路径设置别名

```js
module.exports = {
    resolve: {
        alias: {
            '@': path.resolve(__dirname, 'src')
        }
    },
}
```

