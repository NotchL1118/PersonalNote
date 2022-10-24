# 笔记

## vue.config.js配置文件
> 使用vue inspect > output.js可以查看到Vue脚手架的默认配置
> 使用vue.config.js可以对脚手架进行个性化定制

## 不同版本的Vue
    1.vue.js与vue.runtime.xxx.js区别：
        1）vue.js是完整版的Vue，包含：核心功能+模板解析器
        2）vue.runtime.xxx.js是运行版的Vue，只包含：核心功能；没有模板解析器
    
    2.因为vue.runtime.xxx.js没有模板解析器，所以不能使用template配置项，
        需要使用render函数接收到的createElement函数去指定具体内容

## ref属性

    1.被用来给元素或子组件注册引用信息(id的替代者)
    2.应用在html标签上获取的是真实DOM元素，应用在组件标签上式组件实例对象cv
    3.使用方式
        1.打表示：`<h1 ref="xxx">`...`</h1>` 或 `<School ref="xxx"/>`
        2.获取：`this.$refs.xxx`

## props属性

    功能：让组件接受外部传进来的数据
    1.传递数据：`<Demo name="xxx"/>`
    2.接收数据：
        第一种方式(只接受)：
            props:['name']
        第二种方式(限制类型)：
            props:{
                name:String
            }
        第三种方式(限制类型、限制必要性、指定默认值)
            props:{
                name:{
                    type:String, // 类型
                    required:true, // 必要性
                    default:'LSY' // 默认值
                }
            }
    
    备注：props是只读的，Vue底层会监测你对props的修改，如果进行了修改，会发出警告，
         若确实需要修改，复制props李的内容到data中一份，再去修改data中的数据

## mixin(混入)
    功能：可以把多个组件共用的配置提取成一个混入对象
    使用方式：
        第一步：定义混合
            {
                data(){....}
                methods:{....}
                .....
            }
        第二步：使用混合
            1.全局混入：Vue.mixin(xxx) 在main.js中
            2.局部混入：mixins:['xxx']


## 插件
    功能：用于增强Vue
    本质：包含install方法的一个对象，install的第一个参数是Vue，第二个以后的参数是插件使用者传递的数据
    1.定义插件：
        对象.install = function(Vue，options){
    
        //全局过滤器
        //Vue.filter('过滤器名',function(){})
    
        //全局指令
        //Vue.directive('指令名',function(){})
    
        //全局混入
        //Vue.mixin({})
    
        //全局组件
        //Vue.component('组件名',function(){})
    
        //原型方法
        //Vue.prototype.$方法名 = function(){}
    
        }
    2.使用插件：Vue.use()，在main.js中

## scoped样式
    作用：让样式在局部生效，防止冲突
    写法：<style scoped>


## 总结TodoList案例
    1.组件化编码流程：
        (1)拆分静态组件：组件要按照功能点拆分，命名不能要html元素冲突
        (2)实现动态组件：考虑好数据的存放位置，数据是一个组件在用，还是一些组件再用
            1)一个组件在用：放在组件自身即可
            2)一些组件在用：放在他们共同的父组件上(状态提升)
        (3)实现交互：从绑定事件开始
    
    2.props适用于：
        (1)父组件===> 子组件通信
        (2)子组件===> 父组件通信(要求父给子一个函数)
    
    3.使用v-model切记，v-model绑定的值不能是props传过来的值，因为props不可以修改
    4.props传过来的若是对象类型的值，修改对象中的属性Vue不会报错，但不推荐这样做


## webStorage
    1.存储内容大小一般支持5MB左右(不同浏览器不同)
    2.浏览器端可以通过Window.sessionStorage 和 Window.localStorage 属性来实现本地存储机制
    3.相关API：
        1.`xxxStorage.setItem('key','value')`
        该方法接受一个键和一个值作为参数，把键值对添加到存储中，如果键名存在，更新值
    
        2.`xxxStorage.getItem('key')`
        该方法接受一个键名，返回键名对应的值
    
        3.`xxxStorage.removeItem('key')`
        该方法接受一个键名，删除
    
        4.`xxxStorage.clear()`
        清空存储中的所有数据
    
    4.备注
        1.SessionStorage存储的内容会随着浏览器窗口关闭而消失
        2.LocalStorage存储的内容，需要手动清除才会消失
        3.`xxxStorage.getItem('key')` 如果对应value的值获取不到，返回值是null
        4.`JSON.parse(null)`的结果依然是null


## 组件的自定义事件
    1.一种组件间通信的方式，适用于 **子组件 ==> 父组件**
    2.使用场景：A是父组件，B是子组件，B想给A传数据，就在A中给B绑定自定义事件(事件的回调在A中)
    3.绑定自定义事件：
        (1).第一种方式，在父组件中 `<子组件 @事件名="调用函数"/ >` 或 `<子组件 v-on:事件名="调用函数"/ >`
        (2).第二种方式，在父组件中
        ```JavaScript
        <子组件 ref="xxx"/ >
        ....
        mounted(){
            this.$refs.xxx.$on('事件名',this.调用函数)
        }
        ```
        (3).若想让自定义事件只触发一次，可以使用`once`修饰符 或 `$once` 方法
    
    4.触发自定义事件:`this.$emit('事件名',参数)`
    5.解绑自定义事件:`this.$off('事件名')`，多个事件解绑就以数组形式传进去`this.$off(['事件1','事件2'])`
    6.组件上也可以绑定原生DOM事件，需要使用`native`修饰符
    7.注意：通过`this.$refs.xxx.$on('事件名',回调)`绑定自定义事件时，回调要么配置在父组件methods中，要么用箭头函数，否则this指向会出问题

## 全局事件总线
    1.一种组件间通信的方式，适用于任意组件间通信
    2.安装全局事件总线：
        new Vue({
            ....
            beforeCreate(){
                Vue.prototype.$bus = this //安装全局事件总线，$bus就是当前应用的vm
            },
            ....
        })
    
    3.使用事件总线：
        (1).接收数据：A组件像接收数据，则在A组件中给$bus绑定自定义事件，事件的回调留在A组件自身
            methods(){
                demo(data){
                    ....
                }
            }
            ....
            mounted(){
                this.$bus.$on('xxxx',this.demo)
                // 或者
                this.$bus.$on('xxxx',(data)=>{
                    .....
                })
            }
        (2).提供数据
            this.$bus.$emit('xxxx',数据)
    
    4.最好在beforeDestroy钩子中，用$off解绑当前组件所用到的事件

## 消息订阅与发布(pubsub)
    1.一种组件间通信的方式，适用于任意组件间通信(有很多库可以用，这里用pubsub)
    2.使用步骤：
        (1).安装pubsub: npm i pubsub-js
        (2).引入: import pubsub from 'pubsub-js'
        (3).接收数据: A组件想要接收数据，则在A组件中订阅消息，订阅的毁掉留在A组件自身
            methods(){
                demo(data){
                    .....
                }
            }
            ....
            mounted(){
                this.pid = pubsub.subscribe('xxx',this.demo) //订阅消息
                this.pid = pubsub.subcribe('xxx',()=>{
                    //第二种方式
                })
            }
        (4).提供数据: pubsub.publish('xxx',数据)
        (5).最好在beforeDestroy钩子中，用pubsub.unsubscribe(pid)来取消订阅

## nextTick
    1.语法：this.$nextTick(回调函数)
    2.作用：在下一次DOM更新结束后执行指定的回调
    3.什么时候用：当改变数据后，要基于更新后的新DOM进行某些操作，要在nextTick所指定的回调函数中执行

## Vue封装的过度和动画
    1.作用：在插入、更新或移除DOM元素时，在合适的时候给元素添加样式类名
    2.写法：
        (1).准备好样式
            - 元素进入的样式
            - 1.v-enter：进入的起点
            - 2.v-enter-active：进入的过程中
            - 3.v-enter-to：进入的终点
            - 元素离开的样式
            - 1.v-leave：离开的起点
            - 2.v-leave-active：离开的过程中
            - 3.v-leave-to：离开的终点
        (2).使用transition包裹要过渡的元素，并配置name属性
            <transition name="hello" appear>
                <h2 v-show='isShow'>你好Vue</h2>
            </transition>
        (3).如果是有多个元素，要用transition-group，且要给每个元素配置key值，可以配合v-for使用 

3.图示：
    ![image-20221005223838373](D:\Ccode\Vue\vue_test\assets\image-20221005223838373.png)


## Vue脚手架配置代理
    1.方法一
        在Vue.config.js中添加如下配置：
            devServer：{
                proxy:"http://localhost:5000"
            }
    
        说明：
            1.优点：配置简单，请求资源时候直接发给前端(8080)即可
            2.缺点：不能配置多个代理，不能灵活的控制请求是否走代理
            3.工作方式：若按照上述配置代理，当请求了前端不存在的资源时候，该请求会转发给服务器(优先匹配前端资源)
    
    2.方法二
        在Vue.config.js中配置具体代理规则
        module.exports = {
        devServer: {
            proxy: {
            '/api': {              //匹配所有以 /api 开头的请求路径
                target: 'http://localhost:5000',   //代理目标的基础路径
                ws: true,
                changeOrigin: true  //该选项默认为true，目标服务器收到的请求头的host为http://localhost:5000，false为http://localhost:8080
            },
            '/foo': {
                target: '<other_url>'
                }
            },
            '/api1': {          
                target: '<url>',
                ws: true,
                changeOrigin: true
            },
            '/foo': {
                target: '<other_url>'
                }
            }
        }
    }
    
        说明：
            1.优点：可以配置多个代理，且可以灵活的控制请求是否走代理
            2.缺点：配置繁琐，请求资源时必须加前缀


## 插槽
    1.作用:让父组件可以向子组件指定位置插入html结构，也是一种组件间通信方式，适用于 父组件 ==> 子组件
    2.分类：默认插槽，具名插槽，作用于插槽
    3.使用方式：
        1.默认插槽
        ```
        父组件中：
            <Category>
                <div>html结构</div>
            </Category>
    
        子组件中：
            <template>
                <div>
                    <!-- 定义插槽 -->
                    <slot>默认内容</slot>
                </div>
            </template>
        ```
        2.具名插槽:
        ```
        父组件中：
            <Category>
                <template slot="center">
                    <div>html结构</div>
                </template>
    
                <template v-slot:footer>
                    <div>html结构</div>
                </template>  
            </Category>
        子组件中：
            <template>
                <div>
                    <!-- 定义插槽 -->
                    <slot name="center">默认内容</slot>
                    <slot name="footer">默认内容</slot>
                </div>
            </template>
        ```
    
        3.作用域插槽
            1.理解：数据在组件自身，但根据数据生成的结构需要组件的使用者来决定(例如：foods的数据在Category组件里，但使用数据
            所遍历出来的结构由App组件来决定)
            2.代码：
            ```
            父组件中：     
                <!-- 第一种写法 scope -->
                <category title="食物">
                    <template scope="Dates">
                        <ul>
                            <li v-for="(g,index) in Dates.foods" :key="index">{{g}}</li>
                        </ul>
                    </template>
                </category>
                <!-- 第二种ES6写法 -->
                <category title="食物">
                    <template scope="{foods}">
                        <ul>
                            <li v-for="(g,index) in foods" :key="index">{{g}}</li>
                        </ul>
                    </template>
                </category>
                <!-- 第三种新式写法 slot-scope -->
                <category title="食物">
                    <template slot-scope="{foods}">
                        <ul>
                            <h4 v-for="(g,index) in foods" :key="index">{{g}}</h4>
                        </ul>
                    </template>
                </category>      
            子组件中：
                <template>
                    <div>
                        <h3>{{title}}</h3>
                        <slot :foods="foods">如果没值，默认就是这个</slot>
                    </div>
                </template>   
    
                <script>
                    export default {
                        name:'Category',
                        props:['title'],
                        <!-- 数据在子组件自身 -->
                        data(){
                            return {
                                foods:['pizza','burger','hotdog']
                            }
                        }
                    }
                </script>                  
            ```


## Vuex
    1.概念
        在Vue中实现集中式状态(数据)管理的一个Vue插件，对vue应用中的多个组件的共享状态进行集中式的管理(读/写)，也是一种组件间通信的方式，且适用于任意组件间通信
        
    2.何时使用
        多个组件需要共享数据时
        
    3.搭建Vuex环境
        1.创建文件 src/store/index.js
            //引入Vue
            import Vue from 'vue'
            //引入Vuex
            import Vuex from 'vuex'
            //Vuex必须在store实例创建之前就使用Vue.use()来安装
            Vue.use(Vuex)
    
            //准备actions——用于响应组件中的动作
            const actions = {}
    
            //准备mutations——用于操作数据（state）
            const mutations = {}
    
            //准备state——用于存储数据
            const state = {}
    
            //创建并暴露store
            export default new Vuex.Store({
                actions,
                mutations,
                state
            })
        2.在main.js中创建vm时传入store配置项
        new Vue({
            render: h => h(App),
            store, //挂载store对象
        }).$mount('#app')
    
    4.基础使用
        1.初始化数据，配置actions、mutations、操作文件store.js
        2.组件中读取vuex中的数据：$store.state.sum
        3.组件中修改vuex中的数据：$store.dispatch('action中的方法名',数据)
                              $store.commit('mutation中的方法名',数据)
        > 备注：若没有网络请求或其他业务逻辑，组件可以越过actions，即不写dispatch，直接写commit
    
    5.getters的使用
        1.概念：当state中的数据需要经过加工后再使用，可以使用getters加工
        2.在store.js(在这里是./store/index.js)中追加getters配置
            const getters = {
                bigSum(state){
                    return state.sum * 10
                }
            }
    
            //创建并暴露store
            export default new Vuex.Store({
                ....
                getters
            })        
        3.组件中读取数据： $store.getters.bigSum
    
    6.四个map方法的使用
        1. mapState方法：用于映射state中的数据为计算属性，语法糖
            computed:{
                //【对象写法】，语法糖，利用mapState生成计算属性从state种读取数据,mapState是一个对象，所以需要展开来
                ..mapState({name:'name', age:'age'}),
    
                //【数组写法】,可以简写
                ...mapState(['name','age'])
            }     
    
        2. mapGetters方法：用于映射getters中的数据为计算属性
            computed:{
                //【对象写法】，语法糖，利用mapState生成计算属性从state种读取数据,mapState是一个对象，所以需要展开来
                ..mapGetters({bigNum:'bigNum'}),
    
                //【数组写法】,可以简写
                ...mapGetters(['bigNum'])
            }           
    
        3. mapActions方法：用于生成与actions对话的方法，即包含 $store.dispatch(xxx)的函数
            methods:{
                // 【对象写法】，上面click事件调用要添加参数incrementOdd(n)
                ...mapActions({
                    incrementOdd:'incrementOdd',
                    incrementWait:'incrementWait'
                })
    
                // 【数组写法】
                // ...mapActions(['incrementOdd','incrementWait'])
            }  
    
        4. mapMutations方法：用于生成与mutations对话的方法，即包含 $store.commit(xxx)的函数
            methods:{
                // 【对象写法】，上面click事件调用要添加参数increment(n)
                ...mapMutations({
                    increment:'INCREMENT',
                    deincrement:'DEINCREMENT'
                }),
                
                // 【数组写法】  
                // ...mapMutations(['INCREMENT','DEINCREMENT']),
            }  
    
    7.模块化+命名空间
        1.目的：让代码更好维护，让多种数据分类更加准确
        2.修改store.js
            const personOptions = {
                namespaced: true,//开启命名空间
                actions:{
                    ......
                },
                mutations:{  
                    ......
                },
                state:{
                    ......
                },
                getters:{
                    .......
                }
            }
            
            export default new Vuex.Store({
                modules:{
                    person:personOptions
                }
            })
        3.开启命名空间后，组件中读取state数据
            //方式一，自己直接读取
            this.$store.state.person.list
            //方式二，借助mapState
            ...mapState('person',['list','sum','name'])
    
        4.开启命名空间后，组件中读取getters数据
            //方式一，自己直接读取
            this.$store.getters['person/firstName']
            //方式二，借助mapGetters
            ...mapGetters('person',['firstName'])
    
        5.开启命名空间后，组件中调用dispatch
            //方式一，自己直接dispatch
            this.$store.dispatch('person/addPerson',newPerson)
            //方式二，借助mapActions
            ...mapActions('person',['addPerson'])
    
        6.开启命名空间后，组件中调用commit
            //方式一，自己直接commit
            this.$store.commit('person/ADD_PERSON',newPerson)
            //方式二，借助mapMutations
            ...mapMutations('person',['ADD_PERSON'])

## 路由
### 1.基本使用
        1.安装vue-router，命令： npm i vue-router(现在默认安装4版本，适用于vue3)
        2.引用并应用插件 Vue.use(VueRouter)    
        3.编写router配置项：
            //该文件专门用来创建整个服务器的路由器
            import VueRouter from "vue-router";
            //引用路由组件
            import About from "../components/About";
            import Home from "../components/Home";

            //创建一个路由器并传入配置对象并暴露
            export default new VueRouter({
                routes:[
                    {
                        path:'/about',
                        component:About
                    },
                    {
                        path:'/home',
                        component:Home
                    },
                ]
            })
        4.实现切换(active-class可以配置高亮样式)
            <router-link class="list-group-item" active-class="active" to="/about">About</router-link>
        5.指定展示位置
            <router-view></router-view>  

### 2.几个注意点
        1.路由组件通常存放在pages文件夹，一般组件存放在components文件夹
        2.通过切换，"隐藏"了的路由组件，默认是被销毁的，需要的时候再去挂载
        3.每个组件都有自己的$route属性，里面存放自己的路由信息
        4.整个应用只有一个router，可以通过组件的$router属性获取      

### 3.多级路由(嵌套路由)
        1.配置路由规则，添加一个children配置项
            export default new VueRouter({
                routes:[
                    {
                        path:'/home',
                        component:Home,
                        children:[
                            {
                                path:'news',  //此处不要写/news
                                component:News
                            },
                            {
                                path:'message',
                                component:Message,
                            }
                        ]
                    },
                ]
            })     
        2.跳转(要写完整路径)
            <router-link class="list-group-item" active-class="active" to="/home/news">News</router-link>

### 4.路由的query传参
    1.传递参数
        <!-- 跳转并携带query参数 to的字符串写法 -->
        <router-link :to="`/home/message/detail?id=${m.id}&title=${m.title}`">{{m.title}}<router-link>

        <!-- 跳转并携带query参数 to的对象写法 -->
        <router-link
            :to="{
                path:'/home/message/detail',
                query:{
                        id:m.id,
                        title:m.title
                    }
                }"
        > {{m.title}}</router-link>
    
    2.接收参数
        $route.query.id
        $route.query.title

### 5.命名路由
    1.作用：简化路由的跳转
    2.使用：
        1.给路由命名
        routes:[
            {
                name:'guanyu'
                path:'/about',
                component:About
            },
        ]
        2.简化调整
        <!-- 简化前需要完整路径 -->
            <router-link to="/about">About</router-link>

        <!-- 简化后，通过名字 -->
            <router-link :to="{name:'guanyu'}">About</router-link>

        <!-- 简化写法配合传递参数 -->
            <router-link 
                :to="{
                    name:'guanyu',
                    query:{
                        id:666,
                        title:'TEST'
                    }
                }"
            >About</router-link>

### 6.路由的params传参
    1.配置路由，声明接受params参数
        routes:[
            {
                path:'/home',
                component:Home,
                children:[
                    {
                        path:'message',
                        component:Message,
                        children:[
                            {
                                name:'Detail',
                                path:'detail/:id/:title', //要声明接受的params参数
                                component:Detail
                            }
                        ]
                    }
                ]
            },
        ]
    2.传递参数
        <!-- 跳转并传递params参数，to的字符串写法 -->
        <router-link :to="`/home/message/detail/${m.id}/${m.title}`">{{m.title}}</router-link>

        <!-- 跳转并携带params参数 to的对象写法 -->
        <router-link :to="{
            name:'Detail',  //一定得写name，不能写path
            params:{
                id:m.id,
                title:m.title
            }
        }"> {{m.title}}</router-link>

    > 注意，路由携带params参数，若使用to的对象写法，不能使用path配置项，必须使用name

    3.接收参数
        <li>{{$route.params.id}}</li>
        <li>{{$route.params.title}}</li>

### 7.路由的props配置
    1.作用：让路由组件更方便的收到参数
    2.配置
        children:[
                    {
                        name:'Detail',
                        path:'detail/:id/:title',
                        component:Detail,

                        //第一种写法，值为对象，会将该对象中的所有key-value以props的形式传递给Detail组件
                        // props:{a:1,b:'hello'}

                        //第二种写法，值为布尔值，若为true，则会将路由组件收到的所有params参数以props的形式传递给Detail组件
                        // props:true

                        //第三种写法，值为函数,会将该对象中的所有key-value以props的形式传递给Detail组件
                        props(route){
                            return {
                                id:route.query.id,
                                title:route.query.title
                            }
                        }
                            //还可以展开
                            //props({query}){return {id:query.id,title:query.title}}
                    }
                ]

### 8.<router-link>的replace属性
    1.作用：控制路由跳转时操作浏览器历史记录的模式
    2.浏览器的历史记录有两种写入方式：分别为push和replace，push是追加历史记录，replace是替换当前记录。路由跳转
      时候默认为push
    3.如何开启 <router-link replace .....> News </router-link>

### 9.编程式路由导航
    1.作用：不借助<router-link>实现路由跳转，让路由跳转更灵活
    2.具体编码：
        //主要依靠router的两个api
            this.$router.push({
                name:'Detail',
                params:{
                    id:m.id,
                    title:m.title
                }  
            })
        
            this.$router.replace({
                name:'Detail',
                params:{
                    id:m.id,
                    title:m.title
                }
            })
    3.补充
        1.前进
        this.$router.forword()
        2.后退
        this.$router.back()
        3.自定义前进后退
        this.$router.go() //正数前进，复数后退

### 10.缓存路由组件
    1.作用：让不展示的路由保持挂载，不被销毁
    2.代码
        <keep-alive include="News">
            <router-view></router-view>
        </keep-alive>
        //多个 
        <keep-alive :include="['News','Message']">
            <router-view></router-view>
        </keep-alive>

### 11.新的生命周期钩子
    1.作用：路由组件所独有的两个钩子，用于捕获路由组件的激活状态
    2.具体名字：
        1.activated 路由组件被激活时触发
        2.deactivated 路由组件失活时被触发

### 12.路由守卫
    1.作用：对路由进行权限控制
    2.分类：全局守卫，独享守卫，组件内守卫
        1.全局守卫
            //全局前置路由守卫 ------ 初始化时、每次路由切换前被调用 
            router.beforeEach((to,from,next)=>{
                if(to.meta.isAuth){ //判断是否需要进行权限控制
                    if(localStorage.getItem('name') === 'LSY') //权限控制的具体规则
                    {
                        next(); //放行，跳转到下一界面
                    }
                    else
                    {
                        alert('请先登录');
                    }
                }
                else
                {
                    next();
                }
            })

            //全局后置路由守卫 ------ 初始化时、每次路由切换后被调用 
            router.afterEach((to,from)=>{
                document.title = to.meta.title || "默认标题";  //修改网页的title
            })
        2.独享守卫：
            beforeEnter(to,from,next){
                
            }

        3.组件内守卫
            // 进入守卫：通过路由规则，进入该组件时被调用
            beforeRouteEnter (to, from, next) {
                console.log('About beforeRouteEnter')
                next();
            },

            // 离开守卫：通过路由规则，离开该组件时被调用
            beforeRouteLeave (to, from, next) {
                console.log('About beforeRouteLeave')
                next();
            }

### 13.路由器的两种工作模式
    1.对于一个url来说，什么是hash值？ --- #及其后面的内容就是hash值
    2.hash值不会包含在http请求中，即：hash值不会带给服务器
    3.hash模式：
        1.地址中永远带着#号，不美观
        2.若以后将地址通过第三方收集app分享，若app校验严格，则地址会被标记为不合法
        3.兼容性好
    4.history模式
        1.地址干净
        2.兼容性比hash模式略差
        3.应用部署上线时需要后端人员支持，解决刷新页面服务端404问题